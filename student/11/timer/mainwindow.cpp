#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timer_update())
    );
    ui->setupUi(this);

    // configure timer
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer->start();
}


void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}


void MainWindow::on_resetButton_clicked()
{
    seconds = 0;
    minutes = 0;
    ui->lcdNumberMin->display(minutes);
    ui->lcdNumberSec->display(seconds);
}


void MainWindow::on_closeButton_clicked()
{
    close();
}

void MainWindow::timer_update() {
    // clock signal
    //update minutes and seconds
    if (seconds == 59) {
        seconds = -1;
        minutes++;
        ui->lcdNumberMin->display(minutes);
    }
    // update gui
    seconds++;
    ui->lcdNumberSec->display(seconds);
}

