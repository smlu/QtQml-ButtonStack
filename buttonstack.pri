QT += core gui widgets quickwidgets

lessThan(QT_MAJOR_VERSION, 5) | lessThan(QT_MINOR_VERSION, 3): error("Current Qt version is $$QT_VERSION, it must be at least 5.3.")

INCLUDEPATH+=src

RESOURCES += \
    src/buttonstack.qrc

HEADERS += \
    $$PWD/src/stackbutton.h \
    $$PWD/src/buttonstackwidget.h

SOURCES += \
    $$PWD/src/buttonstackwidget.cpp
