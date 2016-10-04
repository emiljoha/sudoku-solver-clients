#-------------------------------------------------
#
# Project created by QtCreator 2015-11-14T11:15:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sudoku
TEMPLATE = app
ICON = S_icon.icns


SOURCES += main.cpp\
           Main-Window.cpp\
           inputarea.cpp


HEADERS  += Main-Window.h\
            inputarea.h

DISTFILES += TODO.txt


LIBS += $$PWD/sudoku_solver.a

