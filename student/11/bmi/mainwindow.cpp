#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_closeButton_clicked()
{
    close();
}


void MainWindow::on_countButton_clicked()
{
    // do BMI calculation

    // check if possible
    ui->infoTextBrowser->clear();
    float bmi = 0;
    if (ui->heightLineEdit->text().toInt() != 0) {
        bmi = weight / (height * height)* 10000;
        ui->resultLabel->setText(QString::number(bmi));

        // set weight class
        if (bmi > 25) {
            ui->infoTextBrowser->setText("You are overweight.");
        } else if (bmi > 18.5) {
            ui->infoTextBrowser->setText("Your weight is normal.");
        } else {
            ui->infoTextBrowser->setText("You are underweight.");
        }
    } else {
        // division by zero
        ui->resultLabel->setText("Cannot count");
    }
}


void MainWindow::on_weightLineEdit_textChanged(const QString &arg1)
{
    // assume is int
    if (arg1 != "") {
        weight = arg1.toFloat();
    } else {
        weight = 0;
    }
}


void MainWindow::on_heightLineEdit_textChanged(const QString &arg1)
{
    if (arg1 != "") {
        height = arg1.toFloat();
    } else {
        height = 0;
    }
}

