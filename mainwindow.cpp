#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

Board::Board(MainWindow *ui)
{
    cell = new QPushButton(ui);
    state = State::Empty;
    team = Team::None;
}

Board* board[8][8];
Team *turn;
int info[2][6] = {{8,2,2,2,1,1},{8,2,2,2,1,1}};
bool selected;

bool Check(int i, int j, int i2, int j2, Ui::MainWindow* ui)
{
    // PAWN Black
    if(board[i2][j2]->team == Team::Black && board[i2][j2]->state == State::Pawn)
    {
        if(i2 == 1 && board[i][j]->cell == board[i2+2][j2]->cell && board[i2+2][j2]->state == State::Empty)
            return true;
        else if(board[i][j]->cell == board[i2+1][j2]->cell && board[i2+1][j2]->state == State::Empty)
            return true;
        else if(board[i][j]->cell == board[i2+1][j2+1]->cell && board[i2+1][j2+1]->state != State::Empty)
        {
            --info[Team::White][board[i][j]->state];
            ui->tableWidget->item(board[i][j]->state, Team::White)->setText(QString::number(info[Team::White][board[i][j]->state]));
            return true;
        }
        else if(board[i][j]->cell == board[i2+1][j2-1]->cell && board[i2+1][j2-1]->state != State::Empty)
        {
            --info[Team::White][board[i][j]->state];
            ui->tableWidget->item(board[i][j]->state, Team::White)->setText(QString::number(info[Team::White][board[i][j]->state]));
            return true;
        }
    }
    // PAWN White
    else if(board[i2][j2]->team == Team::White && board[i2][j2]->state == State::Pawn)
    {
        if(i2 == 6 && board[i][j]->cell == board[i2-2][j2]->cell && board[i2-2][j2]->state == State::Empty)
            return true;
        else if(board[i][j]->cell == board[i2-1][j2]->cell && board[i2-1][j2]->state == State::Empty)
            return true;
        else if(board[i][j]->cell == board[i2-1][j2+1]->cell && board[i2-1][j2+1]->state != State::Empty)
        {
            --info[Team::Black][board[i][j]->state];
            ui->tableWidget->item(board[i][j]->state, Team::Black)->setText(QString::number(info[Team::Black][board[i][j]->state]));
            return true;
        }
        else if(board[i][j]->cell == board[i2-1][j2-1]->cell && board[i2-1][j2-1]->state != State::Empty)
        {
            --info[Team::Black][board[i][j]->state];
            ui->tableWidget->item(board[i][j]->state, Team::Black)->setText(QString::number(info[Team::Black][board[i][j]->state]));
            return true;
        }
    }
    // ROOK
    else if(board[i2][j2]->state == State::Rook)
    {
        if(i == i2 && j > j2)
        {
            for (int var = j2 + 1; var < j; ++var)
            {
                if(board[i][var]->state != State::Empty)
                    return false;
            }
        }
        else if(i == i2 && j < j2)
        {
            for (int var = j + 1; var < j2; ++var)
            {
                if(board[i][var]->state != State::Empty)
                    return false;
            }
        }
        else if(j == j2 && i > i2)
        {
            for (int var = i2 + 1; var < i; ++var)
            {
                if(board[var][j]->state != State::Empty)
                    return false;
            }
        }
        else if(j == j2 && i < i2)
        {
            for (int var = i + 1; var < i2; ++var)
            {
                if(board[var][j]->state != State::Empty)
                    return false;
            }
        }
        if(board[i2][j2]->team == Team::Black && board[i][j]->team == Team::White)
        {
            --info[Team::White][board[i][j]->state];
            ui->tableWidget->item(board[i][j]->state, Team::White)->setText(QString::number(info[Team::White][board[i][j]->state]));
        }
        else if(board[i2][j2]->team == Team::White && board[i][j]->team == Team::Black)
        {
            --info[Team::Black][board[i][j]->state];
            ui->tableWidget->item(board[i][j]->state, Team::Black)->setText(QString::number(info[Team::Black][board[i][j]->state]));
        }
        return true;
    }
    // KNIGHT
    if(board[i2][j2]->state == State::Knight)
    {
        if((i == i2+2 && j == j2+1) || (i == i2+1 && j == j2+2) || (i == i2-2 && j == j2-1) || (i == i2-1 && j == j2-2) ||
                (i == i2+2 && j == j2-1) || (i == i2-2 && j == j2+1) || (i == i2+1 && j == j2-2) || (i == i2-1 && j == j2+2))
        {
            if(board[i][j]->state == State::Empty)
                return true;
            else if(board[i][j]->team == board[i2][j2]->team)
                return false;
            else if(board[i][j]->team != board[i2][j2]->team)
            {
                --info[board[i][j]->team][board[i][j]->state];
                ui->tableWidget->item(board[i][j]->state, board[i][j]->team)->setText(QString::number(info[board[i][j]->team][board[i][j]->state]));
                return true;
            }
        }
    }
    // BISHOP
    if(board[i2][j2]->state == State::Bishop)
    {
        if(abs(i - i2) == abs(j - j2))
        {
            if(i > i2 && j > j2)
            {
                for (int var = i2 + 1, var2 = j2 + 1; var < i; ++var, ++var2)
                {
                    if(board[var][var2]->state != State::Empty)
                        return false;
                }
            }
            else if(i < i2 && j < j2)
            {
                for (int var = i + 1, var2 = j + 1; var < i2; ++var, ++var2)
                {
                    if(board[var][var2]->state != State::Empty)
                        return false;
                }
            }
            else if(j > j2 && i < i2)
            {
                for (int var = i + 1, var2 = j - 1; var < i2; ++var, --var2)
                {
                    if(board[var][var2]->state != State::Empty)
                        return false;
                }
            }
            else if(j < j2 && i > i2)
            {
                for (int var = i - 1, var2 = j + 1; var2 < j2; --var, ++var2)
                {
                    if(board[var][var2]->state != State::Empty)
                        return false;
                }
            }
            if(board[i2][j2]->team == Team::Black && board[i][j]->team == Team::White)
            {
                --info[Team::White][board[i][j]->state];
                ui->tableWidget->item(board[i][j]->state, Team::White)->setText(QString::number(info[Team::White][board[i][j]->state]));
            }
            else if(board[i2][j2]->team == Team::White && board[i][j]->team == Team::Black)
            {
                --info[Team::Black][board[i][j]->state];
                ui->tableWidget->item(board[i][j]->state, Team::Black)->setText(QString::number(info[Team::Black][board[i][j]->state]));
            }
            return true;
        }
    }
    // QUEEN
    if(board[i2][j2]->state == State::Queen)
    {
        if(i == i2 && j > j2)
        {
            for (int var = j2 + 1; var < j; ++var)
            {
                if(board[i][var]->state != State::Empty)
                    return false;
            }
        }
        else if(i == i2 && j < j2)
        {
            for (int var = j + 1; var < j2; ++var)
            {
                if(board[i][var]->state != State::Empty)
                    return false;
            }
        }
        else if(j == j2 && i > i2)
        {
            for (int var = i2 + 1; var < i; ++var)
            {
                if(board[var][j]->state != State::Empty)
                    return false;
            }
        }
        else if(j == j2 && i < i2)
        {
            for (int var = i + 1; var < i2; ++var)
            {
                if(board[var][j]->state != State::Empty)
                    return false;
            }
        }
        else if(i > i2 && j > j2)
        {
            for (int var = i2 + 1, var2 = j2 + 1; var < i; ++var, ++var2)
            {
                if(board[var][var2]->state != State::Empty)
                    return false;
            }
        }
        else if(i < i2 && j < j2)
        {
            for (int var = i + 1, var2 = j + 1; var < i2; ++var, ++var2)
            {
                if(board[var][var2]->state != State::Empty)
                    return false;
            }
        }
        else if(j > j2 && i < i2)
        {
            for (int var = i + 1, var2 = j - 1; var < i2; ++var, --var2)
            {
                if(board[var][var2]->state != State::Empty)
                    return false;
            }
        }
        else if(j < j2 && i > i2)
        {
            for (int var = i - 1, var2 = j + 1; var2 < j2; --var, ++var2)
            {
                if(board[var][var2]->state != State::Empty)
                    return false;
            }
        }
        if(board[i2][j2]->team == Team::Black && board[i][j]->team == Team::White)
        {
            --info[Team::White][board[i][j]->state];
            ui->tableWidget->item(board[i][j]->state, Team::White)->setText(QString::number(info[Team::White][board[i][j]->state]));
        }
        else if(board[i2][j2]->team == Team::White && board[i][j]->team == Team::Black)
        {
            --info[Team::Black][board[i][j]->state];
            ui->tableWidget->item(board[i][j]->state, Team::Black)->setText(QString::number(info[Team::Black][board[i][j]->state]));
        }
        return true;
    }
    // KING
    if(board[i2][j2]->state == State::King)
    {
        if((i == i2 && j == j2+1) || (i == i2 && j == j2-1) || (i == i2+1 && j == j2) || (i == i2-1 && j == j2))
        {
            if(board[i][j]->team == Team::None)
                return true;
            if(board[i][j]->team != board[i2][j2]->team)
            {
                --info[board[i][j]->team][board[i][j]->state];
                ui->tableWidget->item(board[i][j]->state, board[i][j]->team)->setText(QString::number(info[board[i][j]->team][board[i][j]->state]));
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap chess("D:/Qt/Chess/data/Chess_Board.jpg");
    ui->label_board->setPixmap(chess);

    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            board[i][j] = new Board(this);
            board[i][j]->cell->setFlat(true);
            board[i][j]->cell->setStyleSheet("QPushButton { background-color: transparent }");
            board[i][j]->cell->setIconSize(QSize(60, 60));
            board[i][j]->cell->setGeometry(50 + j * 70, 117 + i * 70, 70, 70);
            board[i][j]->state = State::Empty;
            board[i][j]->team = Team::None;
        }
    }

    board[0][0]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_rdt60.png"));
    board[0][1]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_ndt60.png"));
    board[0][2]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_bdt60.png"));
    board[0][3]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_qdt60.png"));
    board[0][4]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_kdt60.png"));
    board[0][5]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_bdt60.png"));
    board[0][6]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_ndt60.png"));
    board[0][7]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_rdt60.png"));

    board[7][0]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_rlt60.png"));
    board[7][1]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_nlt60.png"));
    board[7][2]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_blt60.png"));
    board[7][3]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_qlt60.png"));
    board[7][4]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_klt60.png"));
    board[7][5]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_blt60.png"));
    board[7][6]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_nlt60.png"));
    board[7][7]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_rlt60.png"));

    board[0][0]->state = State::Rook;
    board[0][1]->state = State::Knight;
    board[0][2]->state = State::Bishop;
    board[0][3]->state = State::Queen;
    board[0][4]->state = State::King;
    board[0][5]->state = State::Bishop;
    board[0][6]->state = State::Knight;
    board[0][7]->state = State::Rook;

    board[7][0]->state = State::Rook;
    board[7][1]->state = State::Knight;
    board[7][2]->state = State::Bishop;
    board[7][3]->state = State::Queen;
    board[7][4]->state = State::King;
    board[7][5]->state = State::Bishop;
    board[7][6]->state = State::Knight;
    board[7][7]->state = State::Rook;

    for(int j = 0; j < 8; ++j)
    {
        board[1][j]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_pdt60.png"));
        board[6][j]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_plt60.png"));
        board[1][j]->state = State::Pawn;
        board[6][j]->state = State::Pawn;
        board[0][j]->team = Team::Black;
        board[1][j]->team = Team::Black;
        board[6][j]->team = Team::White;
        board[7][j]->team = Team::White;
    }

    int i2 = 0, j2 = 0;
    turn = new Team;
    *turn = Team::Black;
    selected = false;

    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            MainWindow::connect(board[i][j]->cell, &QPushButton::clicked, [=, &i2, &j2]{
                if(!selected && board[i][j]->team == *turn)
                {
                    selected = true;
                    board[i][j]->cell->setStyleSheet("border: 5px solid red;");
                    i2 = i;
                    j2 = j;
                }
                else if(selected && board[i][j]->team == *turn)
                {
                    board[i2][j2]->cell->setStyleSheet("border: 0px;");
                    board[i][j]->cell->setStyleSheet("border: 5px solid red;");
                    i2 = i;
                    j2 = j;
                }
                else if(selected && board[i][j]->team != *turn)
                {
                    if (Check(i, j, i2, j2, ui))
                    {
                        board[i][j]->cell->setStyleSheet("border: 0px");
                        board[i2][j2]->cell->setStyleSheet("border: 0px");
                        board[i][j]->cell->setIcon(board[i2][j2]->cell->icon());
                        board[i2][j2]->cell->setIcon(QIcon());
                        board[i][j]->state = board[i2][j2]->state;
                        board[i2][j2]->state = State::Empty;
                        board[i][j]->team = board[i2][j2]->team;
                        board[i2][j2]->team = Team::None;
                        if(board[i][j]->state == State::Pawn && board[i][j]->team == Team::Black && i == 7)
                        {
                            Dialog dialog(board[i][j], ui->tableWidget);
                            dialog.setModal(true);
                            dialog.exec();
                        }
                        else if(board[i][j]->state == State::Pawn && board[i][j]->team == Team::White && i == 0)
                        {
                            Dialog dialog(board[i][j], ui->tableWidget);
                            dialog.setModal(true);
                            dialog.exec();
                        }
                        if(*turn == Team::Black)
                        {
                            *turn = Team::White;
                            ui->label_turn->setText("Turn: White");
                        }
                        else
                        {
                            *turn = Team::Black;
                            ui->label_turn->setText("Turn: Black");
                        }
                        selected = false;
                        if(info[Team::Black][State::King] == 0)
                            QMessageBox::information(this,"Game is end!","The winner is White!");
                        else if(info[Team::White][State::King] == 0)
                            QMessageBox::information(this,"Game is end!","The winner is Black!");
                    }
                }
            });
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i = 2; i < 6; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            board[i][j]->cell->setIcon(QIcon());
            board[i][j]->state = State::Empty;
            board[i][j]->team = Team::None;
            board[i][j]->cell->setStyleSheet("border: 0px");
        }
    }

    board[0][0]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_rdt60.png"));
    board[0][1]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_ndt60.png"));
    board[0][2]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_bdt60.png"));
    board[0][3]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_qdt60.png"));
    board[0][4]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_kdt60.png"));
    board[0][5]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_bdt60.png"));
    board[0][6]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_ndt60.png"));
    board[0][7]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_rdt60.png"));

    board[7][0]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_rlt60.png"));
    board[7][1]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_nlt60.png"));
    board[7][2]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_blt60.png"));
    board[7][3]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_qlt60.png"));
    board[7][4]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_klt60.png"));
    board[7][5]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_blt60.png"));
    board[7][6]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_nlt60.png"));
    board[7][7]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_rlt60.png"));

    board[0][0]->state = State::Rook;
    board[0][1]->state = State::Knight;
    board[0][2]->state = State::Bishop;
    board[0][3]->state = State::Queen;
    board[0][4]->state = State::King;
    board[0][5]->state = State::Bishop;
    board[0][6]->state = State::Knight;
    board[0][7]->state = State::Rook;

    board[7][0]->state = State::Rook;
    board[7][1]->state = State::Knight;
    board[7][2]->state = State::Bishop;
    board[7][3]->state = State::Queen;
    board[7][4]->state = State::King;
    board[7][5]->state = State::Bishop;
    board[7][6]->state = State::Knight;
    board[7][7]->state = State::Rook;

    for(int j = 0; j < 8; ++j)
    {
        board[1][j]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_pdt60.png"));
        board[6][j]->cell->setIcon(QIcon("D:/Qt/Chess/data/Chess_plt60.png"));
        board[1][j]->state = State::Pawn;
        board[6][j]->state = State::Pawn;
        board[0][j]->team = Team::Black;
        board[1][j]->team = Team::Black;
        board[6][j]->team = Team::White;
        board[7][j]->team = Team::White;
        board[0][j]->cell->setStyleSheet("border: 0px");
        board[1][j]->cell->setStyleSheet("border: 0px");
        board[6][j]->cell->setStyleSheet("border: 0px");
        board[7][j]->cell->setStyleSheet("border: 0px");
    }

    for (int i = 0; i < 2; ++i)
    {
        info[i][State::Pawn] = 8;
        info[i][State::Rook] = 2;
        info[i][State::Bishop] = 2;
        info[i][State::Knight] = 2;
        info[i][State::Queen] = 1;
        info[i][State::King] = 1;
        ui->tableWidget->item(State::Pawn, i)->setText("8");
        ui->tableWidget->item(State::Rook, i)->setText("2");
        ui->tableWidget->item(State::Bishop, i)->setText("2");
        ui->tableWidget->item(State::Knight, i)->setText("2");
        ui->tableWidget->item(State::Queen, i)->setText("1");
        ui->tableWidget->item(State::King, i)->setText("1");
    }
    *turn = Team::Black;
    ui->label_turn->setText("Turn: Black");
    selected = false;
}

