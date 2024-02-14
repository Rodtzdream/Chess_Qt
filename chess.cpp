//#include "chess.h"

//Chess::Chess(MainWindow *ui, Ui::MainWindow *ui2, QLabel* background)
//{
//    this->ui = ui;
//    this->ui2 = ui2;
//    move = false;
//    turn = Team::Black;

//    QPixmap chess("D:/Qt/Chess/data/Chess_Board3.jpg");
//    background->setPixmap(chess);

//    for(int i = 0; i < 8; ++i)
//    {
//        for(int j = 0; j < 8; ++j)
//        {
//            board[i][j] = new QPushButton(ui);
//            MainWindow::connect(board[i][j], &QPushButton::clicked, [=]{
//                if(state[i][j] != State::Empty)
//                {
//                    if(!move)
//                        move = true;
//                    else
//                        board[this->i][this->j]->setStyleSheet("border: 0px;");
//                    board[i][j]->setStyleSheet("border: 5px solid red;");
//                    this->i = i;
//                    this->j = j;
//                }
//            });
//            board[i][j]->setFlat(true);
//            board[i][j]->setStyleSheet("QPushButton { background-color: transparent }");
//            board[i][j]->setIconSize(QSize(60, 60));
//            board[i][j]->setGeometry(50 + j * 70, 117 + i * 70, 70, 70);
//            state[i][j] = State::Empty;
//            team[i][j] = Team::None;
//        }
//    }

//    board[0][0]->setIcon(QIcon("D:/Qt/Chess/data/Chess_rdt60.png"));
//    board[0][1]->setIcon(QIcon("D:/Qt/Chess/data/Chess_ndt60.png"));
//    board[0][2]->setIcon(QIcon("D:/Qt/Chess/data/Chess_bdt60.png"));
//    board[0][3]->setIcon(QIcon("D:/Qt/Chess/data/Chess_kdt60.png"));
//    board[0][4]->setIcon(QIcon("D:/Qt/Chess/data/Chess_qdt60.png"));
//    board[0][5]->setIcon(QIcon("D:/Qt/Chess/data/Chess_bdt60.png"));
//    board[0][6]->setIcon(QIcon("D:/Qt/Chess/data/Chess_ndt60.png"));
//    board[0][7]->setIcon(QIcon("D:/Qt/Chess/data/Chess_rdt60.png"));

//    board[7][0]->setIcon(QIcon("D:/Qt/Chess/data/Chess_rlt60.png"));
//    board[7][1]->setIcon(QIcon("D:/Qt/Chess/data/Chess_nlt60.png"));
//    board[7][2]->setIcon(QIcon("D:/Qt/Chess/data/Chess_blt60.png"));
//    board[7][3]->setIcon(QIcon("D:/Qt/Chess/data/Chess_klt60.png"));
//    board[7][4]->setIcon(QIcon("D:/Qt/Chess/data/Chess_qlt60.png"));
//    board[7][5]->setIcon(QIcon("D:/Qt/Chess/data/Chess_blt60.png"));
//    board[7][6]->setIcon(QIcon("D:/Qt/Chess/data/Chess_nlt60.png"));
//    board[7][7]->setIcon(QIcon("D:/Qt/Chess/data/Chess_rlt60.png"));

//    state[0][0] = State::Rook;
//    state[0][1] = State::Knight;
//    state[0][2] = State::Bishop;
//    state[0][3] = State::King;
//    state[0][4] = State::Queen;
//    state[0][5] = State::Bishop;
//    state[0][6] = State::Knight;
//    state[0][7] = State::Rook;

//    state[7][0] = State::Rook;
//    state[7][1] = State::Knight;
//    state[7][2] = State::Bishop;
//    state[7][3] = State::King;
//    state[7][4] = State::Queen;
//    state[7][5] = State::Bishop;
//    state[7][6] = State::Knight;
//    state[7][7] = State::Rook;

//    for(int j = 0; j < 8; ++j)
//    {
//        board[1][j]->setIcon(QIcon("D:/Qt/Chess/data/Chess_pdt60.png"));
//        board[6][j]->setIcon(QIcon("D:/Qt/Chess/data/Chess_plt60.png"));
//        state[1][j] = State::Pawn;
//        state[6][j] = State::Pawn;
//        team[0][j] = Team::Black;
//        team[1][j] = Team::Black;
//        team[6][j] = Team::White;
//        team[7][j] = Team::White;
//    }
//}
