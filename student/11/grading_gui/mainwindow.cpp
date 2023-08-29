#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecounter.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set valid ranges for spinboxes
    ui->spinBoxN->setMaximum(MAX_N_POINTS);
    ui->spinBoxG->setMaximum(MAX_G_POINTS);
    ui->spinBoxP->setMaximum(MAX_P_POINTS);
    ui->spinBoxE->setMaximum(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_countPushButton_clicked()
{
    // calculate grade
    //get different scores from spinboxes
    int n = ui->spinBoxN->value();
    int p = ui->spinBoxP->value();
    int g = ui->spinBoxG->value();
    int e = ui->spinBoxE->value();

    int grade = count_final_grade(n, g ,p, e);

    QString grade_message = "Total grade: " + QString::number(grade);

    // set grade to textBrowser
    ui->textBrowser->setText(grade_message);
}

