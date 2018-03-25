TEMPLATE=app

QT -= gui
QT += core

CONFIG += link_pkgconfig

PKGCONFIG += libwbxml2 libxml-2.0

LIBS += -lreadline
INCLUDEPATH += /usr/include/readline

HEADERS=\
  cmd-options.h \
  rl-controller.h \
  cmd-controller.h

SOURCES=\
  main.cpp \
  cmd-options.cpp \
  rl-controller.cpp \
  cmd-controller.cpp
