#include <QDebug>
#include <QGridLayout>
#include <QSizePolicy>
#include <QStatusBar>
#include "mainwindow.h"

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
	sbar->showMessage("Click Begin Test");
	this->setStatusBar(sbar);

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

}

void MainWindow::testSucceeded(double download_speed,
	double upload_speed)
{
	this->download->setValue(download_speed);
	this->upload->setValue(upload_speed);

	this->statusBar()->showMessage("Test succeeded");
	startButton->setText("Begin Test");
}

void MainWindow::testFailed(const QString& text)
{
	qDebug() << text;
	this->statusBar()->showMessage("Test failed");
	startButton->setText("Try again");
}

void MainWindow::testProgressed(const QString &testName,
	int testProgress, double currentSpeed)
{
	QString msg = "%1 progress: %2%";
	msg = msg.arg(testName).arg(testProgress);
	if(testName=="download")
		this->download->setValue(currentSpeed);
	else if(testName=="upload")
		this->upload->setValue(currentSpeed);
	this->statusBar()->showMessage(msg);
}


void MainWindow::testStarted()
{
	this->statusBar()->showMessage("Test running");
	startButton->setText("Cancel");
}
