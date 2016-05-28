#ifndef STOCKHISTORICALDATA_H
#define STOCKHISTORICALDATA_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include "stockhistoricaldatapoint.h"

class StockHistoricalData : public QObject
{
    Q_OBJECT
public:
    StockHistoricalData(QObject * parent = 0)
        :QObject(parent){}


    explicit StockHistoricalData(const QJsonArray & data, QObject *parent = 0);

    explicit StockHistoricalData(const StockHistoricalData & other);

    explicit StockHistoricalData(StockHistoricalData && other);

    int columnCount() const;

    //void setData(const QJsonArray & data);

    void addData(StockHistoricalDataPoint & shdp);



//    StockHistoricalData & operator==(StockHistoricalData && rhs);
//    StockHistoricalData & operator==(StockHistoricalData &rhs);

    const StockHistoricalDataPoint & operator[](int index) const;

    const StockHistoricalData & operator=(const StockHistoricalData & other);

signals:

public slots:

    int size() const;

    //const QJsonObject & getData(int index) const;

    const StockHistoricalDataPoint & getDataPoint(int index) const;



    /**
     * @brief getLabels returns a list of labels constructed from the dates for each data point
     * @param nrOfLabels the nr of datapoints to return from the latest and backwards
     * @return an json array of strings of dates
     */
    //QJsonArray getLabels(int nrOfLabels = 0) const;

    /**
     * @brief getValues returns the nr of datapoints from the latest and backwards
     * @param nrOfObjects the nr of datapoints  to return
     * @return a json array of data
     */
    //QJsonArray getValues(int nrOfObjects = 0) const;

    //float getClosingPrice(int index) const;

    //QString getDateString(int index) const;

private:

    void calculateAndAddSMA(const QString &key, int sma);

    QVector<StockHistoricalDataPoint> mDataPoints;
};

#endif // STOCKHISTORICALDATA_H
