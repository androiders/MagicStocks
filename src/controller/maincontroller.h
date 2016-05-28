#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "src/Stock/stockmodel.h"
#include "src/net/yahoointerface.h"
#include "src/factories/stockdatafactory.h"
#include "src/fs/stockdatafilestorage.h"
#include "mainwindow.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = 0);

    void setStockModel(StockModel * model);

    void setMainWindow(MainWindow * mw);

    void setYahooInterface(YahooInterface * yi);

    void setStockDataFactory(StockDataFactory * sdf);

    void setStockDataFileStorage(StockDataFileStorage * sdfs);

    bool connectAll();

    bool saveIndex(const QString & fileName);

    bool loadIndex(const QString & fileName);

signals:

public slots:

    void getStockBySymbol(const QString &symbol);



private slots:

    void updateStocksHistory(bool b);

private:

    StockModel * mModel;

    YahooInterface * mYhi;

    MainWindow * mMw;

    StockDataFactory * mSdfac;

    StockDataFileStorage * mSdfs;
};

#endif // MAINCONTROLLER_H
