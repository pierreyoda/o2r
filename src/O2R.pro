#-------------------------------------------------
#
# Project created by QtCreator 2012-05-30T16:05:57
#
#-------------------------------------------------

QT       += core gui xml

TARGET = O2R
TEMPLATE = app

INCLUDEPATH += "F:/Prog/LIBS/SFML - Qt build/include/"
win32:LIBS += -L"F:/Prog/LIBS/SFML - Qt build/lib"
CONFIG( debug, debug|release ) {
LIBS += -lsfml-system-d -lsfml-window-d -lsfml-graphics-d
}  else {
LIBS += -lsfml-system -lsfml-window -lsfml-graphics
}

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
    dialogs/AboutDialog.cpp \
    managers/AssetsManager.cpp \
    managers/TilesTypesManager.cpp \
    factories/TiledMapFactory.cpp \
    map/LevelInfo.cpp \
    game/Screen.cpp \
    game/GameScreen.cpp \
    game/EditorScreen.cpp \
    game/EmptyScreen.cpp \
    dialogs/EditorLevelPropertiesDialog.cpp \
    entities/Cat.cpp \
    map/TiledMapPathfinder.cpp \
    map/micropather/micropather.cpp \
    dialogs/ModsDialog.cpp \
    dialogs/AvailableModsDialog.cpp \
    entities/Trap.cpp

HEADERS  += MainWindow.hpp \
    GameCanvas.hpp \
    QSfmlCanvas.hpp \
    entities/TiledEntity.hpp \
    entities/Tile.hpp \
    entities/Mouse.hpp \
    map/TiledMap.hpp \
    managers/FilespathProvider.hpp \
    dialogs/AboutDialog.hpp \
    managers/AssetsManager.hpp \
    managers/TilesTypesManager.hpp \
    factories/TiledMapFactory.hpp \
    map/LevelInfo.hpp \
    game/Screen.hpp \
    game/GameScreen.hpp \
    game/EditorScreen.hpp \
    game/EmptyScreen.hpp \
    dialogs/EditorLevelPropertiesDialog.hpp \
    entities/Cat.hpp \
    map/TiledMapPathfinder.hpp \
    map/micropather/micropather.h \
    dialogs/ModsDialog.hpp \
    dialogs/AvailableModsDialog.hpp \
    entities/Trap.hpp

FORMS    += MainWindow.ui \
    dialogs/AboutDialog.ui \
    dialogs/EditorLevelPropertiesDialog.ui \
    dialogs/ModsDialog.ui \
    dialogs/AvailableModsDialog.ui

TRANSLATIONS = o2r_fr.ts

RESOURCES += resources.qrc
