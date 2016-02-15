#-------------------------------------------------
#
# Project created by QtCreator 2016-02-15T15:15:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = facebook-fetch
TEMPLATE = app


SOURCES += main.cpp\
    fbwizard.cpp \
    intropage.cpp \
    fileselectpage.cpp \
    parsepage.cpp \
    messagesparser.cpp

HEADERS  += \
    fbwizard.h \
    intropage.h \
    fileselectpage.h \
    parsepage.h \
    messagesparser.h

FORMS    += mainwindow.ui

QT += webkit webkitwidgets
