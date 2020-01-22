HEADERS += \
    $$PWD/qextserialport.h \
    $$PWD/qextserialport_global.h \
    $$PWD/qextserialport_p.h \
    $$PWD/frmcomtool.h \
    $$PWD/myhelper.h
           
SOURCES += $$PWD/qextserialport.cpp \
           $$PWD/frmcomtool.cpp

win32:SOURCES += $$PWD/qextserialport_win.cpp
unix:SOURCES += $$PWD/qextserialport_unix.cpp
