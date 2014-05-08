#-------------------------------------------------
#
# Project created by QtCreator 2014-05-08T20:55:18
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = cv3_hello
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += C:\OpenCV249\build\include C:\OpenCV249\build\include\opencv
LIBS += -LC:\OpenCV249\build\x86\vc10\lib


CONFIG(debug, debug|release) {
    LIBS += -lopencv_core249d \
    -lopencv_highgui249d \
} else {
    LIBS += -lopencv_core249 \
    -lopencv_highgui249 \

}
