#-------------------------------------------------
#
# Project created by QtCreator 2016-09-04T16:52:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app


SOURCES += main.cpp\
    GameScene.cpp \
    MainSurface.cpp \
    Block.cpp \
    Cell.cpp \
    BlockScene.cpp

HEADERS  += \
    GameScene.h \
    MainSurface.h \
    Block.h \
    Cell.h \
    BlockScene.h

FORMS    += widget.ui
