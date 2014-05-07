#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "speedmeter.h"
#include "speedofmetest.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

private slots:
	void testSucceeded(double download_speed,
		double upload_speed);
	void testFailed(const QString& text);
	void testProgressed(const QString &testName,
		int testProgress, double currentSpeed);
	void testStarted();

private:
	SpeedMeter *download;
	SpeedMeter *upload;
	QPushButton *startButton;

	SpeedOfMeTest test;
};

#endif
