#include "mainwindow.h"
#include <QApplication>
#include "src/Stock/stockmodel.h"
#include "src/Stock/stockdata.h"
#include "src/Stock/stockhistoricaldata.h"
#include "src/Stock/stockhistoricaldatapoint.h"
#include "src/factories/stockdatafactory.h"
#include "src/controller/maincontroller.h"
#include "customplotdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainController * mc = new MainController();
    MainWindow w(mc);
    CustomPlotDialog cd;

    StockModel * sm = new StockModel();
    StockDataFactory * sdf = new StockDataFactory();
    YahooInterface * yhi = new YahooInterface();
    StockDataFileStorage * sdfs = new StockDataFileStorage();

    mc->setMainWindow(&w);
    mc->setStockModel(sm);
    mc->setStockDataFactory(sdf);
    mc->setYahooInterface(yhi);
    mc->setStockDataFileStorage(sdfs);
    mc->connectAll();

    cd.show();
    w.show();

    return a.exec();
}
