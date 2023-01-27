QT += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    createrecord.cpp \
    main.cpp \
    model.cpp \
    piece.cpp \
    piecescollector.cpp \
    createtable.cpp \
    jsondata.cpp \
    linechart.cpp \
    barchart.cpp \
    piechart.cpp \
    donutchart.cpp \
    view.cpp \
    controller.cpp \
    pointchart.cpp


HEADERS += \
    createrecord.h \
    model.h \
    piece.h \
    piecescollector.h \
    createtable.h \
    jsondata.h \
    graph.h \
    linechart.h \
    barchart.h \
    piechart.h \
    donutchart.h \
    view.h \
    controller.h \
    pointchart.h


FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

