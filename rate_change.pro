QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#工程所使用的模版;app表示是应用程序;lib则表明是库
TEMPLATE=app

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

#临时文件存放位置
MOC_DIR         = $$PWD/build/moc  #指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录
RCC_DIR         = $$PWD/build/rcc  #指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录
UI_DIR          = $$PWD/build/ui   #指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录
OBJECTS_DIR     = $$PWD/build/obj  #指定目标文件(obj)的存放目录

CONFIG(release, release | debug ){
    DESTDIR += $$PWD/bin/release
}else{
    DESTDIR += $$PWD/bin/debug
}

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
