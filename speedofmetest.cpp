#include <cstdlib>
#include "speedofmetest.h"

SpeedOfMeTest::SpeedOfMeTest()
{
	timer = new QTimer(this);	
}

void SpeedOfMeTest::checkPage() {
	if(rand()%2)
		emit succeeded(10, 4);
	else
		emit failed("");
}

void SpeedOfMeTest::start()
{
	emit started();
}
