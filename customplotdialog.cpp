#include "customplotdialog.h"
#include "ui_customplotdialog.h"

CustomPlotDialog::CustomPlotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomPlotDialog)
{
    ui->setupUi(this);
}

CustomPlotDialog::~CustomPlotDialog()
{
    delete ui;
}
