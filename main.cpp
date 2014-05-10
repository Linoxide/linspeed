#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	app.setOrganizationName("LinOxide");
	app.setOrganizationDomain("linoxide.com");
	app.setApplicationName("Speedtest");

	MainWindow mw;
	mw.show();

	return app.exec();
}
