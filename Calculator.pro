#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T20:22:17
#
#-------------------------------------------------

QT       += core
CONFIG += c++14
CONFIG += c++11

QT       -= gui

TARGET = Calculator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    parser.cpp \
    helper.cpp \
    expression.cpp \
    logical.cpp \
    primary.cpp \
    relation.cpp

HEADERS += \
    parser.h \
    helper.h \
    expression.h \
    logical.h \
    primary.h \
    relation.h
