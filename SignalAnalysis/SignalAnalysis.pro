#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T13:36:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SignalAnalysis
TEMPLATE = app


SOURCES +=\
        MainWindow.cpp \
    Main.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

win32: LIBS += -L$$PWD/../Portaudio/ -lportaudio_x86

INCLUDEPATH += $$PWD/../Portaudio
DEPENDPATH += $$PWD/../Portaudio

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../release/ -lGuitarSori
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../debug/ -lGuitarSori
else:unix: LIBS += -L$$PWD/../ -lGuitarSori

INCLUDEPATH += $$PWD/../Debug
DEPENDPATH += $$PWD/../Debug
