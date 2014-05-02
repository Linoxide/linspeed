#include "debugpage.h"

DebugPage::DebugPage(QWidget *parent) : QWebPage(parent) {}

void DebugPage::javaScriptConsoleMessage(const QString & message, int lineNumber, const QString & sourceID) {
	qDebug() << message << " " << lineNumber << " " << sourceID;
}

