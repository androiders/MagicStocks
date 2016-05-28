#ifndef STOCKDATAFILESTORAGE_H
#define STOCKDATAFILESTORAGE_H

#include <QObject>
#include <QJsonArray>
#include "src/Stock/stockdata.h"
#include "src/Stock/stockmodel.h"

class StockDataFileStorage : public QObject
{
    Q_OBJECT
public:
    explicit StockDataFileStorage(QObject *parent = 0);

signals:

    void stocksReadReady(const QJsonArray & stocks);

    void stockHistoricalDataReadReady(const QString & symbol, const QJsonArray & stockData);

public slots:

    bool saveIndex(const StockModel * model, const QString & indexName);
    bool saveStockData(const StockData * data);
    bool saveStockData(const QString & symbol, const QString & jsonData);
    bool saveStockData(const QString & symbol, const QJsonArray & jsonData);
    bool saveStockData(const QString & dirPath, const QString & symbol, const QString & jsonData);

    bool readIndex(const QString & indexFileName);

    bool readStockData(const QString & dir, const QString & symbol);

private:

    QString getHomeFilePath(const QString & fileName);

};

#endif // STOCKDATAFILESTORAGE_H
