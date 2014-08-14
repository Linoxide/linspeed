/*
 *  Copyright (C) 2014 Linoxide <linoxide@gmail.com>
 *  Copyright (C) 2014 Michał Łuszczyk <michal.luszczyk@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

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

protected slots:
	void contextMenuEvent(QContextMenuEvent *event);

	void testSucceeded(double download_speed, double upload_speed);
	void testFailed(const QString& text);
	void testProgressed(const QString &testName, double currentSpeed);
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
