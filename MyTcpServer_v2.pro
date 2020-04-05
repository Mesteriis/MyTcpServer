QT       += core gui network

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
    gui/clickablelabel.cpp \
    gui/clientitemonform.cpp \
    gui/popup.cpp \
    gui/stat.cpp \
    gui/switchwithid.cpp \
    main.cpp \
    gui/guicore.cpp \
    sys/client.cpp \
    sys/rng.cpp \
    sys/swcore.cpp \
    sys/worker.cpp

HEADERS += \
    gui/clickablelabel.hpp \
    gui/clientitemonform.hpp \
    gui/guicore.hpp \
    gui/popup.hpp \
    gui/stat.hpp \
    gui/switchwithid.hpp \
    sys/client.hpp \
    sys/rng.hpp \
    sys/swcore.hpp \
    sys/worker.hpp

FORMS += \
    gui/guicore.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/resources.qrc

ICON = $${PWD}/res/server.icns

VERSION = 2.0.0

QMAKE_TARGET_COMPANY = "Shade Inc"
QMAKE_TARGET_PRODUCT = MyTcpServer
QMAKE_TARGET_DESCRIPTION = Simpli Tcp Server graf
QMAKE_TARGET_COPYRIGHT = AVM
