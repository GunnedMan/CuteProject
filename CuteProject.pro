QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GmGame/GmDatabase/GmDatabase.cpp \
    GmGame/GmGame.cpp \
    GmGame/GmGameUpdateTimer.cpp \
    GmGame/GmGrafix/GmGameScene.cpp \
    GmGame/GmGrafix/GmGameScreen.cpp \
    GmGame/GmGrafix/GmGrafix.cpp \
    GmGame/GmGrafix/GmUiIndicatorBar.cpp \
    GmGame/GmInput/GmInput.cpp \
    GmGame/GmPhysObject/GmPhysObject.cpp \
    GmGame/GmPhysObject/GmPlayerShip.cpp \
    GmGame/GmUtility.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GmGame/GmDatabase/GmDatabase.h \
    GmGame/GmGame.h \
    GmGame/GmGameUpdateTimer.h \
    GmGame/GmGrafix/GmGameScene.h \
    GmGame/GmGrafix/GmGameScreen.h \
    GmGame/GmGrafix/GmGrafix.h \
    GmGame/GmGrafix/GmUiIndicatorBar.h \
    GmGame/GmInput/GmInput.h \
    GmGame/GmPhysObject/GmPhysObject.h \
    GmGame/GmPhysObject/GmPlayerShip.h \
    GmGame/GmUtility.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

QMAKE_LFLAGS += -static

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    gmGrafix/todo.txt
