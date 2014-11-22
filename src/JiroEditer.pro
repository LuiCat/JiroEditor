#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T14:39:21
#
#-------------------------------------------------

QT += gui opengl widgets

TARGET = JiroEditer
TEMPLATE = app

QMAKE_LFLAGS += -static-libgcc
QMAKE_LFLAGS += -static-libstdc++

SOURCES += \
	main.cpp \
    qoggvorbis.cpp \
	soundeffects.cpp \
    soundbuffer.cpp \
	soundcore.cpp \
	gltextureloader.cpp \
	notify.cpp \
    jiroediter.cpp

HEADERS  += \
    qoggvorbis.h \
	soundeffects.h \
    soundbuffer.h \
	soundcore.h \
	gltextureloader.h \
    notify.h \
    jiroediter.h

RESOURCES += \
	resource.qrc

OTHER_FILES += \
	icon.ico

DEFINES += _WIN32

LIBS += \
    $${_PRO_FILE_PWD_}/libVorbisFile_win32.a \
    $${_PRO_FILE_PWD_}/libVorbis_win32.a \
    $${_PRO_FILE_PWD_}/libOgg_win32.a \
    $${_PRO_FILE_PWD_}/dsound.lib

