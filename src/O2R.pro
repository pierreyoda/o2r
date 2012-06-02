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

include(QsLog/QsLog.pri)


SOURCES += main.cpp\
        MainWindow.cpp \
    GameCanvas.cpp \
    QSfmlCanvas.cpp \
    entities/TiledEntity.cpp \
    entities/Tile.cpp \
    entities/Mouse.cpp \
    map/TiledMap.cpp \
    managers/FilespathProvider.cpp \
    dialogs/AboutDialog.cpp

HEADERS  += MainWindow.hpp \
    GameCanvas.hpp \
    QSfmlCanvas.hpp \
    entities/TiledEntity.hpp \
    entities/Tile.hpp \
    entities/Mouse.hpp \
    map/TiledMap.hpp \
    managers/FilespathProvider.hpp \
    dialogs/AboutDialog.hpp

FORMS    += MainWindow.ui \
    dialogs/AboutDialog.ui

TRANSLATIONS = o2r_fr.ts

RESOURCES += resources.qrc
