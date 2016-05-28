#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/controller/maincontroller.h"
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(MainController *mc, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mMc = mc;
//    connect(ui->searchField,SIGNAL(editingFinished()),this,SLOT(searchExecute()));
    connect(ui->searchField,SIGNAL(returnPressed()),this,SLOT(searchExecute()));
    connect(ui->searchListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(searchItemDblClicked(QListWidgetItem*)));
    connect(ui->addStockButton,SIGNAL(clicked(bool)),this,SLOT(addStockBtnClicked(bool)));
    connect(ui->actionSave_model, SIGNAL(triggered(bool)), this, SLOT(actionSaveIndex(bool)));
    connect(ui->actionLoad_model,SIGNAL(triggered(bool)),this,SLOT(actionLoadIndex(bool)));
    connect(ui->actionUpdate_stock, SIGNAL(triggered(bool)),this,SIGNAL(updateStocks(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTableModel(QAbstractTableModel * model)
{
    ui->tableView->setModel(model);
}

//void MainWindow::connectSearchField(YahooInterface *yhi)
//{
//    if(yhi == NULL)
//        return;

//    mYhi = yhi;
//    connect(this, SIGNAL(search(QString)),yhi,SLOT(searchStocks(QString)));
//    connect(yhi,SIGNAL(stockSearchFailed(QString)),this,SLOT(searchFailed(QString)));
//    connect(yhi,SIGNAL(stockSearchReady(const QStringList & )),this,SLOT(searchReady(const QStringList & )));
//}

void MainWindow::searchExecute()
{
    QString str = ui->searchField->text();
    emit search(str);
}

void MainWindow::searchFailed(const QString &errStr)
{
    ui->addStockButton->setEnabled(false);
    ui->searchListWidget->addItem(errStr);
}

void MainWindow::searchReady(const QStringList & symbols)
{
    ui->searchListWidget->clear();
    foreach(QString result , symbols)
    {
        ui->searchListWidget->addItem(result);
    }

    ui->addStockButton->setEnabled(true);
}

void MainWindow::searchItemDblClicked(QListWidgetItem *item)
{
    if(item == NULL)
        return;

    QString symbol = item->text();
    mMc->getStockBySymbol(symbol);

}

void MainWindow::addStockBtnClicked(bool)
{
    if(ui->searchListWidget->selectedItems().size() == 0)
        return;

    QListWidgetItem * item = ui->searchListWidget->selectedItems().first();
    if(!item)
        return;

    searchItemDblClicked(item);
}

void MainWindow::actionSaveIndex(bool b)
{
    QString homeDirStr = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               homeDirStr,
                               tr("Index (*.idx)"));

    if(fileName.isEmpty())
        return;

   if(! mMc->saveIndex(fileName))
       QMessageBox::information(this,"Save failed","Save fail. Either it is empty or the file does not exist.");
}

void MainWindow::actionLoadIndex(bool b)
{
    QString homeDirStr = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"),
                               homeDirStr,
                               tr("Index (*.idx)"));

    if(fileName.isEmpty())
        return;

   if(! mMc->loadIndex(fileName))
       QMessageBox::information(this,"Load failed","Load index failed. Either it is empty or the file does not exist.");

}


