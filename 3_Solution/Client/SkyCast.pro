QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cexceptie.cpp \
    cuser.cpp \
    getweather.cpp \
    iexceptie.cpp \
    irequest.cpp \
    iuser.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    normaluser.cpp \
    requestback.cpp \
    requestcity.cpp \
    requestlogin.cpp \
    requestlogout.cpp \
    requestregister.cpp \
    signin.cpp \
    skycast.cpp \
    tcpclient.cpp

HEADERS += \
    cexceptie.h \
    cuser.h \
    getweather.h \
    iexceptie.h \
    irequest.h \
    iuser.h \
    login.h \
    mainwindow.h \
    normaluser.h \
    requestback.h \
    requestcity.h \
    requestlogin.h \
    requestlogout.h \
    requestregister.h \
    signin.h \
    skycast.h \
    tcpclient.h

FORMS += \
    login.ui \
    mainwindow.ui \
    signin.ui \
    skycast.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
