#include "speedmeter.h"

SpeedMeter::SpeedMeter(double _num, const QString &_format, QWidget *parent) 
	: QLabel(parent), format(_format) 
{
	setValue(_num);
	setAlignment(Qt::AlignCenter);
}

void SpeedMeter::setEmpty()
{
	setValue(0);
}

void SpeedMeter::setValue(double _num)
{
	num = _num;
	QString formattedNum = QString::number(num);
	if(num==0)
		formattedNum = QString::fromUtf8("—");
	setText(QString(format).arg(formattedNum));
}

void SpeedMeter::setFormat(const QString& _format)
{
	format = _format;
	setValue(num);
}
