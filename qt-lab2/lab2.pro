QT       += core gui widgets

TARGET = lab2
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/core/Game.cpp \
    src/core/BallList.cpp \
    src/core/Ball.cpp \
    src/core/Path.cpp \
    src/core/Shooter.cpp \
    src/core/CollisionSystem.cpp \
    src/ui/MainWindow.cpp \
    src/ui/GameWidget.cpp \
    src/ui/ScoreBoard.cpp

HEADERS += \
    src/core/BallList.h \
    src/core/Game.h \
    src/core/Ball.h \
    src/core/Path.h \
    src/core/Shooter.h \
    src/core/CollisionSystem.h \
    src/ui/MainWindow.h \
    src/ui/GameWidget.h \
    src/ui/ScoreBoard.h

INCLUDEPATH += \
    src \
    src/core \
    src/ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
