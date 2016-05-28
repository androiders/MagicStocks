#include "yahoointerface.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

YahooInterface::YahooInterface(QObject *parent)
:QObject(parent)
,mSearchReqId(0)
,mStockReadyReqId(0)
{
    connect(&rc,SIGNAL(requestReady(QString,unsigned int)),this,SLOT(stockDataReady(QString,unsigned int)));
}

void YahooInterface::searchStocks(const QString &searchText, const QString &region, const QString &lang)
{
    RequestData rd;
    rd.url = "http://autoc.finance.yahoo.com/autoc";

    DataPair dp;
    dp.first="query";
    dp.second = searchText;
    rd.requestParams.append(dp);

    dp.first = "region";
    dp.second = region;
    rd.requestParams.append(dp);

    dp.first = "lang";
    dp.second = lang;
    rd.requestParams.append(dp);

    dp = getCallbackPair("YAHOO.Finance.SymbolSuggest.ssCallback");
    rd.requestParams.append(dp);

    mSearchReqId = rc.requestGet(rd);
}

void YahooInterface::getStockBySymbol(const QString &symbol)
{
    QStringList s;
    s.append(symbol);
    getStocksBySymbol(s);
}



void YahooInterface::getStocksBySymbol(const QStringList &symbols)
{
    RequestData rd;
    rd.url = "http://query.yahooapis.com/v1/public/yql";
    QString query = "select * from yahoo.finance.quotes where symbol in (";
    for(int i = 0; i< symbols.length(); ++i)
    {
        query += "\"" + symbols[i] + "\"";
        if(i != (symbols.length() - 1))
        {
            query += ",";
        }
    }
    query += ")";

    DataPair dp;
    dp.first="q";
    dp.second = query;

    rd.requestParams.append(dp);

    dp = getJsonFormatPair();
    rd.requestParams.append(dp);

    dp = getDiagnosticsPair();
    rd.requestParams.append(dp);

    dp = getEnvPair();
    rd.requestParams.append(dp);

    dp.first = "debug";
    dp.second = "true";
    rd.requestParams.append(dp);

    dp = getCallbackPair();
    rd.requestParams.append(dp);

    mStockReadyReqId = rc.requestGet(rd);
}

void YahooInterface::getHistoricalStockData(const QString &symbol, const QDate from, const QDate to)
{
    RequestData rd;
    rd.url = "http://query.yahooapis.com/v1/public/yql";
    QString query = "select * from yahoo.finance.historicaldata where symbol =";
    query += " '" + symbol + "'";
    query +=  " and startDate = '" + from.toString("yyyy.MM.dd")
            + "' and endDate = '" +  to.toString("yyyy.MM.dd") + "'";

    DataPair dp;
    dp.first="q";
    dp.second = query;

    rd.requestParams.append(dp);

    dp = getJsonFormatPair();
    rd.requestParams.append(dp);

    dp = getDiagnosticsPair();
    rd.requestParams.append(dp);

    dp = getEnvPair();
    rd.requestParams.append(dp);

    dp.first = "debug";
    dp.second = "true";
    rd.requestParams.append(dp);

    dp = getCallbackPair();
    rd.requestParams.append(dp);

    unsigned int rid = rc.requestGet(rd);
    mHistoricalDataReqIds.insert(rid,true);
    qDebug() << "query historical data: " + QString::number(rid) + query;

}

void YahooInterface::stockDataReady(const QString &data, unsigned int reqId)
{
    if(reqId == mSearchReqId)
        parseSearchResult(data);

    if(reqId == mStockReadyReqId)
        parseStockData(data);

    if(mHistoricalDataReqIds.contains(reqId))
    {
        parseHistoricalStockData(data);
        mHistoricalDataReqIds.remove(reqId);
        qDebug() << "received response " + QString::number(reqId);
    }


}

void YahooInterface::parseStockData(const QString &data)
{
    QStringList propertyNames;
    QStringList propertyKeys;
    //QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonObject jsonQuery = jsonObject["query"].toObject();
    QJsonObject jsonResult = jsonQuery["results"].toObject();

    //if many symbols were querried...
    if(jsonResult["quote"].isArray())
        emit stocksReady(jsonResult["quote"].toArray());

    //if just onw symbol was querried
    if(jsonResult["quote"].isObject())
    {
        QJsonObject obj = jsonResult["quote"].toObject();
        if(obj["Name"].isNull())//this means that the symbol was not found!
        {
            emit noStockFound(obj["Symbol"].toString() + " was not found");
        }
        else
        {
//            qDebug() << jsonResult["quote"].toObject();
            QJsonArray stocks;
            stocks.append(obj);
            emit stocksReady(stocks);
        }
    }

}

void YahooInterface::searchFailed()
{
    emit stockSearchFailed("No results found");
    return;

}

void YahooInterface::parseSearchResult(const QString &data)
{
    if(data.isEmpty())
    {
        searchFailed();
        return;
    }

    //brute force parsing!
    QString json = data;
    json.remove(0,QString("YAHOO.Finance.SymbolSuggest.ssCallback(").length());
    json.remove(json.lastIndexOf(')'),2);
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    //get the result set array
    QJsonObject resultSet = doc.object();
    QJsonObject resultsObj = resultSet["ResultSet"].toObject();
    QJsonValue results = resultsObj["Result"];

    QJsonArray resultArray;
    if(results.isObject())
    {
        resultArray.append(results);
    }
    if(results.isArray())
    {
        resultArray = results.toArray();
    }

    if(resultArray.size() == 0)
    {
        searchFailed();
        return;
    }

    QStringList symbols;
    foreach(QJsonValue val, resultArray)
    {
        if(val.toObject().keys().contains(("symbol")))
            symbols.append(val.toObject().value("symbol").toString());
    }

    emit stockSearchReady(symbols);
    emit stockSearchReady(resultArray.toVariantList());

    //    qDebug() << "search result: " << data;
}

void YahooInterface::parseHistoricalStockData(const QString &data)
{

    //qDebug() << "historical reply: " + data;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    //get the query
    QJsonObject resultSet = doc.object();
    QJsonObject resultsObj = resultSet["query"].toObject();
    //get the result objec
    QJsonObject result = resultsObj["results"].toObject();
    //get the quote array
    QJsonValue quotes = result["quote"];


    QJsonArray quotesArray;
    if(quotes.isObject())
    {
        quotesArray.append(quotes);
    }
    if(quotes.isArray())
    {
        quotesArray = quotes.toArray();
    }

    QString symbol = quotesArray.first().toObject()["Symbol"].toString();
    emit stockHistoricalDataReady(symbol, quotesArray);
}

DataPair YahooInterface::getJsonFormatPair() const
{
    DataPair dp;
    dp.first = "format";
    dp.second = "json";
    return dp;
}

DataPair YahooInterface::getDiagnosticsPair() const
{
    DataPair dp;
    dp.first = "diagnostics";
    dp.second = "true";
    return dp;
}

DataPair YahooInterface::getEnvPair() const
{
    DataPair dp;
    dp.first = "env";
    dp.second = "store://datatables.org/alltableswithkeys";
    return dp;
}

DataPair YahooInterface::getCallbackPair(const QString &cb) const
{
    DataPair dp;
    dp.first = "callback";
    dp.second = cb;
    return dp;
}
