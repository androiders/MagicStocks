#ifndef OAUTHCLIENT_H
#define OAUTHCLIENT_H

#include <QObject>
#include <QString>
#include "src/net/restclient.h"

class OAuthClient : public QObject
{
    Q_OBJECT
public:
    explicit OAuthClient(QObject *parent = 0);



signals:

    void signalAuthUrl(QUrl url);
    void signalAuthDone();

public slots:

    void getRequestToken();

    void verifyAccess(QString verifier);


private:

    QString getTimeStamp() const;

    QString getRandomString(QString timeStamp) const;

    DataPair getTimePair() const;

    DataPair getVersionPair() const;

    DataPair getSignatureMethodPair() const;

    DataPair getConsumerKeyPair() const;

    DataPair getRandomStringPair(QString timeStamp) const;

    void handleRequestReply(QString answerString);

    void handleVerification(QString answerString);

    RestClient restClient;

    QString consumerKey;
    QString consumerSecret;
    QString requestToken;
    QString tokenSecret;

    bool requesting;
    bool verifying;

private slots:

    void replyComplete(QString answerString);

};

#endif // OAUTHCLIENT_H
