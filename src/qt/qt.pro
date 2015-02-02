TEMPLATE = app

QT += qml quick widgets bluetooth core

SOURCES += main.cpp \
    parking.cpp \
    communication.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    parking.h \
    communication.h

CONFIG += mobility

MOBILITY =

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += android/AndroidManifest.xml

