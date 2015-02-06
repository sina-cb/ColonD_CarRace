#-------------------------------------------------
#
# Project created by QtCreator 2015-02-06T00:52:39
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ColonD_CarRace
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../Box2D_v2.1.2/Box2D
LIBS += -L ../Box2D_v2.1.2/Box2D/Build/Box2D
LIBS += -lBox2D

LIBS += -lGL -lglut

SOURCES += main.cpp \

HEADERS += \
