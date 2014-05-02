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
	void succeeded(double download_speed,
		double upload_speed);
};

#endif
