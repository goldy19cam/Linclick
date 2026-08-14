#fichier de configuration qmake et se cree automatiquement avec le projet
QT +=  core gui sql widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    formwindow.cpp \
    linkswindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    formwindow.h \
    linkswindow.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

DISTFILES += \
    Readme.md
