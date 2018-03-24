TEMPLATE=app

QT -= gui
QT += core

CONFIG += link_pkgconfig

PKGCONFIG += libwbxml2 libxml-2.0

LIBS += -lreadline
INCLUDEPATH += /usr/include/readline

HEADERS=

SOURCES=\
  main.cpp
