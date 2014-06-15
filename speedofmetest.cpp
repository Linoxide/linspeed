#include <cstdlib>
#include <QWebElement>
#include <QWebFrame>
#include "speedofmetest.h"

const int CHECK_INTERVAL = 1000;
const int MAX_NUM_CHECK = 60;
const int WAIT_FOR_LOAD = 5000;

const QString TEST_URL = "http://ii-lo.tarnow.pl/~michal/speedtest.html";

SpeedOfMeTest::SpeedOfMeTest()
{
	running = false;
	timer = new QTimer(this);
	timer->setSingleShot(true);
	connect(timer, SIGNAL(timeout()),
		this, SLOT(checkPage()));
	connect(page.currentFrame(), SIGNAL(loadFinished(bool)),
		this, SLOT(pageLoaded(bool)));
}

QString SpeedOfMeTest::parseField(const QString& name) const
{
	return page.currentFrame()->findFirstElement('#'+name).toInnerXml();
}

void SpeedOfMeTest::tryGetResults()
{
	QString status = parseField("status");
	if(status == "progress") {
		parseProgress();
	} else if(status == "error") {
		parseError();
	} else if(status == "success") {
		parseSuccess();
	}

}

void SpeedOfMeTest::parseProgress()
{
	const QString &type = parseField("type");
	int num_tests;

	// should be retrieved from API, but it does not provide such info
	if(type=="download")
		num_tests = 3;
	else if(type=="upload")
		num_tests = 1;
	else {
		return; // don't crash just because of bad progress notification
	}

	emit progressed(type, ((parseField("pass").toInt()-1)*100+parseField("percentDone").toInt())/num_tests,
		parseField("currentSpeed").toDouble());
}

void SpeedOfMeTest::parseSuccess()
{
	const QString &down = parseField("download"),
		&up = parseField("upload");

	running = false;
	emit succeeded(down.toDouble(), up.toDouble());
}

void SpeedOfMeTest::parseError()
{
	running = false;
	emit failed(parseField("error"));
}

void SpeedOfMeTest::tryStartTest()
{
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
		if(running) {
			running = false;
			emit failed("timeout");
		}
		page.currentFrame()->load(QUrl(""));
	}
}

void SpeedOfMeTest::start()
{
	if(!running) {
		timer->start(2000);
		page.currentFrame()->load(TEST_URL);
		QTimer::singleShot(WAIT_FOR_LOAD, this, SLOT(failUnlessLoaded()));
		running = true;
		loaded = false;
		timesChecked = 0;
		webTestStarted = false;
		emit started();
	} else {
		running = false;
		page.currentFrame()->setUrl(QUrl(""));
		emit failed("cancelled");
	}
}

void SpeedOfMeTest::pageLoaded(bool)
{
	if(!running) return;

	QWebElement el = page.currentFrame()->findFirstElement("#status");
	if(el.isNull()) {
		running = false;
		emit failed("wrong page loaded");
	}

	loaded = true;
}

void SpeedOfMeTest::failUnlessLoaded()
{
	if(!loaded) {
		emit failed("No Internet connection");
		running = false;
		timer->stop();
	}
}
