#include <cstdlib>
#include <QJsonDocument>
#include <QJsonObject>
#include <QWebElement>
#include <QWebFrame>
#include <QWebView>
#include "speedofmetest.h"

const int CHECK_INTERVAL = 500;
const int MAX_NUM_CHECK = 60;

const QString TEST_URL = "http://speedof.me/api/doc/sample.html";
const QString JS_COMPLETED = 
	"SomApi.onTestCompleted = function(res) { "
	"msgDiv.innerHTML = JSON.stringify({ 'success': true, 'data': res }) }";
const QString JS_ERROR = 
	"SomApi.onTestError = function(res) { "
	"msgDiv.innerHTML = JSON.stringify({ 'success': false, 'data': res }) }";

SpeedOfMeTest::SpeedOfMeTest()
{
	QWebView *webview = new QWebView;
	webview->setPage(&page);
	webview->show();

	timer = new QTimer(this);
	timer->setSingleShot(true);
	connect(timer, SIGNAL(timeout()),
		this, SLOT(checkPage()));
	connect(page.currentFrame(), SIGNAL(loadFinished(bool)),
		this, SLOT(pageLoaded(bool)));
}

void SpeedOfMeTest::tryGetResults()
{
	const QWebElement &el = page.currentFrame()->findFirstElement("#msg");
	if(el.isNull()) {
		running = false;
		emit failed("");
	}

	if(el.toInnerXml() == "") {
		qDebug() << "empty";
		timer->start(2000);
	} else {
		qDebug() << el.toInnerXml();
		parseResults(el.toInnerXml());
	}
}

void SpeedOfMeTest::tryStartTest()
{
	qDebug() << "try start test";
	qDebug() << page.currentFrame()->evaluateJavaScript("SomApi.startTest");
	bool ready =  page.currentFrame()->evaluateJavaScript("SomApi.startTest instanceof Function").toBool();
	if(ready) {
		page.currentFrame()->evaluateJavaScript("SomApi.startTest();");
		webTestStarted = true;
	}
}

void SpeedOfMeTest::checkPage()
{
	if(!running) return;

	if(loaded) {
		if(!webTestStarted) {
			tryStartTest();
		} else {
			tryGetResults();
		}
	}

	timesChecked++;
	if(running && timesChecked < MAX_NUM_CHECK) {
		timer->start(CHECK_INTERVAL);
	} else {	
		page.currentFrame()->load(QUrl(""));
	}
}

void SpeedOfMeTest::start()
{
	if(!running) {
		timer->start(2000);
		page.currentFrame()->load(TEST_URL);
		running = true;
		loaded = false;
		timesChecked = 0;
		webTestStarted = false;
		emit started();
	} else {
		running = false;
		page.currentFrame()->setUrl(QUrl(""));
		emit failed("");
	}
}

void SpeedOfMeTest::pageLoaded(bool)
{
	if(!running) return;

	page.currentFrame()->evaluateJavaScript(JS_COMPLETED);
	page.currentFrame()->evaluateJavaScript(JS_ERROR);

	QWebElement el = page.currentFrame()->findFirstElement("#msg");
	if(el.isNull()) {
		running = false;
		emit failed("");
	}

	el.setInnerXml("");

	loaded = true;
}

void SpeedOfMeTest::parseResults(const QString &results)
{
	QJsonDocument doc = QJsonDocument::fromJson(results.toUtf8());
	QJsonObject obj = doc.object();
	if(!obj["success"].toBool()) emit failed("webtest returned error");
	else {
		const QJsonValue &down = obj["data"].toObject()["download"];
		const QJsonValue &up = obj["data"].toObject()["upload"];

		qDebug() << down << up;
		
		if(!down.isDouble() || !up.isDouble())	{
			emit failed("wrong data type");
		} else {
			emit succeeded(down.toDouble(), up.toDouble());
		}
	}
	running = false;
}
