TEMPLATE=app

QT -= gui
QT += core
QT += network

CONFIG += link_pkgconfig

PKGCONFIG += libwbxml2 libxml-2.0

LIBS += -lreadline
INCLUDEPATH += /usr/include/readline

HEADERS=\
  as-env.h \
  cmd-base.h \
  cmd-help.h \
  cmd-options.h \
  cmd-unknown.h \
  cmd-verbose.h \
  cmd-sync-key.h \
  rl-controller.h \
  cmd-controller.h \
  network-manager.h \
  cmd-folder-sync.h

SOURCES=\
  main.cpp \
  as-env.cpp \
  cmd-base.cpp \
  cmd-help.cpp \
  cmd-options.cpp \
  cmd-unknown.cpp \
  cmd-verbose.cpp \
  cmd-sync-key.cpp \
  rl-controller.cpp \
  cmd-controller.cpp \
  network-manager.cpp \
  cmd-folder-sync.cpp
