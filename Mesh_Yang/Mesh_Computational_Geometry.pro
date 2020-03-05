#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T10:55:17
#
#-------------------------------------------------

QT       += core gui opengl
@CONFIG += c++11@
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mesh_Computational_Geometry
TEMPLATE = app


SOURCES += main.cpp\
    face.cpp \
    gradient.cpp \
        mainwindow.cpp \
    gldisplaywidget.cpp \
    mesh.cpp \
    vertex.cpp

HEADERS  += mainwindow.h \
    face.h \
    gldisplaywidget.h \
    gradient.h \
    mesh.h \
    vertex.h

FORMS    += mainwindow.ui

#---- Comment the following line on MacOS
# LIBS = -lGLU
LIBS += -lglu32
LIBS += -lOpengl32

