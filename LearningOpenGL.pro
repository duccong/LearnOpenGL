#-------------------------------------------------
#
# Project created by QtCreator 2020-05-13T10:42:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LearningOpenGL
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    openglwindow.cpp \
    hellotriangle.cpp \
    shader.cpp \
    textures.cpp \
    transform.cpp \
    coordinatesystems.cpp

HEADERS += \
    openglwindow.h \
    hellotriangle.h \
    shader.h \
    textures.h \
    transform.h \
    coordinatesystems.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    3.3.shader.vs \
    3.3.shader.fs \
    5.1.transform.fs \
    5.1.transform.vs \
    wall.jpg \
    container.jpg \
    3.4.textures.fs \
    3.4.textures.vs \
    test.PNG \
    test2.PNG \
    5.1.transform.vs \
    5.1.transform.fs \
    6.1.coordinate_systems.fs \
    6.1.coordinate_systems.vs
