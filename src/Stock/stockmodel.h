#ifndef STOCKMODEL_H
#define STOCKMODEL_H

#include <QList>
#include <QHash>
#include <QAbstractTableModel>

class StockData; //declared in stockdata.h

class StockModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    StockModel(QObject *parent = 0);

    ~StockModel(){}

public slots:

    QHash<int, QByteArray> roleNames() const;

    QVariantMap get(int row) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    int columnCount(const QModelIndex &parent) const;
    int	rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


    StockData * getStockData(const QModelIndex & index);

    StockData * getStockData(const QString & symbol);

    const StockData & getStockDataRef(int i) const;

//    QHash<int, QByteArray> roleNames() const;

    void addData(StockData * data);

//    void setHistoricalData(const QString & symbol, const QJsonArray & data);

signals:

    void historicalDataUpdated(const QString & symbol);

private:

    static QHash<int,QByteArray> sHeaderRoleNames;

    QList<StockData*> mStockList;
};

#endif // STOCKMODEL_H
