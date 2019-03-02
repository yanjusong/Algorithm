QT += core
QT -= gui

CONFIG += c++11

TARGET = sort
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

DESTDIR = $$PWD/bin

INCLUDEPATH += sort

SOURCES += main.cpp \
    sort/bubble.c sort/quick.c sort/insert.c sort/merge.c sort/heap.c sort/select.c sort/shell.c sort/radix.c

HEADERS += \
    sort/easysort.h
