# -------------------------------------------------
# Project created by QtCreator 2010-01-05T19:38:42
# -------------------------------------------------
VER_MAJ      = 1
VER_MIN      = 0
VER_PAT      = 0
VERSION      = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

#CONFIG += release
TARGET = Analyzer
DESTDIR = bin
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
RESOURCES += Analyzer.qrc
win32{
    INCLUDEPATH += c:\projects\qwt-5.2.0\src
    win32:release{
        LIBS += C:\projects\qwt-5.2.0\lib\libqwt.a
    }
    else{
        LIBS += C:\projects\qwt-5.2.0\lib\libqwtd.a
    }
}
unix{
    INCLUDEPATH += /home/lihaibo/dev/qwt-5.2.0/src
    LIBS += /home/lihaibo/dev/qwt-5.2.0/lib/libqwt.a
}
