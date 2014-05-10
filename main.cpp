#include <QApplication>
#include "mainwindow.h"
#include "results.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	app.setOrganizationName("LinOxide");
	app.setOrganizationDomain("linoxide.com");
	app.setApplicationName("Speedtest");

	qRegisterMetaTypeStreamOperators<ResultsRecord>("ResultsRecord");

	MainWindow mw;
	mw.show();

	return app.exec();
}
