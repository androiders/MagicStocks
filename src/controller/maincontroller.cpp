#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{

}

void MainController::setStockModel(StockModel *model)
{
    mModel = model;
}

void MainController::setMainWindow(MainWindow *mw)
{
    mMw = mw;
}

void MainController::setYahooInterface(YahooInterface *yi)
{
    mYhi = yi;
}

void MainController::setStockDataFactory(StockDataFactory *sdf)
{
    mSdfac = sdf;
}

void MainController::setStockDataFileStorage(StockDataFileStorage *sdfs)
{
    mSdfs = sdfs;
}

bool MainController::connectAll()
{
    if(!mModel || !mMw || !mYhi || !mSdfac || !mSdfs)
        return false;

    mSdfac->setModel(mModel);

    //model yahho connections
    QObject::connect(mYhi,SIGNAL(stocksReady(QJsonArray)),mSdfac,SLOT(buildFromJsonArray(QJsonArray)));
    QObject::connect(mYhi,SIGNAL(stockHistoricalDataReady(QString,QJsonArray)),mSdfac,SLOT(buildHistoryFromJsonArray(QString,QJsonArray)));

    mMw->setTableModel(mModel);
//    mMw->>connectSearchField(mYhi);

    //search field connections to yahoo interface
    connect(mMw, SIGNAL(search(QString)),mYhi,SLOT(searchStocks(QString)));
    connect(mYhi,SIGNAL(stockSearchFailed(QString)),mMw,SLOT(searchFailed(QString)));
    connect(mYhi,SIGNAL(stockSearchReady(const QStringList & )),mMw,SLOT(searchReady(const QStringList & )));

    //update stocks signal
    connect(mMw,SIGNAL(updateStocks(bool)), this, SLOT(updateStocksHistory(bool)));

    //file system connections
    connect(mSdfs,SIGNAL(stocksReadReady(QJsonArray)),mSdfac,SLOT(buildFromJsonArray(QJsonArray)));
    connect(mSdfs,SIGNAL(stockHistoricalDataReadReady(QString,QJsonArray)),mSdfac,SLOT(buildHistoryFromJsonArray(QString,QJsonArray)));

    return true;
}

void MainController::getStockBySymbol(const QString & symbol)
{
    mYhi->getStockBySymbol(symbol);
}

bool MainController::saveIndex(const QString &fileName)
{
    return mSdfs->saveIndex(mModel,fileName);
}

bool MainController::loadIndex(const QString &fileName)
{
    return mSdfs->readIndex(fileName);
}

void MainController::updateStocksHistory(bool b)
{
    Q_UNUSED(b);

    QDate today = QDate::currentDate();
    QDate from = today.addYears(-1);

    for(int i = 0; i < mModel->rowCount(); ++i)
    {
        QString symb = mModel->getStockDataRef(i).symbol();
        mYhi->getHistoricalStockData(symb,from, today);
    }

}
