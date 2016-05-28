#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QObject>
#include <QPair>
#include <QNetworkAccessManager>
#include <QMap>
#include <QNetworkReply>

typedef QPair<QString,QString> DataPair;

struct RequestData
{
    QString url;
    QList<DataPair> requestParams;
};

class RestClient : public QObject
{
    Q_OBJECT
public:
    explicit RestClient(QObject *parent = 0);

    unsigned int requestGet(RequestData & req);


signals:

    void requestReady(QString networkReply, unsigned int requestId);

public slots:

    void requestFinished(QNetworkReply * reply);

    QMap<QString,QString> parseNetworkReply(QString &networkReply);


private:

    QString requestDataToString(RequestData & data);


    unsigned int mRequestCnt;
    QNetworkAccessManager manager;

    QHash<QNetworkReply*,unsigned int> mReplayIdMap;


};

#endif // RESTCLIENT_H
