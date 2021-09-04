QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutwindow.cpp \
    begingamewindow.cpp \
    gamewindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    aboutwindow.h \
    begingamewindow.h \
    gamewindow.h \
    mainwindow.h

FORMS += \
    aboutwindow.ui \
    begingamewindow.ui \
    gamewindow.ui \
    mainwindow.ui

TRANSLATIONS += \
    monopoly_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourses.qrc

DISTFILES += \
    ../build-monopoly-Desktop_Qt_6_0_3_MinGW_64_bit-Release/list_players.txt \
    monopoly-preview-1920x1440px-1920_auto_x2_colored_light_ai.png \
    monopoly_area.PNG
