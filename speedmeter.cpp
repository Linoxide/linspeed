#include <QVBoxLayout>
#include "speedmeter.h"

SpeedMeter::SpeedMeter(const QString& text, QWidget *parent) 
	: QWidget(parent)
{
	QLabel *label = new QLabel(text);
	value = new QLabel("-- kbps");

	QVBoxLayout *layout = new QVBoxLayout;
	this->setLayout(layout);

	layout->addWidget(label);
	layout->addWidget(value);
}

void SpeedMeter::setValue(double num) {
	this->value->setNum(num);
}
