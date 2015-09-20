#-------------------------------------------------
#
# Project created by QtCreator 2015-07-08T14:34:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibraryMaster
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    manager.cpp \
    user.cpp \
    visitor.cpp \
    dbhelper.cpp \
    querybookdialog.cpp \
    addbookdialog.cpp \
    usersetdialog.cpp

HEADERS  += mainwindow.h \
    manager.h \
    user.h \
    visitor.h \
    dbhelper.h \
    querybookdialog.h \
    addbookdialog.h \
    usersetdialog.h

FORMS    += mainwindow.ui \
    manager.ui \
    user.ui \
    visitor.ui \
    querybookdialog.ui \
    addbookdialog.ui \
    usersetdialog.ui

RESOURCES += \
    bkg1.qrc
