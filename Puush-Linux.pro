#-------------------------------------------------
#
# Project created by QtCreator 2015-10-01T07:16:50
#
#-------------------------------------------------

QT       += core gui phonon

CONFIG += qxt
QXT     += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Puush-Linux
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    shortcutreader.cpp \
    screenshotmanager.cpp \
    globalshortcut.cpp

HEADERS  += mainwindow.h \
    shortcutreader.h \
    screenshotmanager.h \
    globalshortcut.h

FORMS    += mainwindow.ui

RESOURCES += \
    rc.qrc
