#ifndef STOCKDATA_H
#define STOCKDATA_H

#include <QObject>
#include <QVariant>
#include <QString>
//#include <QtQml>
#include <QJsonObject>
#include "stockhistoricaldata.h"

class StockData : public QObject
{
    Q_OBJECT
   // Q_ENUMS(PriceChange)

    //Q_PROPERTY(QString name READ name WRITE setName)
//    Q_PROPERTY(float currentPrice READ getCurrentPrice WRITE setCurrentPrice NOTIFY currentPriceChanged)

public:
    StockData(const QString & name, const QString & symbol, QObject *parent = 0);

    ~StockData(){}

//    StockData(const QJsonObject & jsonData);

//    StockData(const StockData & other);

//    enum PriceChange
//    {
//        NO_CHANGE = 0,
//        CHANGE_UP,
//        CHANGE_DOWN
//    };

public:

    int columntCount() const;

    void setName(const QString &value);
    void setSymbol(const QString & symbol);

    double getLatestClosingPrice() const;

    double getLatestHighestPrice() const;

    double getLatestLowestPrice() const;

    double getLatestOpeningPrice() const;

    double getLatestSMA200() const;

    QDate getDate() const;

//    void setCurrentPrice(float value);

//    void setHighest(float value);

//    void setLowest(float value);

//    void setChange(float pChange);

    QString name() const;
    QString symbol() const;
//    float getCurrentPrice() const;
//    float getHighest() const;
//    float getLowest() const;
//    float getPriceChange() const;
//    QString currency() const;
//    float getTwoHundredDayAverage() const;
//    float getFiftyDayAverage() const;

    void setHistoricalData(const StockHistoricalData & data);
    int getHistoricalSize() const;

    const StockHistoricalDataPoint & getHistoricalData(int index) const;

//    const QVariant &operator[](std::size_t idx) const;
//    QVariant &operator[](std::size_t idx);

    const QVariant getValueByIndex(std::size_t idx) const;

signals:

    void currentPriceChanged();

public slots:

//    QJsonArray getLabels(int size) const;

//    QJsonArray getValues(int size) const;

private:

    QString mName;
    QString mSymbol;

//    float currentPrice;
//    float dayLow;
//    float dayHigh;

//    float change;

//    float twoHundredDayAverage;
//    float  fiftyDayAverage;

//    QString mCurrency;

    StockHistoricalData mHistoricalData;
};

//Q_DECLARE_METATYPE(StockData*)
//Q_DECLARE_METATYPE(StockData::PriceChange)
//QML_DECLARE_TYPE(StockData*)
//QML_DECLARE_TYPE(StockData::PriceChange)




#endif // STOCKDATA_H
