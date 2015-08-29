#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T12:56:45
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        client.cpp \
    scene.cpp

HEADERS  += client.h \
    scene.h

LIBS += -lGLU
