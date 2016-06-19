#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T10:37:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = CPPython
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += C++11
TEMPLATE = app


SOURCES += main.cpp

HEADERS += \
    os/path.hpp \
    os.hpp \
    string.hpp \
    util.hpp \
    builtin.hpp
