# MIT License
#
# Copyright (c) 2018 Alexander Chumakov
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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
  cmd-prop.h \
  cmd-sync.h \
  cmd-options.h \
  cmd-unknown.h \
  cmd-verbose.h \
  rl-controller.h \
  cmd-controller.h \
  network-manager.h \
  cmd-folder-sync.h

SOURCES=\
  main.cpp \
  as-env.cpp \
  cmd-base.cpp \
  cmd-help.cpp \
  cmd-prop.cpp \
  cmd-sync.cpp \
  cmd-options.cpp \
  cmd-unknown.cpp \
  cmd-verbose.cpp \
  rl-controller.cpp \
  cmd-controller.cpp \
  network-manager.cpp \
  cmd-folder-sync.cpp
