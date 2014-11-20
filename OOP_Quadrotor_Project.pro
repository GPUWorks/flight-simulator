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
    renderingcontroller.cpp \
    physicscontroller.cpp \
    globjectfactory.cpp \
    landscapefactory.cpp \
    glcamerasimulation.cpp \
    landscapeobject.cpp \
    registry.cpp \
    lib/qcustomplot.cpp \
    glcamera.cpp

HEADERS  += controlwindow.h \
    graphwidget.h \
    camglwidget.h \
    maincontroller.h \
    registry.h \
    renderingcontroller.h \
    physicscontroller.h \
    globject.h \
    globjectfactory.h \
    landscapefactory.h \
    glcamerasimulation.h \
    glcamera.h \
    landscapeobject.h \
    lib/qcustomplot.h

FORMS    += controlwindow.ui
