#include "restclient.h"
#include <QUrl>


RestClient::RestClient(QObject *parent)
:QObject(parent)
,mRequestCnt(0)
{
    connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(requestFinished(QNetworkReply*)));
}

unsigned int RestClient::requestGet(RequestData &req)
{
    mRequestCnt++;
    QUrl u(requestDataToString(req));
 //   qDebug() << "url: " << u;
    QNetworkRequest request(u);
    QSslConfiguration config = request.sslConfiguration();
    config.setProtocol(QSsl::SslV3);
    request.setSslConfiguration(config);
    QNetworkReply * r = manager.get(request);
    mReplayIdMap.insert(r,mRequestCnt);
    return mRequestCnt;
}


QString RestClient::requestDataToString(RequestData &data)
{
    QString str = data.url + "?";
    QPair<QString,QString> p;
    foreach (p, data.requestParams) {
        str+= p.first + "=" + p.second + "&";
    }
    return str;
}

QMap<QString,QString> RestClient::parseNetworkReply(QString & networkReply)
{
    QMap<QString,QString> answer;
    QString data = networkReply;
    QStringList variables = data.split('&');
    for(int i = 0; i < variables.length(); ++i)
    {
        QStringList split = variables.at(i).split('=');
        answer.insert(split.at(0),split.at(1));
    }

    return answer;
}

void RestClient::requestFinished(QNetworkReply *reply)
{
    //qDebug() << "network reply: " << reply->readAll();
//    QList<QPair<QString,QString>> answer = parseNetworkReply(reply->readAll());
    unsigned int id = mReplayIdMap.value(reply);
    mReplayIdMap.remove(reply);
    emit requestReady(QString::fromUtf8(reply->readAll()),id);
    reply->deleteLater();
}

