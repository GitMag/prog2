#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QObject>
#include "gamewindow.hh"

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
    void on_playButton_clicked();

    void on_pushButtonCancelGame_clicked();

    void on_pushButtonStartGame_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HH
