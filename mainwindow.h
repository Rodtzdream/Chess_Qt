#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

class MainWindow;
struct Board;

enum State{
    Pawn,
    Rook,
    Bishop,
    Knight,
    Queen,
    King,
    Empty
};

enum Team{
    Black,
    White,
    None
};

struct Board
{
    Board(MainWindow *ui);
    QPushButton* cell;
    State state;
    Team team;
};

extern Board* board[8][8];
extern Team *turn;
extern int info[2][6];
extern bool selected;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
