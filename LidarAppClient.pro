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
    fenclient.cpp \
    header.cpp \
    object.cpp \
    objectpacket.cpp \
    shape.cpp \
    triplet.cpp \
    vertice.cpp \
    zone.cpp \
    zonepacket.cpp

HEADERS  += FenClient.h \
    header.h \
    object.h \
    objectpacket.h \
    shape.h \
    triplet.h \
    vertice.h \
    zone.h \
    zonepacket.h

FORMS    += FenClient.ui
