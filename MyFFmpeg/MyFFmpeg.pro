QT += core gui dtkwidget

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyFFmpeg
TEMPLATE = app

SOURCES += \
        main.cpp \
    ui/mymainwindow.cpp \
    ui/myplaylistwidget.cpp \
    ui/myplaywidget.cpp \
    ui/myvideotranscodewidget.cpp \
    ui/myvideoframewidget.cpp \
    ui/mycaptionrecognitionwidget.cpp
    action/myplaylist.cpp \

RESOURCES +=         resources.qrc

HEADERS += \
    ui/mymainwindow.h \
    ui/myplaylistwidget.h \
    ui/myplaywidget.h \
    ui/myvideotranscodewidget.h \
    ui/myvideoframewidget.h \
    ui/mycaptionrecognitionwidget.h
    action/myplaylist.h \
