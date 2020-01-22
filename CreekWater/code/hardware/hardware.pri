

#INCLUDEPATH += $$PWD/qextserialport
##INCLUDEPATH += $$PWD/usbhid


##HEADERS += \
##        $$PWD/usbhid/hidapi.h  \
##        $$PWD/usbhid/usbhid.h
           
##SOURCES +=  \
##        $$PWD/usbhid/usbhid.cpp


#HEADERS += \
#    $$PWD/qextserialport/qextserialport.h \
#    $$PWD/qextserialport/qextserialport_global.h \
#    $$PWD/qextserialport/qextserialport_p.h \
#    $$PWD/qextserialport/myhelper.h

#SOURCES += $$PWD/qextserialport/qextserialport.cpp

#win32:SOURCES += $$PWD/qextserialport/qextserialport_win.cpp
#unix:SOURCES += $$PWD/qextserialport/qextserialport_unix.cpp


## 添加动态扫描串口
##HEADERS += \
##    $$PWD/qextserialport/qextserialenumerator.h \
##    $$PWD/qextserialport/qextserialenumerator_p.h

##SOURCES += $$PWD/qextserialport/qextserialenumerator.cpp

##win32:SOURCES += $$PWD/qextserialport/qextserialenumerator_win.cpp
##unix:SOURCES += $$PWD/qextserialport/qextserialenumerator_unix.cpp






INCLUDEPATH += $$PWD/qextserialport
DEPENDPATH += $$PWD/qextserialport

PUBLIC_HEADERS         += $$PWD/qextserialport/qextserialport.h \
                          $$PWD/qextserialport/qextserialenumerator.h \
                          $$PWD/qextserialport/qextserialport_global.h

HEADERS                += $$PUBLIC_HEADERS \
                          $$PWD/qextserialport/qextserialport_p.h \
                          $$PWD/qextserialenumerator_p.h \

SOURCES                += $$PWD/qextserialport/qextserialport.cpp \
                          $$PWD/qextserialport/qextserialenumerator.cpp
unix {
    SOURCES            += $$PWD/qextserialport/qextserialport_unix.cpp
    linux* {
        SOURCES        += $$PWD/qextserialport/qextserialenumerator_linux.cpp
    } else:macx {
        SOURCES        += $$PWD/qextserialport/qextserialenumerator_osx.cpp
    } else {
        SOURCES        += $$PWD/qextserialport/qextserialenumerator_unix.cpp
    }
}
win32:SOURCES          += $$PWD/qextserialport/qextserialport_win.cpp \
                          $$PWD/qextserialport/qextserialenumerator_win.cpp

linux*{
    !qesp_linux_udev:DEFINES += QESP_NO_UDEV
    qesp_linux_udev: LIBS += -ludev
}

macx:LIBS              += -framework IOKit -framework CoreFoundation
win32:LIBS             += -lsetupapi -ladvapi32 -luser32

# moc doesn't detect Q_OS_LINUX correctly, so add this to make it work
linux*:DEFINES += __linux__

