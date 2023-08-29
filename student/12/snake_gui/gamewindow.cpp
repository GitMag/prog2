#include "gamewindow.hh"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent, int width, int height, int seed) :
    QDialog(parent),
    ui_(new Ui::GameWindow),
    width_(width),
    height_(height),
    seed_(seed)
{
    ui_->setupUi(this);

    //set graphics scene as background for dialog
    scene = new QGraphicsScene(this);
    ui_->graphicsView->setScene(scene);

    //add and connect timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(update_game()));

    // configure drawing pens
    bodyColor.setColor(Qt::green);
    foodColor.setColor(Qt::yellow);
    outlinePen.setWidth(2);

    //init game
    init_game();

}

GameWindow::~GameWindow()
{
    delete ui_;
    delete board;
}

void GameWindow::init_game() {

    // hide notification label
    ui_->labelNotify->hide();

    // configure board
    delete board;
    board = new GameBoard(width_,height_, seed_);

    //start timer
    timer->start(300);
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
    // set snake direction according to keypress


    if (event->key() == Qt::Key_W) {
        direction_ = "w";
    } else if (event->key() == Qt::Key_S) {
        direction_ = "s";
    } else if (event->key() == Qt::Key_D) {
        direction_ = "d";
    } else if (event->key() == Qt::Key_A) {
        direction_ = "a";
    }
}

void GameWindow::draw_snake() {

    std::deque<Point> snake_coords = {};
    snake_coords = board->get_snake_coords();

            // just change the draw color, then do one scene->addRect with the corresponding color instead of doing it 3 times
    for (auto coord : snake_coords) {
        if (coord == board->getHead()) {
            // head
            scene->addRect(coord.get_x() * SNAKE_PIECE_SIZE, coord.get_y() * SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, outlinePen, Qt::red);
        } else if (coord == board->getTail()) {
            scene->addRect(coord.get_x() * SNAKE_PIECE_SIZE, coord.get_y() * SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, outlinePen, Qt::yellow);
        } else {
            // normal body piece
             scene->addRect(coord.get_x() * SNAKE_PIECE_SIZE, coord.get_y() * SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, outlinePen, Qt::green);
        }

    }

}

void GameWindow::draw_food() {

    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    std::deque<Point> snake_coords = {};
    Point food_coord = board->get_food_coords();

            // scene->addRect(coord[0] * SNAKE_PIECE_SIZE, y * SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, outlinePen, blueBrush);
   scene->addRect(food_coord.get_x() * SNAKE_PIECE_SIZE, food_coord.get_y() * SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, outlinePen, blueBrush);

}

void GameWindow::draw_walls() {
    int x = -1;
    while (x <= width_) {
        // draw vertical wall if x is 0 or end of width
        if (x == -1 or x == width_) {
            for (int y = -1; y <= height_; ++y) {
                // draw vertical
                scene->addRect(x * SNAKE_PIECE_SIZE, y * SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, outlinePen, Qt::black);
            }
        } else {
            // draw horizontal line
            scene->addRect(x * SNAKE_PIECE_SIZE, -1 * SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, outlinePen, Qt::black);
            scene->addRect(x * SNAKE_PIECE_SIZE, height_ * SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, outlinePen, Qt::black);
        }
        ++x;
    }
}
void GameWindow::post_game_actions(bool victory) {
    //stop timer and do other general stuff
    timer->stop();

    if (victory) {
        // display victory message
        ui_->labelNotify->setText("You won!");
    } else {
        ui_->labelNotify->setText("You lost!");
    }
    ui_->labelNotify->show();
}


void GameWindow::update_game() {

    //check if game has been won/lost
    if (board->gameWon()) {
        post_game_actions(true);
    } else if (board->gameLost()) {
        post_game_actions();
    }
    // clear scene
    board->moveSnake(direction_);
    scene->clear();

    // draw walls
    draw_walls();

    // draw snake
    draw_snake();

    //draw food
    draw_food();

    // move snake


    qDebug() << board->get_snake_coords()[0].get_x() << " " << board->get_snake_coords()[0].get_y();


}

void GameWindow::on_pushButtonReset_clicked()
{
    //reset
    init_game();
}

void GameWindow::on_pushButtonPause_clicked()
{
    // pause game
    if (game_paused_) {
        timer->start();
        game_paused_ = false;
        ui_->pushButtonPause->setText("Pause");
        ui_->labelNotify->hide();
    } else {
        timer->stop();
        game_paused_ = true;
        ui_->pushButtonPause->setText("Resume");
        ui_->labelNotify->setText("Game paused!");
        ui_->labelNotify->show();

    }
}

