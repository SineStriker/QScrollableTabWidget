QT       += core gui core-private widgets-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Visual/QCommandPalette.cpp \
    Visual/QCommandPaletteItem.cpp \
    Visual/QCommandPalette_p.cpp \
    Visual/QScrollableTabBar.cpp \
    Visual/QScrollableTabBarTab.cpp \
    Visual/QScrollableTabBarTab_p.cpp \
    Visual/QScrollableTabBar_p.cpp \
    Visual/QScrollableTabWidget.cpp \
    Visual/QScrollableTabWidget_p.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    Visual/QCommandPalette.h \
    Visual/QCommandPaletteItem.h \
    Visual/QCommandPalette_p.h \
    Visual/QScrollableTabBar.h \
    Visual/QScrollableTabBarTab.h \
    Visual/QScrollableTabBarTab_p.h \
    Visual/QScrollableTabBar_p.h \
    Visual/QScrollableTabWidget.h \
    Visual/QScrollableTabWidget_p.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/res.qrc
