#ifndef DIALOG_H
#define DIALOG_H

#include "mainwindow.h"
#include <QDialog>
#include <QTableWidget>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Board *board, QTableWidget *tableWidget, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    Board *board;
    QTableWidget *tableWidget;
};

#endif // DIALOG_H
