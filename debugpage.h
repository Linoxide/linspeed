#ifndef DEBUGPAGE_H
#define DEBUGPAGE_H

#include <QWebPage>
#include <QWebFrame>
#include <string>

class DebugPage : public QWebPage {
	Q_OBJECT

public:
	DebugPage(QWidget *parent=0);

	void javaScriptConsoleMessage(const QString & message, int lineNumber, const QString & sourceID);
};

#endif
