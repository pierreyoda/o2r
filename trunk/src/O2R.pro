#-------------------------------------------------
#
# Project created by QtCreator 2012-05-30T16:05:57
#
#-------------------------------------------------

QT       += core gui

TARGET = O2R
TEMPLATE = app

INCLUDEPATH += "F:/Prog/LIBS/SFML - Qt build/include/"
win32:LIBS += -L"F:/Prog/LIBS/SFML - Qt build/lib"
LIBS += -lsfml-system -lsfml-window -lsfml-graphics


SOURCES += main.cpp\
        MainWindow.cpp \
    GameCanvas.cpp \
    QSfmlCanvas.cpp

HEADERS  += MainWindow.hpp \
    GameCanvas.hpp \
    QSfmlCanvas.hpp

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
