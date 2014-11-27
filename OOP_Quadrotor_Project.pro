#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T17:15:22
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = OOP_Quadrotor_Project
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        controlwindow.cpp \
    graphwidget.cpp \
    camglwidget.cpp \
    maincontroller.cpp \
    physicscontroller.cpp \
    globjectfactory.cpp \
    landscapefactory.cpp \
    landscapeobject.cpp \
    registry.cpp \
    lib/qcustomplot.cpp \
    glcamera.cpp \
    glcamera3rdperson.cpp \
    glcamera1stperson.cpp \
    gllight.cpp \
    quadrotorfactory.cpp \
    quadrotorobject.cpp

HEADERS  += controlwindow.h \
    graphwidget.h \
    camglwidget.h \
    maincontroller.h \
    registry.h \
    physicscontroller.h \
    globject.h \
    globjectfactory.h \
    landscapefactory.h \
    glcamera.h \
    landscapeobject.h \
    lib/qcustomplot.h \
    glcamera3rdperson.h \
    glcamera1stperson.h \
    gllight.h \
    quadrotorfactory.h \
    quadrotorobject.h

FORMS    += controlwindow.ui

OTHER_FILES += \
    landscape.vert.glsl \
    landscape.frag.glsl \
    quadrotor.vert.glsl \
    quadrotor.frag.glsl

RESOURCES += \
    res.qrc
