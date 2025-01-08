QT += core widgets statemachine

TEMPLATE = app

TARGET = myapp

CONFIG += c++21

SOURCES += \
        main.cpp

RESOURCES += \
    assets.qrc

# Enable pkg-config
CONFIG += link_pkgconfig

# Specify the OpenCV package
PKGCONFIG += opencv4

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
