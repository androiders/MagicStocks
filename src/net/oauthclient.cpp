#include "oauthclient.h"
#include <QPair>
#include <QDateTime>
#include <QByteArray>



OAuthClient::OAuthClient(QObject *parent) : QObject(parent)
{
    consumerKey = "dj0yJmk9TEVieEY2RFNpejRxJmQ9WVdrOVFXaElZblZGTnpJbWNHbzlNQS0tJnM9Y29uc3VtZXJzZWNyZXQmeD01MA--";
    consumerSecret = "2d53b81d79d1c974d3c2f9824ebc2eeab09a02fc";
    connect(&restClient,SIGNAL(requestReady(QString)),this,SLOT(replyComplete(QString)));
    requesting = false;
    verifying = false;
}

void OAuthClient::getRequestToken()
{
    RequestData rd;
//    rd.url = "https://api.login.yahoo.com/oauth/v2/get_request_token";
    rd.url = "https://query.yahooapis.com/v1/public/yql";

    rd.requestParams.append(getTimePair());

    rd.requestParams.append(getRandomStringPair(getTimeStamp()));

    rd.requestParams.append(getConsumerKeyPair());

    rd.requestParams.append(getSignatureMethodPair());

    DataPair query;
    query.first= "q";
    query.second = "select * from pm.finance where symbol='SCA-B.ST'";
    rd.requestParams.append(query);

    DataPair format;
    format.first = "format";
    format.second = "json";
    rd.requestParams.append(format);

    QPair<QString,QString> sig;
    sig.first = "oauth_signature";
    sig.second = consumerSecret + "%26";
    rd.requestParams.append(sig);

    rd.requestParams.append(getVersionPair());

    QPair<QString,QString> lang;
    lang.first = "xoauth_lang_pref";
    lang.second = "en-us";
    rd.requestParams.append(lang);

    QPair<QString,QString> cb;
    cb.first = "oauth_callback";
    cb.second = "oob";
    rd.requestParams.append(cb);

    requesting = true;
    restClient.requestGet(rd);
}

void OAuthClient::verifyAccess(QString verifier)
{
    qDebug() << "code is: " << verifier;

    RequestData rd;
    rd.url = "https://api.login.yahoo.com/oauth/v2/get_token";

    rd.requestParams.append(getConsumerKeyPair());
    rd.requestParams.append(getSignatureMethodPair());
    rd.requestParams.append(getVersionPair());
    rd.requestParams.append(getTimePair());
    rd.requestParams.append(getRandomStringPair(getTimeStamp()));

    DataPair token;
    token.first = "oauth_token";
    token.second = requestToken;
    rd.requestParams.append(token);

    DataPair verif;
    verif.first = "oauth_verifier";
    verif.second = verifier;
    rd.requestParams.append(verif);

    DataPair sig;
    sig.first = "oauth_signature";
    sig.second =consumerSecret + "%26" + tokenSecret;
    rd.requestParams.append(sig);

    verifying = true;
    restClient.requestGet(rd);
}

QString OAuthClient::getTimeStamp() const
{
    QDateTime dt(QDate::currentDate());
    return QString::number(dt.toTime_t());
}

QString OAuthClient::getRandomString(QString timeStamp) const
{
    return "random" + timeStamp;
}

DataPair OAuthClient::getTimePair() const
{
    DataPair time;
    time.first = "oauth_timestamp";
    time.second = getTimeStamp();
    return time;
}

DataPair OAuthClient::getVersionPair() const
{

    DataPair ver;
    ver.first = "oauth_version";
    ver.second = "1.0";
    return ver;

}

DataPair OAuthClient::getSignatureMethodPair() const
{
    DataPair sigMeth;
    sigMeth.first = "oauth_signature_method";
    sigMeth.second = "plaintext";
    return sigMeth;
}

DataPair OAuthClient::getConsumerKeyPair() const
{
    DataPair key;
    key.first = "oauth_consumer_key";
    key.second = consumerKey;
    return key;
}

DataPair OAuthClient::getRandomStringPair(QString timeStamp) const
{
    DataPair once;
    once.first = "oauth_nonce";
    once.second = getRandomString(timeStamp);
    return once;
}

void OAuthClient::handleRequestReply(QString answerString)
{
    qDebug() << "answer: " << answerString;
    QMap<QString,QString> data = restClient.parseNetworkReply(answerString);
    requestToken = data["oauth_token"];
    tokenSecret = data["oauth_token_secret"];
    QString authUrl = data["xoauth_request_auth_url"];
    authUrl = QUrl::fromPercentEncoding(authUrl.toUtf8());
    QUrl url(authUrl);

    requesting = false;
    emit signalAuthUrl(url);

}

void OAuthClient::handleVerification(QString answerString)
{
    qDebug() << "auth reply: " << answerString;
    verifying = false;
    emit signalAuthDone();
}

void OAuthClient::replyComplete(QString answerString)
{
    if(requesting)
        handleRequestReply(answerString);
 //   if(verifying)
 //       handleVerification(answerString);
}

