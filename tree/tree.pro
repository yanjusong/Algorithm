TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    bst.c \
    tree.c \
    avl.c \
    rb.c \
    deque.c \
    test_traveltree.c

HEADERS += \
    bst.h \
    tree.h \
    avl.h \
    rb.h \
    deque.h
