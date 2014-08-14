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

#include <map>
#include <QtGui>
#include <QAction>
#include <QActionGroup>
#include <QContextMenuEvent>
#include <QDebug>
#include <QGridLayout>
#include <QMenu>
#include <QSettings>
#include <QSizePolicy>
#include <QStatusBar>
#include "mainwindow.h"
#include "aboutdialog.h"
#include "reportdialog.h"
#include "results.h"
#include "theme.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), showFrame(true)
{
	setWindowTitle("Linspeed");

	downloadLabel = new QLabel("Download");
	uploadLabel = new QLabel("Upload");

	download = new SpeedMeter(0, "%1");
	upload = new SpeedMeter(0, "%1");

	startButton = new QPushButton("Begin Test");

	statusMessage = new QLabel;
	statusMessage->setAlignment(Qt::AlignCenter);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(downloadLabel, 0, 0, Qt::AlignCenter);
	layout->addWidget(uploadLabel, 0, 1, Qt::AlignCenter);
	layout->addWidget(download, 1, 0);
	layout->addWidget(upload, 1, 1);
	layout->addWidget(startButton, 2, 0, 1, 2);
	layout->addWidget(statusMessage, 3, 0, 1, 2);

	QWidget *central = new QWidget;
	central->setLayout(layout);

	this->setCentralWidget(central);

	connect(startButton, SIGNAL(clicked()),
		&this->test, SLOT(start()));

	connect(&this->test, SIGNAL(succeeded(double, double)), 
		this, SLOT(testSucceeded(double, double)));

	connect(&this->test, SIGNAL(failed(const QString&)),
		this, SLOT(testFailed(const QString&)));

	connect(&this->test, SIGNAL(started()),
		this, SLOT(testStarted()));
	
	connect(&this->test, SIGNAL(progressed(const QString&, double)),
		this, SLOT(testProgressed(const QString&, double)));

	Results results;
	if(!results.empty()) {
		QPair<double, double> resPair = results.getLastSpeed();
		this->download->setValue(resPair.first);
		this->upload->setValue(resPair.second);
	}

	QSettings settings;
	restoreGeometry(settings.value("geometry").toByteArray());
	loadTheme(settings.value("theme").toString());
	clearStatusMessage();
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu context(this);
	QMenu *themes = context.addMenu("&Themes");
	QAction *showFrameAction = context.addAction("Show window &frame");
	showFrameAction->setCheckable(true);
	showFrameAction->setChecked(showFrame);
	connect(showFrameAction, SIGNAL(toggled(bool)), 
		this, SLOT(toggleShowFrame(bool)));
	context.addSeparator();

	context.addAction("&Report", this, SLOT(report()));
	context.addSeparator();

	context.addAction("&About", this, SLOT(about()));
	context.addAction("About &Qt", qApp, SLOT(aboutQt()));
	context.addAction("&Close", this, SLOT(close()));

	// themes
	QActionGroup *themesGroup = new QActionGroup(this);
	connect(themesGroup, SIGNAL(triggered(QAction*)),
		this, SLOT(switchTheme(QAction*)));

	map<QString, QMenu*> themeSubmenus;

	QList<Theme> themesList = Theme::listThemes();
	for(int i=0; i<themesList.size(); ++i) {
		Theme& cur = themesList[i];
		QString sizeName = cur.name.section(" ", -1);
		QString nameWithoutSize = cur.name.section(" ", 0, -2);

		if(themeSubmenus.find(nameWithoutSize) == themeSubmenus.end()) {
			QMenu *curMenu = themes->addMenu(nameWithoutSize);
			themeSubmenus[nameWithoutSize] = curMenu;
		}

		QAction *action = themeSubmenus[nameWithoutSize]->addAction(sizeName);
		action->setActionGroup(themesGroup);
		action->setCheckable(true);

		if(currentTheme == cur.name) {
			action->setChecked(true);
		}

		action->setObjectName(cur.name);
	}

	context.exec(event->globalPos());
}

void MainWindow::testSucceeded(double downloadSpeed,
	double uploadSpeed)
{
	this->download->setValue(downloadSpeed);
	this->upload->setValue(uploadSpeed);

	clearStatusMessage();
	startButton->setText("Begin Test");

	Results res;
	res.addResult(downloadSpeed, uploadSpeed);
}

