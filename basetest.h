#ifndef BASETEST_H
#define BASETEST_H

#include <QObject>

class BaseTest : public QObject {
	Q_OBJECT

public slots:
	virtual void start() = 0;

signals:
	void running();
	void error(const QString &error);
	void success(double download_speed,
		double upload_speed);
};

#endif
