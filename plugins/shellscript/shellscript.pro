include ("../../global.pri")
include ("../plugins.pri")

CONFIG   += plugin
TARGET = shellscript
TEMPLATE = lib

HEADERS += shellscript.h
SOURCES += shellscript.cpp

INCLUDEPATH += ../../src/
DESTDIR = ../