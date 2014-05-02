#ifndef WEBTEST_H
#define WEBTEST_H

#include <QWebPage>
#include "basetest.h"

class WebTest : public BaseTest {
	Q_OBJECT

public:
	WebTest();
	~WebTest();

private:
	QWebPage page;
	
};

#endif
