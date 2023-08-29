#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH

#include "gameboard.hh"
#include <QDialog>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <qtimer.h>
#include <QKeyEvent>

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, int height=5, int width=5, int seed=0);
    ~GameWindow();

    // catch keypresses
    void keyPressEvent(QKeyEvent* event) override;

    //  draws snake piece
    void draw_snake();

    // draws food
    void draw_food();

    //draw walls, only exec on game start
    void draw_walls();

    // initializes the game
    void init_game();

    // exect ui actions after game has been won
    void post_game_actions(bool victory=false);


private slots:
    // update game for every timer timeout
    void update_game();

    void on_pushButtonReset_clicked();

    void on_pushButtonPause_clicked();

private:

    Ui::GameWindow *ui_;
    QGraphicsScene *scene;
    GameBoard *board;
    QTimer *timer;

    int width_ = 20;
    int height_ = 20;
    int seed_ = 0;

    QBrush bodyColor;
    QBrush foodColor;
    QPen outlinePen;

    // default direction
    std::string direction_ = "w";

    bool game_paused_ = false;
};

#endif // GAMEWINDOW_HH
