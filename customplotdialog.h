#ifndef CUSTOMPLOTDIALOG_H
#define CUSTOMPLOTDIALOG_H

#include <QDialog>

namespace Ui {
class CustomPlotDialog;
}

class CustomPlotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomPlotDialog(QWidget *parent = 0);
    ~CustomPlotDialog();

private:
    Ui::CustomPlotDialog *ui;
};

#endif // CUSTOMPLOTDIALOG_H
