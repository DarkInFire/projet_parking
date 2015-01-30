TEMPLATE = app

QT += qml quick widgets bluetooth core androidextras

SOURCES += main.cpp \
    parking.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    parking.h

CONFIG += mobility

MOBILITY =

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += android/AndroidManifest.xml

