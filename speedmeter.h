#ifndef SPEEDMETER_H
#define SPEEDMETER_H

#include <QWidget>
#include <QString>

class SpeedMeter : public QWidget {
	Q_OBJECT

public:
	SpeedMeter(const QString& text, QWidget *parent = 0);

public slots:

private:

};

#endif
