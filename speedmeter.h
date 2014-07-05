#ifndef SPEEDMETER_H
#define SPEEDMETER_H

#include <QWidget>
#include <QString>
#include <QLabel>

class SpeedMeter : public QLabel {
	Q_OBJECT

public:
	SpeedMeter(double _num, const QString& _format, QWidget *parent = 0);

public slots:
	void setValue(double num);
	void setEmpty();
	void setFormat(const QString &_format);

protected:
	double num;
	QString format;
};

#endif
