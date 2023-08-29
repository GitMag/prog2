/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QGraphicsView *graphicsView;
    QPushButton *pushButtonReset;
    QPushButton *pushButtonPause;
    QLabel *labelNotify;

    void setupUi(QDialog *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName("GameWindow");
        GameWindow->resize(849, 619);
        graphicsView = new QGraphicsView(GameWindow);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(20, 20, 811, 531));
        pushButtonReset = new QPushButton(GameWindow);
        pushButtonReset->setObjectName("pushButtonReset");
        pushButtonReset->setGeometry(QRect(710, 570, 121, 29));
        pushButtonPause = new QPushButton(GameWindow);
        pushButtonPause->setObjectName("pushButtonPause");
        pushButtonPause->setGeometry(QRect(580, 570, 121, 29));
        labelNotify = new QLabel(GameWindow);
        labelNotify->setObjectName("labelNotify");
        labelNotify->setGeometry(QRect(50, 390, 761, 151));
        QFont font;
        font.setPointSize(72);
        labelNotify->setFont(font);
        labelNotify->setAutoFillBackground(true);

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QDialog *GameWindow)
    {
        GameWindow->setWindowTitle(QCoreApplication::translate("GameWindow", "Dialog", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("GameWindow", "Reset game", nullptr));
        pushButtonPause->setText(QCoreApplication::translate("GameWindow", "Pause", nullptr));
        labelNotify->setText(QCoreApplication::translate("GameWindow", "You win!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
