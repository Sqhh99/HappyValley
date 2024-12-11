QT       += core gui
RC_ICONS += indicate.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adjacencylist.cpp \
    adjacencymatrix.cpp \
    loginwidget.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    adjacencylist.h \
    adjacencymatrix.h \
    loginwidget.h \
    widget.h

FORMS += \
    loginwidget.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    SCENIC SPOTS.txt

RESOURCES += \
    Icon.qrc
