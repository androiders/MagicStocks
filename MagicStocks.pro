#-------------------------------------------------
#
# Project created by QtCreator 2016-05-01T16:56:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = MagicStocks
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/Stock/stockdata.cpp \
    src/Stock/stockhistoricaldata.cpp \
    src/Stock/stockmodel.cpp \
    src/Stock/stockhistoricaldatapoint.cpp \
    src/fs/stockdatafilestorage.cpp \
    src/factories/stockdatafactory.cpp \
    src/net/oauthclient.cpp \
    src/net/restclient.cpp \
    src/net/yahoointerface.cpp \
    src/controller/maincontroller.cpp \
    src/qcustomplot/qcustomplot.cpp \
    customplotdialog.cpp

HEADERS  += mainwindow.h \
    src/Stock/stockdata.h \
    src/Stock/stockhistoricaldata.h \
    src/Stock/stockmodel.h \
    src/Stock/stockhistoricaldatapoint.h \
    src/fs/stockdatafilestorage.h \
    src/factories/stockdatafactory.h \
    src/net/oauthclient.h \
    src/net/restclient.h \
    src/net/yahoointerface.h \
    src/controller/maincontroller.h \
    src/qcustomplot/qcustomplot.h \
    customplotdialog.h

FORMS    += mainwindow.ui \
    customplotdialog.ui
