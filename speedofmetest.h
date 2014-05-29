#ifndef SPEEDOFMETEST_H
#define SPEEDOFMETEST_H

#include <QTimer>
#include <QWebPage>
#include "basetest.h"

class SpeedOfMeTest : public BaseTest {
	Q_OBJECT

public:
	SpeedOfMeTest();

	void start();

private slots:
	void checkPage();
	void pageLoaded(bool);

private:
	QWebPage page;
	QTimer *timer;
	bool running;
	int timesChecked;
	bool webTestStarted;
	bool loaded;

	QString parseField(const QString &name) const;
	void tryStartTest();
	void tryGetResults();
	void parseProgress();
	void parseError();
	void parseSuccess();

};

#endif
