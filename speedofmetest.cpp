#include <cstdlib>
#include <QJsonDocument>
#include <QJsonObject>
#include <QWebElement>
#include <QWebFrame>
#include <QWebView>
#include "speedofmetest.h"

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

void SpeedOfMeTest::checkPage()
{
	static int  num = 0;
	++num;

	if(num == 2) {
		qDebug() << "starting test";
		page.currentFrame()->evaluateJavaScript("SomApi.startTest();");
	}

	const QWebElement &el = page.currentFrame()->findFirstElement("#msg");

	if(el.toInnerXml() == "") {
		qDebug() << "empty";
		timer->start(2000);
	} else {
		qDebug() << el.toInnerXml();
		parseResults(el.toInnerXml());
	}
}

void SpeedOfMeTest::start()
{
	page.currentFrame()->load(TEST_URL);
	emit started();
}

void SpeedOfMeTest::pageLoaded(bool)
{
	timer->start(2000);
	page.currentFrame()->evaluateJavaScript(JS_COMPLETED);
	page.currentFrame()->evaluateJavaScript(JS_ERROR);
	page.currentFrame()->findFirstElement("#msg").setInnerXml("");
}

void SpeedOfMeTest::parseResults(const QString &results)
{
	QJsonDocument doc = QJsonDocument::fromJson(results.toUtf8());
	QJsonObject obj = doc.object();
	if(!obj["success"].toBool()) emit failed("");
	else {
		emit succeeded(obj["data"].toObject()["download"].toDouble(),
			obj["data"].toObject()["upload"].toDouble());
	}
}
