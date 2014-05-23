TEMPLATE = app
TARGET = linspeed
DEPENDPATH += .
INCLUDEPATH += .

QT = core gui webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

HEADERS = speedmeter.h mainwindow.h basetest.h webtest.h speedofmetest.h \
	debugpage.h results.h reportdialog.h theme.h
SOURCES = main.cpp speedmeter.cpp mainwindow.cpp webtest.cpp speedofmetest.cpp \
	debugpage.cpp results.cpp reportdialog.cpp theme.cpp
RESOURCES = themes/themes.qrc

target.path =   $$PREFIX/bin
target.files = $$TARGET
sources.files = qt.pro $$SOURCES $$HEADERS $$RESOURCES $$FORMS
INSTALLS += target

