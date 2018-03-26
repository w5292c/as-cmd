TEMPLATE=app

QT -= gui
QT += core

CONFIG += link_pkgconfig

PKGCONFIG += libwbxml2 libxml-2.0

LIBS += -lreadline
INCLUDEPATH += /usr/include/readline

HEADERS=\
  cmd-base.h \
  cmd-help.h \
  cmd-options.h \
  cmd-unknown.h \
  rl-controller.h \
  cmd-controller.h

SOURCES=\
  main.cpp \
  cmd-base.cpp \
  cmd-help.cpp \
  cmd-options.cpp \
  cmd-unknown.cpp \
  rl-controller.cpp \
  cmd-controller.cpp
