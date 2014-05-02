#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "speedmeter.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

public slots:
	void startClicked();

private:
	SpeedMeter *download;
	SpeedMeter *upload;
	QPushButton *startButton;
};

#endif
