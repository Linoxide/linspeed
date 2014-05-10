#include <QtGui>
#include <QAction>
#include <QContextMenuEvent>
#include <QDebug>
#include <QGridLayout>
#include <QMenu>
#include <QSizePolicy>
#include <QStatusBar>
#include "mainwindow.h"
#include "reportdialog.h"
#include "results.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	download = new SpeedMeter("Download");
	upload = new SpeedMeter("Upload");

	startButton = new QPushButton("Begin Test");

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(download, 0, 0);
	layout->addWidget(upload, 0, 1);
	layout->addWidget(startButton, 1, 0, 1, 2);

	QWidget *central = new QWidget;
	central->setLayout(layout);

	this->setCentralWidget(central);

	QStatusBar *sbar = new QStatusBar;
	this->setStatusBar(sbar);
	statusMessage = new QLabel;
	sbar->addWidget(statusMessage, 1);
	clearStatusMessage();

	setFixedSize(sizeHint());

	connect(startButton, SIGNAL(clicked()),
		&this->test, SLOT(start()));

	connect(&this->test, SIGNAL(succeeded(double, double)), 
		this, SLOT(testSucceeded(double, double)));

	connect(&this->test, SIGNAL(failed(const QString&)),
		this, SLOT(testFailed(const QString&)));

	connect(&this->test, SIGNAL(started()),
		this, SLOT(testStarted()));
	
	connect(&this->test, SIGNAL(progressed(const QString&, int, double)),
		this, SLOT(testProgressed(const QString&, int, double)));

	Results results;
	if(!results.empty()) {
		QPair<double, double> resPair = results.getLastSpeed();
		this->download->setValue(resPair.first);
		this->upload->setValue(resPair.second);
	}
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu context(this);

	QAction *reportAct = new QAction("&Report", this);
	connect(reportAct, SIGNAL(triggered()), this, SLOT(report()));
	context.addAction(reportAct);

	QAction *aboutAct = new QAction("&About", this);
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
	context.addAction(aboutAct);

	QAction *aboutQtAct = new QAction("About &Qt", this);
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	context.addAction(aboutQtAct);

	QAction *closeAct = new QAction("&Close", this);
	connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));
	context.addAction(closeAct);

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
	qDebug() << text;
	setStatusMessage("Status: Test failed");
	startButton->setText("Try again");
}

void MainWindow::testProgressed(const QString &testName,
	int /*testProgress*/, double currentSpeed)
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
	statusMessage->setText(QString("Status: %1").arg(str));
}

void MainWindow::clearStatusMessage()
{
	setStatusMessage("Ready");
}

void MainWindow::report() {
	ReportDialog *dialog = new ReportDialog(this);
	dialog->show();
}

void MainWindow::about() {}

