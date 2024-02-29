QT       += core gui sql
QT += quick


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connexion.cpp \
    fournisseurs.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    connexion.h \
    fournisseurs.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qml/Plugins-master/README.md \
    qml/Plugins-master/android_armv7/QmlioFirebase/debug/libqmlioFirebase.so \
    qml/Plugins-master/android_armv7/QmlioFirebase/plugins.qmltypes \
    qml/Plugins-master/android_armv7/QmlioFirebase/qmldir \
    qml/Plugins-master/android_armv7/QmlioFirebase/release/libqmlioFirebase.so \
    qml/Plugins-master/android_armv7/QmlioNative/libqmlioNative.so \
    qml/Plugins-master/android_armv7/QmlioNative/plugin.qmltypes \
    qml/Plugins-master/android_armv7/QmlioNative/qmldir \
    qml/Plugins-master/mainwindow.qml \
    qml/Plugins-master/mingw32/QmlioFirebase/a \
    qml/Plugins-master/mingw32/QmlioFirebase/plugin.qmltypes \
    qml/Plugins-master/mingw32/QmlioFirebase/qmldir \
    qml/Plugins-master/mingw32/QmlioFirebase/qmlioFirebase.dll \
    qml/Plugins-master/mingw32/QmlioFirebase/qmlioFirebased.dll \
    qml/Plugins-master/mingw32/QmlioNative/a \
    qml/Plugins-master/mingw32/QmlioNative/plugin.qmltypes \
    qml/Plugins-master/mingw32/QmlioNative/qmldir \
    qml/Plugins-master/mingw32/QmlioNative/qmlioNative.dll \
    qml/Plugins-master/mingw32/QmlioNative/qmlioNatived.dll \
    qml/Plugins-master/msvc2017 x64/QmlioFirebase/plugin.qmltypes \
    qml/Plugins-master/msvc2017 x64/QmlioFirebase/qmldir \
    qml/Plugins-master/msvc2017 x64/QmlioFirebase/qmlioFirebase.dll \
    qml/Plugins-master/msvc2017 x64/QmlioFirebase/qmlioFirebased.dll \
    qml/Plugins-master/msvc2017 x64/QmlioNative/plugin.qmltypes \
    qml/Plugins-master/msvc2017 x64/QmlioNative/qmldir \
    qml/Plugins-master/msvc2017 x64/QmlioNative/qmlioNative.dll \
    qml/Plugins-master/msvc2017 x64/QmlioNative/qmlioNatived.dll
