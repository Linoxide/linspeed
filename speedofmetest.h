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

private:
	QTimer *timer;

};

#endif
