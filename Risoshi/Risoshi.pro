#-------------------------------------------------
#
# Project created by QtCreator 2013-02-14T14:45:42
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Risoshi
TEMPLATE = app

QMAKE_CXXFLAGS += -Wno-invalid-offsetof

SOURCES += main.cpp\
        mainwindow.cpp \
    rtabwidget.cpp \
    models.cpp \
    raddwidget.cpp \
    rtableview.cpp

HEADERS  += mainwindow.h \
    rtabwidget.h \
    models.h \
    raddwidget.h \
    rtableview.h

FORMS    += mainwindow.ui \
    rtabwidget.ui \
    raddwidget.ui







win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../dquest/release/ -ldquest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../dquest/debug/ -ldquest
else:symbian: LIBS += -ldquest
else:unix: LIBS += -L$$OUT_PWD/../dquest/ -ldquest

INCLUDEPATH += $$PWD/../dquest
DEPENDPATH += $$PWD/../dquest

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../dquest/release/dquest.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../dquest/debug/dquest.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../dquest/libdquest.a


