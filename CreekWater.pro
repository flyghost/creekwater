#-------------------------------------------------
#
# Project created by QtCreator 2018-11-05T16:16:39
#
#-------------------------------------------------

RC_ICONS = myico.ico

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CreekWater
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++11

INCLUDEPATH += $$PWD/CreekWater/code/mywidgets
INCLUDEPATH += $$PWD/CreekWater/code/core_app
INCLUDEPATH += $$PWD/CreekWater/code/hardware
INCLUDEPATH += $$PWD/CreekWater/code/model
INCLUDEPATH += $$PWD/CreekWater/code/package
INCLUDEPATH += $$PWD/CreekWater/code/framemain
INCLUDEPATH += $$PWD/CreekWater/code/framesetting
INCLUDEPATH += $$PWD/CreekWater/code/framebackstage
INCLUDEPATH += $$PWD/CreekWater/frame

include($$PWD/CreekWater/code/framemain/framemain.pri)
include($$PWD/CreekWater/code/framesetting/framesetting.pri)
include($$PWD/CreekWater/code/framebackstage/framebackstage.pri)
include($$PWD/CreekWater/code/mywidgets/mywidgets.pri)
include($$PWD/CreekWater/code/core_app/core_app.pri)
include($$PWD/CreekWater/code/hardware/hardware.pri)
include($$PWD/CreekWater/code/model/model.pri)
include($$PWD/CreekWater/code/package/package.pri)
include($$PWD/CreekWater/frame/frame.pri)

SOURCES += main.cpp

FORMS += framemain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/CreekWater/lib/ -lhidapi
INCLUDEPATH += $$PWD/CreekWater/lib
DEPENDPATH += $$PWD/CreekWater/lib

RESOURCES += \
    creekwater.qrc

DISTFILES += \
    CreekWater/code/framemain/framemain.pri \
    CreekWater/code/framemain/framemain.pri
