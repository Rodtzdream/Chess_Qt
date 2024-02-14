#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(Board* board, QTableWidget *tableWidget, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->board = board;
    this->tableWidget = tableWidget;
    if(info[board->team][State::Rook] == 2)
        ui->radioButton_5->hide();
    if(info[board->team][State::Knight] == 2)
        ui->radioButton_6->hide();
    if(info[board->team][State::Bishop] == 2)
        ui->radioButton_7->hide();
    if(info[board->team][State::Queen] == 1)
        ui->radioButton_8->hide();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if(ui->radioButton_5->isChecked() || ui->radioButton_6->isChecked() || ui->radioButton_7->isChecked() || ui->radioButton_8->isChecked())
    {
        if(board->team == Team::Black)
        {
            if(ui->radioButton_5->isChecked())
            {
                board->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_rdt60.png"));
                board->state = State::Rook;
            }
            else if(ui->radioButton_6->isChecked())
            {
                board->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_ndt60.png"));
                board->state = State::Knight;
            }
            else if(ui->radioButton_7->isChecked())
            {
                board->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_bdt60.png"));
                board->state = State::Bishop;
            }
            else if(ui->radioButton_8->isChecked())
            {
                board->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_qdt60.png"));
                board->state = State::Queen;
            }
        }
        else
        {
            if(ui->radioButton_5->isChecked())
            {
                board->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_rlt60.png"));
                board->state = State::Rook;
            }
            else if(ui->radioButton_6->isChecked())
            {
                board->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_nlt60.png"));
                board->state = State::Knight;
            }
            else if(ui->radioButton_7->isChecked())
            {
                board->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_blt60.png"));
                board->state = State::Bishop;
            }
            else if(ui->radioButton_8->isChecked())
            {
                board->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_qlt60.png"));
                board->state = State::Queen;
            }
        }
        ++info[board->team][board->state];
        tableWidget->item(board->state, board->team)->setText(QString::number(info[board->team][board->state]));
        --info[board->team][State::Pawn];
        tableWidget->item(State::Pawn, board->team)->setText(QString::number(info[board->team][State::Pawn]));
    }
    this->close();
}
