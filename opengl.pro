QT += core gui widgets opengl openglwidgets
QT += network
QT += sql
CONFIG += c++17
QT += 3dcore 3drender 3dextras


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    miwidget.cpp

HEADERS += mainwindow.h \
    miwidget.h

FORMS += mainwindow.ui
LIBS += -lOpengl32
DISTFILES += \
    ../proj/qtw_open/zzstar.frag \
    ../proj/qtw_open/star.vert