void MainWindow::testFailed(const QString& text)
{
	setStatusMessage(text);
	startButton->setText("Try again");
}

void MainWindow::testProgressed(const QString &testName,
	double currentSpeed)
{
	QString msg = "%1 in progress";
	if(testName=="download") {
		msg = msg.arg("Download");
	} else {
		msg = msg.arg("Upload");
	}

	if(testName=="download")
		this->download->setValue(currentSpeed);
	else if(testName=="upload")
		this->upload->setValue(currentSpeed);
	setStatusMessage(msg);
}


void MainWindow::testStarted()
{
	setStatusMessage("Test in progress");
	this->download->setEmpty();
	this->upload->setEmpty();
	startButton->setText("Cancel");
}

void MainWindow::setStatusMessage(const QString &str) 
{
	statusMessageString = str;
	statusMessage->setText(statusFormat.arg(str));
}

void MainWindow::clearStatusMessage()
{
	setStatusMessage("Ready");
}

void MainWindow::updateStatusMessage()
{
	setStatusMessage(statusMessageString);
}

void MainWindow::switchTheme(QAction *action)
{
	loadTheme(action->objectName());
}

void MainWindow::rearrangeLarge()
{
	download->setFormat("%1 Mbps");
	upload->setFormat("%1 Mbps");

	statusFormat = "%1";
	downloadLabel->show();
	uploadLabel->show();

	updateStatusMessage();
	startButton->setFixedSize(202, 28);
	setFixedSize(220, 120);
}

void MainWindow::rearrangeSmall()
{
	download->setFormat(QString::fromUtf8("↓ %1 M"));
	upload->setFormat(QString::fromUtf8("↑ %1 M"));

	statusFormat = "%1";
	downloadLabel->hide();
	uploadLabel->hide();

	updateStatusMessage();
	startButton->setFixedSize(152, 28);
	setFixedSize(170, 90);
}

void MainWindow::setStyles(const QString& filename) 
{
	QString styleButton, styleBackground;

	if(filename.startsWith("native")) {
		styleButton = "";
		styleBackground = "";
	} else {
		QString pref = filename+"_", suf = "";
		QString fnBackground = pref + "background" + suf,
			fnBtn = pref + "button" + suf,
			fnClick = pref + "button_click" + suf,
			fnHover = pref + "button_hover" + suf;

		styleButton = QString(
			"QPushButton { "
			"background-image: "
			"url(:/themes/%1.png); "
			"border: 0; "
			"padding: 5px; "
			"}\n"
			"QPushButton:hover { "
			"background-image: "
			"url(:/themes/%2.png); "
			"}\n"
			"QPushButton:pressed { "
			"background-image: "
			"url(:/themes/%3.png); "
			"}\n").arg(fnBtn, fnHover, fnClick);

		styleBackground = QString(
			"MainWindow { "
			"background-image: "
			"url(:/themes/%1.png); "
			"}").arg(fnBackground);
	}

	startButton->setStyleSheet(styleButton);
	setStyleSheet(styleBackground);
}

void MainWindow::loadTheme(const QString& name)
{
	QList<Theme> themeList = Theme::listThemes();
	int index;
	for(index=0; index<themeList.size(); ++index) {
		if(themeList[index].name == name)
			break;
	}

	if(index == themeList.size()) {
		index = 0;
	}

	Theme& themeObj = themeList[index];
	currentTheme = themeList[index].name;

	if(themeObj.size == Theme::Large) {
		rearrangeLarge();
	} else {
		rearrangeSmall();
	}

	setStyles(themeObj.filenamePrefix);
}

void MainWindow::toggleShowFrame(bool state)
{
	showFrame = state;
	if(showFrame) {
		setWindowFlags(0);
	} else {
		setWindowFlags(Qt::FramelessWindowHint);
	}
	show();
}

void MainWindow::report() {
	ReportDialog *dialog = new ReportDialog(this);
	dialog->show();
}

void MainWindow::about() {
	AboutDialog *dialog = new AboutDialog(this);
	dialog->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	clickPos = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	move(event->globalPos() - clickPos);
}

void MainWindow::closeEvent(QCloseEvent */*event*/)
{
	QSettings settings;
	settings.setValue("geometry", saveGeometry());
	settings.setValue("theme", currentTheme);
}
