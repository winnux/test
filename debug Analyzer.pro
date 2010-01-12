# -------------------------------------------------
# Project created by QtCreator 2010-01-05T19:38:42
# -------------------------------------------------
# include (examples.pri)
# CONFIG(release, debug|release)
# :LIBS += -lqwtd5
# else:LIBS += -lqwt5
CONFIG += debug
TARGET = Analyzer
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    data_plot.cpp \
    mywidget.cpp \
    setdialog.cpp
HEADERS += mainwindow.h \
    data_plot.h \
    mywidget.h \
    setdialog.h
FORMS += mainwindow.ui \
    setdialog.ui
INCLUDEPATH += c:\projects\qwt-5.2.0\src
LIBS += c:\projects\qwt-5.2.0\lib\libqwtd5.a
