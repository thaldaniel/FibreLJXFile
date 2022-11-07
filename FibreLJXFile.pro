QT += core
TEMPLATE = lib
DEFINES += FIBRELJXFILE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fibreljxfile.cpp \
    ljsettings.cpp

HEADERS += \
    FibreLJXFile_global.h \
    fibreljxfile.h \
    ljsettings.h \
    ljsettings_structs.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LC:/opencv/build/x64/vc15/lib/ -lopencv_world454
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv/build/x64/vc15/lib/ -lopencv_world454d
else:unix: LIBS += -LC:/opencv/build/x64/vc15/lib/ -lopencv_world454

INCLUDEPATH += C:/opencv/build/include
DEPENDPATH += C:/opencv/build/include

DISTFILES += \
    FibreLJXFileFormat.txt
