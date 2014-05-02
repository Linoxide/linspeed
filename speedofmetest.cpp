#include <cstdlib>
#include "speedofmetest.h"

SpeedOfMeTest::SpeedOfMeTest()
{
	timer = new QTimer(this);
	timer->setSingleShot(true);
	connect(timer, SIGNAL(timeout()),
		this, SLOT(checkPage()));
}

void SpeedOfMeTest::checkPage() {
	if(rand()%2)
		emit succeeded(10, 4);
	else
		emit failed(QString(""));
}

void SpeedOfMeTest::start()
{
	timer->start(2000);
	emit started();
}
