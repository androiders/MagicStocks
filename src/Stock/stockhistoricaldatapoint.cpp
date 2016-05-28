#include "stockhistoricaldatapoint.h"

StockHistoricalDataPoint::StockHistoricalDataPoint(QObject *parent)
    :QObject(parent)
    ,mSymbol("")
    ,mOpenPrice(0)
    ,mClosePrice(0)
    ,mDayHigh(0)
    ,mDayLow(0)
    ,mVolume(0)
    ,mSma200(0)
    ,mCurrent(0)
    ,mChange(0)
{

}

//StockHistoricalDataPoint::StockHistoricalDataPoint(QJsonObject jsonData, QObject *parent)
//    :QObject(parent)
//{
//    //mName = jsonData["Name"].toString();
//    mSymbol = jsonData["Symbol"].toString();
//    mClosePrice = (jsonData["Bid"].toString()).toFloat();
//    mCurrent = (jsonData["Bid"].toString()).toFloat();
//    mDayLow = (jsonData["DaysLow"].toString()).toFloat();
//    mDayHigh = (jsonData["DaysHigh"].toString()).toFloat();
//    mChange = (jsonData["Change"].toString()).toFloat();
//    mSma200 = (jsonData["TwoHundreddayMovingAverage"].toString()).toFloat();
//    //fiftyDayAverage = (jsonData["FiftydayMovingAverage"].toString()).toFloat();
//}

StockHistoricalDataPoint::StockHistoricalDataPoint(StockHistoricalDataPoint &&other)
{
    (*this) = other;
}

StockHistoricalDataPoint::StockHistoricalDataPoint(const StockHistoricalDataPoint &other)
    :QObject(other.parent())
    ,mSymbol(other.mSymbol)
    ,mOpenPrice(other.mOpenPrice)
    ,mClosePrice(other.mClosePrice)
    ,mDayHigh(other.mDayHigh)
    ,mDayLow(other.mDayLow)
    ,mVolume(other.mVolume)
    ,mSma200(other.mSma200)
    ,mCurrent(other.mCurrent)
    ,mChange(other.mChange)
    ,mDate(other.mDate)
{
}

float StockHistoricalDataPoint::openPrice() const
{
    return mOpenPrice;
}

void StockHistoricalDataPoint::setOpenPrice(float openPrice)
{
    mOpenPrice = openPrice;
}

float StockHistoricalDataPoint::closePrice() const
{
    return mClosePrice;
}

void StockHistoricalDataPoint::setClosePrice(float closePrice)
{
    mClosePrice = closePrice;
}

float StockHistoricalDataPoint::dayHigh() const
{
    return mDayHigh;
}

void StockHistoricalDataPoint::setDayHigh(float dayHigh)
{
    mDayHigh = dayHigh;
}

float StockHistoricalDataPoint::dayLow() const
{
    return mDayLow;
}

void StockHistoricalDataPoint::setDayLow(float dayLow)
{
    mDayLow = dayLow;
}

int StockHistoricalDataPoint::volume() const
{
    return mVolume;
}

void StockHistoricalDataPoint::setVolume(int volume)
{
    mVolume = volume;
}

//const QJsonObject &StockHistoricalDataPoint::toJsonObject() const
//{
////    Q_ASSERT(false);

//    QJsonObject obj;

//    //mName = jsonData["Name"].toString();
//    obj["Symbol"] = mSymbol;
////    mClosePrice = (jsonData["Bid"].toString()).toFloat();
////    mCurrent = (jsonData["Bid"].toString()).toFloat();
////    mDayLow = (jsonData["DaysLow"].toString()).toFloat();
////    mDayHigh = (jsonData["DaysHigh"].toString()).toFloat();
////    mChange = (jsonData["Change"].toString()).toFloat();
////    mSma200 = (jsonData["TwoHundreddayMovingAverage"].toString()).toFloat();

////    obj.insert("Symbol",mSymbol);
////    obj[""]

//    return obj;
//}

const StockHistoricalDataPoint StockHistoricalDataPoint::operator=(const StockHistoricalDataPoint &other)
{
    mSymbol = other.mSymbol;
    //QDate mDate;
    mOpenPrice = other.mOpenPrice;
    mClosePrice = other.mClosePrice;
    mDayHigh = other.mDayHigh;
    mDayLow = other.mDayLow;
    mVolume = other.mVolume;
    mSma200 = other.mSma200;
    mCurrent = other.mCurrent;
    mChange = other.mChange;
    mDate = other.mDate;
    mVolume = other.mVolume;

    return *this;
}

float StockHistoricalDataPoint::getSma200() const
{
    return mSma200;
}

void StockHistoricalDataPoint::setSma200(float value)
{
    mSma200 = value;
}

int StockHistoricalDataPoint::columnCount()
{
    return 7;
}

QString StockHistoricalDataPoint::getSymbol() const
{
    return mSymbol;
}

void StockHistoricalDataPoint::setSymbol(const QString &symbol)
{
    mSymbol = symbol;
}

QDate StockHistoricalDataPoint::getDate() const
{
    return mDate;
}

void StockHistoricalDataPoint::setDate(const QDate &date)
{
    mDate = date;
}

int StockHistoricalDataPoint::getVolume() const
{
    return mVolume;
}

//QJsonObject StockHistoricalDataPoint::toJsonObject() const
//{
//    QJsonObject obj;
//    obj.insert()
//}

