#-------------------------------------------------
#
# Project created by QtCreator 2018-12-13T11:35:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShopmServerManager
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

win32:CONFIG(release, debug|release) {
    # WINDOWS RELEASE
    PRE_TARGETDEPS += $$OUT_PWD/../qqrencode/release/qtqrencode.dll
    LIBS += -L$$OUT_PWD/../qqrencode/release/ -lqtqrencode

} else:win32:CONFIG(debug, debug|release) {
    # WINDOWS DEBUG
    PRE_TARGETDEPS += $$OUT_PWD/../qqrencode/debug/qtqrencode.dll
    LIBS += -L$$OUT_PWD/../qqrencode/debug/ -lqtqrencode
} else:CONFIG(release, debug|release) {
    PRE_TARGETDEPS += $$OUT_PWD/../qqrencode/libqtqrencode.so
    LIBS += -L$$OUT_PWD/../qqrencode/ -lqtqrencode
} else:CONFIG(debug, debug|release) {
    PRE_TARGETDEPS += $$OUT_PWD/../qqrencode/libqtqrencode.so
    LIBS += -L$$OUT_PWD/../qqrencode/ -lqtqrencode
}

INCLUDEPATH += $$PWD/../qqrencode
DEPENDPATH += $$PWD/../qqrencode
