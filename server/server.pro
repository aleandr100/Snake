#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T17:37:44
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    block.cpp \
    food.cpp \
    client.cpp \
    snake.cpp \
    tcpserver.cpp \
    game.cpp

HEADERS += \
    block.h \
    food.h \
    client.h \
    snake.h \
    tcpserver.h \
    game.h
