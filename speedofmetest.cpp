#include <cstdlib>
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
	qDebug() << page.currentFrame()->toPlainText().toUtf8().constData();
	timer->start(2000);
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
