#ifndef WEBTEST_H
#define WEBTEST_H

#include "basetest.h"
#include "debugpage.h"

class WebTest : public BaseTest {
	Q_OBJECT

public:
	WebTest();
	~WebTest();

protected:
	DebugPage page;
	
};

#endif
