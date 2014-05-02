#ifndef SPEEDMETER_H
#define SPEEDMETER_H

#include <QWidget>
#include <QString>
#include <QLabel>

class SpeedMeter : public QWidget {
	Q_OBJECT

public:
	SpeedMeter(const QString& text, QWidget *parent = 0);

public slots:
	void setValue(double num);

private:
	QLabel *value;

};

#endif
