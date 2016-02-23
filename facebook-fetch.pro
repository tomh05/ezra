#-------------------------------------------------
#
# Project created by QtCreator 2016-02-15T15:15:57
#
#-------------------------------------------------

QT       += core gui

#DEPENDPATH += . botan
#INCLUDEPATH += . botan
#include(botan/Botan.pri)


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = facebook-fetch
TEMPLATE = app


SOURCES += main.cpp\
    fbwizard.cpp \
    intropage.cpp \
    fileselectpage.cpp \
    parsepage.cpp \
    messagesparser.cpp \
    encryptor.cpp \
    uploader.cpp \
    pageserver.cpp \
    #botan/botan.cpp \
    explainerpage.cpp \
    whitelist.cpp

HEADERS  += \
    fbwizard.h \
    intropage.h \
    fileselectpage.h \
    parsepage.h \
    messagesparser.h \
    encryptor.h \
    uploader.h \
    pageserver.h \
    #botan/botan.h \
    explainerpage.h \
    whitelist.h

QT += webkit webkitwidgets

#CONFIG += crypto


#win32 {
# LIBS += -lqca-gnupg
#}
#macx {

#LIBS += -F$$PWD/libs/mac/ -framework qca
#LIBS += -F/usr/local/lib -framework qca-qt5
#LD_LIBRARY_PATH += /usr/local/lib/qca-qt5
#INCLUDEPATH += /usr/local/lib/qca-qt5.framework/Versions/2.1.1/Headers
#DEPENDPATH += $$PWD/libs/mac

#QMAKE_LFLAGS += -F./libs/mac/
#}

RESOURCES += \
    res.qrc
