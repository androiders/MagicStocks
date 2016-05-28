#ifndef STOCKDATAFACTORY_H
#define STOCKDATAFACTORY_H

#include <QObject>
#include "src/Stock/stockdata.h"
#include "src/Stock/stockmodel.h"
#include <QJsonArray>
#include <QJsonDocument>

class StockDataFactory : public QObject
{
    Q_OBJECT
public:
    explicit StockDataFactory(QObject *parent = 0);

    void setModel(StockModel * model);

    static const QJsonArray buildJsonFromStockData(const StockData * sd);

    static QJsonDocument buildJsonDockFromModel(const StockModel * model);

    static QString getSymbolString();

signals:

public slots:

    void buildFromJsonArray(const QJsonArray & array);

    void buildHistoryFromJsonArray(const QString & symbol, const QJsonArray & array);

private:

    StockHistoricalDataPoint createDataPoint(QString symbol,
                                             float closePrice,
                                             float open,
                                             float dayLow,
                                             float dayHigh,
                                             QDate &date,
                                             int volume);

    StockModel * mModel;
};

#endif // STOCKDATAFACTORY_H
