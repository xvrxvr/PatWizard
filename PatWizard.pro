#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T15:41:35
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PatWizard
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        wizardscene.cpp \
        GeometrySolver/gemetrysolver.cpp \


HEADERS  += mainwindow.h \
    gr_object.h \
    NetListReader/inp_def.h \
    wizardscene.h \
    GeometrySolver/gemetrysolver.h \


FORMS    += mainwindow.ui

CONFIG += c++11

DISTFILES += \
    constrains.xlsx
