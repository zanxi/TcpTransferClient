QT       += core gui sql xml network printsupport script
RC_ICONS = client.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Debug/data.cpp \
    Debug/datetime.cpp \
    Debug/logger.cpp \
    csv/csvfile.cpp \
    dataanimals.cpp \
    db/GenerateDB.cpp \
    db/SqlDataBase.cpp \
    db/database.cpp \
    dialog_viewphoto.cpp \
    extendqtablewidget.cpp \
    json/json_w.cpp \
    main.cpp \
    mainwindow.cpp \
    utils/Utils.cpp \
    utils/imageview.cpp \
    utils/qcustomplot.cpp

HEADERS += \
    Debug/data.h \
    Debug/datetime.h \
    Debug/logger.h \
    csv/csvfile.h \
    dataanimals.h \
    db/GenerateDB.h \
    db/SqlDataBase.h \
    db/database.h \
    dialog_viewphoto.h \
    extendqtablewidget.h \
    json/json_w.h \
    mainwindow.h \
    utils/Utils.h \
    utils/imageview.h \
    utils/qcustomplot.h

FORMS += \
    dialog_viewphoto.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
