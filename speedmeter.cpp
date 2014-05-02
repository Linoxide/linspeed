#include <QLabel>
#include <QVBoxLayout>
#include "speedmeter.h"

SpeedMeter::SpeedMeter(const QString& text, QWidget *parent) 
	: QWidget(parent)
{
	QLabel *label = new QLabel(text);
	QLabel *result = new QLabel("-- kbps");

	QVBoxLayout *layout = new QVBoxLayout;
	this->setLayout(layout);

	layout->addWidget(label);
	layout->addWidget(result);
}
