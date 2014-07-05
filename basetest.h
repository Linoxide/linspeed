#ifndef BASETEST_H
#define BASETEST_H

#include <QObject>

class BaseTest : public QObject {
	Q_OBJECT

public slots:
	virtual void start() = 0;

signals:
	void started();
	void failed(const QString &error);
	void succeeded(double downloadSpeed, double uploadSpeed);
	void progressed(const QString &testName, double currentSpeed);
};

#endif
