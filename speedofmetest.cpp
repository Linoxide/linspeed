/*
 *  Copyright (C) 2014 Linoxide <linoxide@gmail.com>
 *  Copyright (C) 2014 Michał Łuszczyk <michal.luszczyk@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <cstdlib>
#include <QWebElement>
#include <QWebFrame>
#include "speedofmetest.h"

const int CHECK_INTERVAL = 100;
const int MAX_NUM_CHECK = 1200;
const int WAIT_FOR_LOAD = 10000;
const int WAIT_BEFORE_RUNNING = 2500;

const QString TEST_URL = "http://linoxide.com/speedtest/speedtest.html";

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

	emit progressed(type, parseField("currentSpeed").toDouble());
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
	emit failed("Internal error");
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
		if(!webTestInQueue) {
			QTimer::singleShot(WAIT_BEFORE_RUNNING, 
				this, SLOT(tryStartTest()));
			webTestInQueue = true;
		}
		if(webTestStarted) {
			tryGetResults();
		}
	}

	timesChecked++;
	if(running && timesChecked < MAX_NUM_CHECK) {
		timer->start(CHECK_INTERVAL);
	} else {
		if(running) {
			running = false;
			emit failed("Timeout");
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
		webTestInQueue = false;
		emit started();
	} else {
		running = false;
		page.currentFrame()->setUrl(QUrl(""));
		emit failed("Cancelled");
	}
}

void SpeedOfMeTest::pageLoaded(bool)
{
	if(!running) return;

	QWebElement el = page.currentFrame()->findFirstElement("#status");
	if(el.isNull()) {
		running = false;
		emit failed("No Internet connection");
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
