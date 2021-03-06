QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += /Users/brycecallender/Downloads/build-qt-material-widgets-Desktop_Qt_5_12_5_clang_64bit-Release/components/libcomponents.a
INCLUDEPATH += $$top_srcdir/QtMaterialDesign/

SOURCES += \
    controlwordmanager.cpp \
    creationdialog.cpp \
    jsonpreview.cpp \
    main.cpp \
    mainwindow.cpp \
    startwindow.cpp \
    settingsmanager.cpp

HEADERS += \
    ControlWord.h \
    GridLayoutUtil.h \
    Instruction.h \
    InstructionSet.h \
    controlwordmanager.h \
    creationdialog.h \
    jsonpreview.h \
    mainwindow.h \
    startwindow.h \
    settingsmanager.h

FORMS += \
    creationdialog.ui \
    jsonpreview.ui \
    mainwindow.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
