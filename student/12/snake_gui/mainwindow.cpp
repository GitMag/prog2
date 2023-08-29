#include "mainwindow.hh"
#include "ui_mainwindow.h"
#
// test


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //hide start game frame
    ui->frameStartGame->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// start GameWidnow and play
void MainWindow::on_playButton_clicked()
{
   ui->frameStartGame->show();

}


void MainWindow::on_pushButtonCancelGame_clicked()
{
    ui->frameStartGame->hide();
    ui->frameMenu->show();
}


void MainWindow::on_pushButtonStartGame_clicked()
{
    int width = ui->spinBoxWidth->value();
    int height = ui->spinBoxHeight->value();
    int seed = ui->lineEditSeed->text().toInt();

    GameWindow *gw = new GameWindow(nullptr, width, height, seed);
    gw->show();
}

