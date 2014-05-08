TEMPLATE = app
TARGET = speedtest
DEPENDPATH += .
INCLUDEPATH += .

QT = core gui webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

HEADERS = speedmeter.h mainwindow.h basetest.h webtest.h speedofmetest.h debugpage.h
SOURCES = main.cpp speedmeter.cpp mainwindow.cpp webtest.cpp speedofmetest.cpp debugpage.cpp

