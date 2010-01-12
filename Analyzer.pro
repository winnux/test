# -------------------------------------------------
# Project created by QtCreator 2010-01-05T19:38:42
# -------------------------------------------------
# include (examples.pri)
# CONFIG(release, debug|release)
# :LIBS += -lqwtd5
# else:LIBS += -lqwt5
CONFIG += release
TARGET = Analyzer
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    data_plot.cpp \
    mywidget.cpp \
    setdialog.cpp \
    pages.cpp
HEADERS += mainwindow.h \
    data_plot.h \
    mywidget.h \
    setdialog.h \
    pages.h
FORMS += mainwindow.ui

# win32
# {
# INCLUDEPATH += c:\projects\qwt-5.2.0\src
# LIBS += c:\projects\qwt-5.2.0\lib\libqwt5.a
# }
# unix
# {
INCLUDEPATH += /home/lihaibo/dev/qwt-5.2.0/src
LIBS += /home/lihaibo/dev/qwt-5.2.0/lib/libqwt.so
RESOURCES += Analyzer.qrc
