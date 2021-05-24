QT += dtkgui5.5
QT += dtkwidget5.5
QT += core multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyFFmpeg
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        main.cpp \
    ui/mymainwindow.cpp \
    ui/myplaylistwidget.cpp \
    ui/myplaywidget.cpp \
    ui/myvideotranscodewidget.cpp \
    ui/myvideoframewidget.cpp \
    ui/mycaptionrecognitionwidget.cpp \
    action/myplaylist.cpp \
    action/myplayengine.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    ui/mymainwindow.h \
    ui/myplaylistwidget.h \
    ui/myplaywidget.h \
    ui/myvideotranscodewidget.h \
    ui/myvideoframewidget.h \
    ui/mycaptionrecognitionwidget.h \
    action/myplaylist.h \
    action/myplayengine.h

LIBS += -lavformat -lavdevice -lavcodec -lavutil -lpthread -lswscale -lswresample -lz
