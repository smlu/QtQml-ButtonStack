QT += core gui widgets quickwidgets

lessThan(QT_VERSION, 5.3): error("Current Qt version is $$QT_VERSION, it must be at least 5.3.")

TARGET = qtqml_buttonstack
TEMPLATE = app

RESOURCES += \
    resource.qrc

HEADERS += \
    buttonstack.h

SOURCES += \
    buttonstack.cpp \
    main.cpp
