#include "speedmeter.h"

SpeedMeter::SpeedMeter(double _num, const QString &_format, QWidget *parent) 
	: QLabel(parent), format(_format) 
{
    setValue(_num);
	setLabelSize(longestNum);
    setAlignment(Qt::AlignCenter);
}

void SpeedMeter::setEmpty()
{
    setValue(0);
}

void SpeedMeter::setValue(double num)
{
    QString formattedNum = QString::number(num);
    if(num==0)
        formattedNum = "—";
	setText(QString(format).arg(formattedNum));
}

void SpeedMeter::setLabelSize(double longestValue)
{
    setValue(longestValue);
	setFixedSize(sizeHint());
    setValue(num);
}

void SpeedMeter::setFormat(const QString& _format)
{
    format = _format;
    setValue(num);
    setLabelSize(longestNum);
}
