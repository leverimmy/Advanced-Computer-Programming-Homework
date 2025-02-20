QT += core gui widgets testlib

TARGET = lab2-test
TEMPLATE = app

CONFIG += c++11 testcase

SOURCES += \
    src/test/GameTest.cpp \
    src/core/Game.cpp \
    src/core/Ball.cpp \
    src/core/BallList.cpp \
    src/core/Path.cpp \
    src/core/Shooter.cpp \
    src/core/CollisionSystem.cpp

HEADERS += \
    src/core/Game.h \
    src/core/Ball.h \
    src/core/BallList.h \
    src/core/Path.h \
    src/core/Shooter.h \
    src/core/CollisionSystem.h \
    src/core/Parameter.h

INCLUDEPATH += \
    src \
    src/core

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
