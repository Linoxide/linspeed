#include <QVBoxLayout>
#include "speedmeter.h"

SpeedMeter::SpeedMeter(const QString& text, QWidget *parent) 
	: QWidget(parent)
{
	QLabel *label = new QLabel(text);
	label->setAlignment(Qt::AlignCenter);

	value = new QLabel("-");
	setLabelSize("124.23 Mbps", value);
	value->setAlignment(Qt::AlignCenter);

	QVBoxLayout *layout = new QVBoxLayout;
	this->setLayout(layout);

	layout->addWidget(label);
	layout->addWidget(value);
}

void SpeedMeter::setValue(double num)
{
	this->value->setText(QString("%1 Mbps").arg(num));
}

void SpeedMeter::setLabelSize(const QString &longestText, QLabel *label)
{
	QString tcopy = label->text();
	label->setText(longestText);
	label->setFixedSize(label->sizeHint());
	label->setText(tcopy);
}
