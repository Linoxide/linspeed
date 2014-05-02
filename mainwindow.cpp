#include <QGridLayout>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	download = new SpeedMeter("Download");
	upload = new SpeedMeter("Upload");

	startButton = new QPushButton("Start");

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(startButton, 0, 0, 1, 2);
	layout->addWidget(download, 1, 0);
	layout->addWidget(upload, 1, 1);

	QWidget *central = new QWidget;
	central->setLayout(layout);

	this->setCentralWidget(central);
}

void MainWindow::startClicked()
{

}
