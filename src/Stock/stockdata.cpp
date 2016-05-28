#include "stockdata.h"


StockData::StockData(const QString & name, const QString & symbol, QObject *parent)
    : QObject(parent)
    ,mName(name)
    ,mSymbol(symbol)
{

}

int StockData::columntCount() const
{
    return mHistoricalData.columnCount();
}

//StockData::StockData(const QJsonObject &jsonData)
//{
//    mName = jsonData["Name"].toString();
//    mSymbol = jsonData["Symbol"].toString();
//    currentPrice = (jsonData["Bid"].toString()).toFloat();
//    dayLow = (jsonData["DaysLow"].toString()).toFloat();
//    dayHigh = (jsonData["DaysHigh"].toString()).toFloat();
//    change = (jsonData["Change"].toString()).toFloat();

//    twoHundredDayAverage = (jsonData["TwoHundreddayMovingAverage"].toString()).toFloat();
//    fiftyDayAverage = (jsonData["FiftydayMovingAverage"].toString()).toFloat();

//}

//StockData::StockData(const StockData &other)
//    :QObject(0)
//{
//    mName = other.mName;
//    currentPrice = other.currentPrice;
////    lowest = 0.0f;
////    highest = 500.0f;
//}

QString StockData::name() const
{
    return mName;
}

void StockData::setName(const QString &value)
{
    mName = value;
}

void StockData::setSymbol(const QString &symbol)
{
    mSymbol = symbol;
}

double StockData::getLatestClosingPrice() const
{
    if(mHistoricalData.size() == 0)
        return 0;

    return mHistoricalData[0].closePrice();
}

double StockData::getLatestHighestPrice() const
{
    if(mHistoricalData.size() == 0)
        return 0;

    return mHistoricalData[0].dayHigh();
}

double StockData::getLatestLowestPrice() const
{
    if(mHistoricalData.size() == 0)
        return 0;

    return mHistoricalData[0].dayLow();
}

double StockData::getLatestOpeningPrice() const
{
    if(mHistoricalData.size() == 0)
        return 0;

    return mHistoricalData[0].openPrice();
}

double StockData::getLatestSMA200() const
{
    if(mHistoricalData.size() == 0)
        return 0;

    return mHistoricalData[0].getSma200();
}

QDate StockData::getDate() const
{
    if(mHistoricalData.size() == 0)
        return QDate();

    return mHistoricalData[0].getDate();
}

QString StockData::symbol() const
{
    return mSymbol;
}

//float StockData::getCurrentPrice() const
//{
//    return currentPrice;
//}

//void StockData::setCurrentPrice(float value)
//{
//    currentPrice = value;
//}

//float StockData::getHighest() const
//{
//    return dayHigh;
//}

//void StockData::setHighest(float value)
//{
//    dayHigh = value;
//}

//float StockData::getLowest() const
//{
//    return dayLow;
//}

//float  StockData::getPriceChange() const
//{
//    return change;
//}

//QString StockData::currency() const
//{
//    return mCurrency;
//}

//float StockData::getTwoHundredDayAverage() const
//{
//    return twoHundredDayAverage;
//}

//float StockData::getFiftyDayAverage() const
//{
//    return fiftyDayAverage;
//}

void StockData::setHistoricalData(const StockHistoricalData &data)
{
    mHistoricalData = data;
}

int StockData::getHistoricalSize() const
{
    return mHistoricalData.size();
}

const StockHistoricalDataPoint &StockData::getHistoricalData(int index) const
{
    return mHistoricalData[index];
}

//const QVariant &StockData::operator[](std::size_t idx) const
//{
//    return getValueByIndex(idx);
//}

//QVariant &StockData::operator[](std::size_t idx)
//{
//    return const_cast<QVariant&>(getValueByIndex(idx));
//}

const QVariant StockData::getValueByIndex(std::size_t idx) const
{
    switch(idx)
    {
    case 0:
        return QVariant::fromValue(mName);
        break;
    case 1:
        return QVariant::fromValue(mSymbol);
        break;
    case 2:
        return QVariant::fromValue(getLatestOpeningPrice());
        break;
    case 3:
        return QVariant::fromValue(getLatestHighestPrice());
        break;
    case 4:
        return QVariant::fromValue(getLatestLowestPrice());
        break;
    case 5:
        return QVariant::fromValue(getLatestClosingPrice());
        break;
//    case 6:
//        return QVariant::fromValue(getLatestSMA200());
//        break;
    case 6:
        return QVariant::fromValue(getDate());
        break;
//    case 8:
//        return QVariant::fromValue(mCurrency);
//        break;
    default:
        return QVariant();
    }
}

//QJsonArray StockData::getLabels(int size) const
//{
//    return mHistoricalData.getLabels(size);
//}


//QJsonArray StockData::getValues(int size) const
//{
//    return mHistoricalData.getValues(size);

//}

//void StockData::setLowest(float value)
//{
//    dayLow = value;
//}

//void StockData::setChange(float pChange)
//{
//    change = pChange;
//}

//QString StockData::symbol() const
//{
//    return mSymbol;
//}

