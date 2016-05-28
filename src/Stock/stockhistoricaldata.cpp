#include "stockhistoricaldata.h"


//StockHistoricalData::StockHistoricalData(const QJsonArray &data, QObject *parent) : QObject(parent)
//{
//    setData(data);
//    for(int i = 0; i < data.size(); ++i)
//    {
//        mDataPoints.append(data.at(i).toObject());
//    }

//    calculateAndAddSMA("SMA200", 200);
//    calculateAndAddSMA("SMA50", 50);

//}

StockHistoricalData::StockHistoricalData(const StockHistoricalData &other)
    :QObject(other.parent())
{
    mDataPoints = other.mDataPoints;
}

StockHistoricalData::StockHistoricalData(StockHistoricalData &&other)
    :QObject(other.parent())
{
    mDataPoints = other.mDataPoints;
}

int StockHistoricalData::columnCount() const
{
    return StockHistoricalDataPoint::columnCount();
}

//void StockHistoricalData::setData(const QJsonArray &data)
//{
//    for(int i = 0; i < data.size(); ++i)
//    {
//        StockHistoricalDataPoint dataPoint(data.at(i).toObject());
//        mDataPoints.append(dataPoint);
//    }

////    calculateAndAddSMA("SMA200", 200);
////    calculateAndAddSMA("SMA50", 50);

//}

void StockHistoricalData::addData(StockHistoricalDataPoint &shdp)
{
    mDataPoints.append(shdp);
}

//StockHistoricalData &StockHistoricalData::operator==(StockHistoricalData &&rhs)
//{
//    mDataPoints = rhs.mDataPoints;
//}

//StockHistoricalData &StockHistoricalData::operator==(StockHistoricalData &rhs)
//{
//    mDataPoints = rhs.mDataPoints;
//}


int StockHistoricalData::size() const
{
    return mDataPoints.size();
}

//const QJsonObject & StockHistoricalData::getData(int index) const
//{
//    return mDataPoints.at(index).toJsonObject();
//}

const StockHistoricalDataPoint & StockHistoricalData::getDataPoint(int index) const
{
    return mDataPoints.at(index);
}


const StockHistoricalDataPoint & StockHistoricalData::operator[](int index) const
{
    return getDataPoint(index);
}

const StockHistoricalData & StockHistoricalData::operator=(const StockHistoricalData &other)
{
    mDataPoints = other.mDataPoints;
    return (*this);
}

//QJsonArray StockHistoricalData::getLabels(int nrOfLabels) const
//{
//    int limit = nrOfLabels > mDataPoints.size() ? mDataPoints.size() : nrOfLabels;
//    QJsonArray arr;
//    for(int i = 0; i < limit; ++i){
//        arr.append(getDateString(i));
//    }

//    return arr;

//}

//QJsonArray StockHistoricalData::getValues(int nrOfObjects) const
//{
//    int limit = nrOfObjects > mDataPoints.size() ? mDataPoints.size() : nrOfObjects;
//    QJsonArray arr;
//    for(int i = 0; i < limit; ++i){
////        QJsonObject obj = mDataPoints.at(i);
//        QJsonValue val = getClosingPrice(mDataPoints.size() -1 - i);
//        arr.append(val);
//    }

//    return arr;
//}

//float StockHistoricalData::getClosingPrice(int index) const
//{
//    QJsonObject obj = mDataPoints.at(index);
//    float price = obj.value("Adj_Close").toString().toFloat();
//    return price;
//}

//QString StockHistoricalData::getDateString(int index) const
//{
//    QJsonObject obj = mDataPoints.at(index);
//    QString date = obj.take("Date").toString();
//    return date;
//}

//void StockHistoricalData::calculateAndAddSMA(const QString & key, int sma)
//{
//    if(mDataPoints.size() < sma)
//    {
//        return;
//    }
//    float smal = 0;

//    for(int i = 0; i < mDataPoints.size() - sma; ++i)
//    {
//        smal = 0;
//        for(int m = 0; m < sma; ++m)
//        {
//            smal += getClosingPrice(i + m );
//        }
//        smal /= (float)sma;
//        mDataPoints[i].insert(key,smal);
//    }

//    //fill in the remaining  fake sma
//    for(int i = mDataPoints.size() - sma; i < mDataPoints.size(); ++i)
//    {
//         mDataPoints[i].insert(key,getClosingPrice(i));
//    }
//}

