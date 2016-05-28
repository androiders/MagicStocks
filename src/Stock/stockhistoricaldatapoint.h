#ifndef STOCKHISTORICALDATAPOINT_H
#define STOCKHISTORICALDATAPOINT_H

#include <QObject>
#include <QJsonObject>
#include <QString>
#include <QDate>

class StockHistoricalDataPoint : public QObject
{
    Q_OBJECT
public:
    StockHistoricalDataPoint(QObject * parent = 0);

    //explicit StockHistoricalDataPoint(QJsonObject data, QObject *parent = 0);
    StockHistoricalDataPoint(StockHistoricalDataPoint && other);
    StockHistoricalDataPoint(const StockHistoricalDataPoint & other);

    float openPrice() const;
    void setOpenPrice(float openPrice);

    float closePrice() const;
    void setClosePrice(float closePrice);

    float dayHigh() const;
    void setDayHigh(float dayHigh);

    float dayLow() const;
    void setDayLow(float dayLow);

    int volume() const;
    void setVolume(int volume);

    //const QJsonObject & toJsonObject() const;

    const StockHistoricalDataPoint operator=(const StockHistoricalDataPoint & other);

    float getSma200() const;
    void setSma200(float value);

    static int columnCount();

    //QJsonObject toJsonObject() const;

    QString getSymbol() const;
    void setSymbol(const QString &symbol);

    QDate getDate() const;
    void setDate(const QDate &date);

    int getVolume() const;

signals:

public slots:

private:

    QString mSymbol;

    //    QString mName;
    //QDate mDate;

    float mOpenPrice;

    float mClosePrice;

    float mDayHigh;

    float mDayLow;

    float mSma200;

    int mVolume;

    float mCurrent;

    float mChange;

    QDate mDate;
};

#endif // STOCKHISTORICALDATAPOINT_H
