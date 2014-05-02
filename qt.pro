TEMPLATE = app
TARGET = speedtest
DEPENDPATH += .
INCLUDEPATH += .

QT += widgets webkitwidgets

HEADERS = speedmeter.h mainwindow.h basetest.h webtest.h speedofmetest.h
SOURCES = main.cpp speedmeter.cpp mainwindow.cpp webtest.cpp speedofmetest.cpp

