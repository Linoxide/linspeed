#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include "speedmeter.h"
#include "speedofmetest.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

protected:
	void contextMenuEvent(QContextMenuEvent *event);

private slots:
	void testSucceeded(double download_speed,
		double upload_speed);
	void testFailed(const QString& text);
	void testProgressed(const QString &testName,
		int testProgress, double currentSpeed);
	void testStarted();
	
	void setStatusMessage(const QString &str);
	void clearStatusMessage();
	void updateStatusMessage();

	void toggleShowFrame(bool state);

	void rearrangeLarge();
	void rearrangeSmall();
	void setStyles(const QString& filename);
	void loadTheme(const QString& name);
	void switchTheme(QAction *action);

	void report();
	void about();

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	void closeEvent(QCloseEvent *event);

private:
	QLabel *downloadLabel;
	QLabel *uploadLabel;
	SpeedMeter *download;
	SpeedMeter *upload;
	QPushButton *startButton;
	QLabel *statusMessage;

	SpeedOfMeTest test;

	QString statusMessageString;
	bool showFrame;
	QString currentTheme;
	QString statusFormat;

	QPoint clickPos;
};

#endif
