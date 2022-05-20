QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battery.cpp \
    capacitor.cpp \
    customscene.cpp \
    customview.cpp \
    element.cpp \
    inductor.cpp \
    main.cpp \
    mainwindow.cpp \
    resistor.cpp \
    settingsdialog.cpp \
    wire.cpp

HEADERS += \
    battery.h \
    capacitor.h \
    customscene.h \
    customview.h \
    element.h \
    inductor.h \
    mainwindow.h \
    resistor.h \
    settingsdialog.h \
    wire.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
