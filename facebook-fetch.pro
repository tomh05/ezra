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
    messagesparser.cpp \
    encryptor.cpp

HEADERS  += \
    fbwizard.h \
    intropage.h \
    fileselectpage.h \
    parsepage.h \
    messagesparser.h \
    encryptor.h

QT += webkit webkitwidgets



win32 {
 LIBS += -lqca-gnupg
}
macx {
QMAKE_LFLAGS += -F/Users/tomh/Programming/coot/facebook/facebook-fetch/libs/mac/

#LIBS += -F$$PWD/libs/mac/ -framework qca
LIBS += -F/usr/local/lib -framework qca-qt5
#INCLUDEPATH += $$PWD/libs/mac/qca.framework/Headers
INCLUDEPATH += /usr/local/lib/qca-qt5.framework/Versions/2.1.1/Headers
DEPENDPATH += $$PWD/libs/mac

#QMAKE_LFLAGS += -F./libs/mac/
}

CONFIG += crypto
