#ifndef SPEEDOFMETEST_H
#define SPEEDOFMETEST_H

#include <QTimer>
#include "webtest.h"

class SpeedOfMeTest : public WebTest {
	Q_OBJECT

public:
	SpeedOfMeTest();

	void start();

private slots:
	void checkPage();
	void pageLoaded(bool);

private:
	QTimer *timer;
	void parseResults(const QString &results);

};

#endif
