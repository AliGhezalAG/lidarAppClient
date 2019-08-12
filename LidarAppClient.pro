#-------------------------------------------------
#
# Project created by QtCreator 2019-08-07T10:26:55
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LidarAppClient
TEMPLATE = app


SOURCES += main.cpp \
    fenclient.cpp

HEADERS  += FenClient.h

FORMS    += FenClient.ui
