#include(../common.pri)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets gui

SOURCES += $$PWD/qtsingleapplication.cpp $$PWD/qtlocalpeer.cpp
HEADERS += $$PWD/qtsingleapplication.h $$PWD/qtlocalpeer.h
