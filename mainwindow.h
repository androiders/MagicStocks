#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include <QString>
#include <QVariantList>
#include <QListWidgetItem>
#include <QDate>

#include "src/net/yahoointerface.h"

class MainController;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(MainController * mc, QWidget *parent = 0);
    ~MainWindow();

    void setTableModel(QAbstractTableModel * model);

    //void connectSearchField(YahooInterface * yhi);

signals:

    void search(QString str);

    void updateStocks(bool b);

public slots:

    void searchExecute();

    void searchFailed(const QString & errStr);

    void searchReady(const QStringList &symbols);

    void searchItemDblClicked(QListWidgetItem * item);

    void addStockBtnClicked(bool);

    void actionSaveIndex(bool b);

    void actionLoadIndex(bool b);

private:
    Ui::MainWindow *ui;

    MainController * mMc;

//    YahooInterface *  mYhi;
};

#endif // MAINWINDOW_H
