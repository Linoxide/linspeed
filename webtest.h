#ifndef WEBTEST_H
#define WEBTEST_H

#include "basetest.h"
#include "debugpage.h"
#include <QWebPage>

class WebTest : public BaseTest {
	Q_OBJECT

public:
	WebTest();
	~WebTest();

protected:
	QWebPage page;
	
};

#endif
