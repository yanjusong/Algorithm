TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    bst.c \
    tree.c \
    avl.c \
    rb.c \
    test_rb.c

HEADERS += \
    bst.h \
    tree.h \
    avl.h \
    rb.h
