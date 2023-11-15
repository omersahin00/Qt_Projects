#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QTimer>
#include <QRandomGenerator>


QTimer *timer;
QPushButton* pushButtonTemp0;
QPushButton* pushButtonTemp1;
QSize buttonSize;

int photoIDs[10];
bool closeKey = false;
bool waitTurn = true;
bool finishGameKey = false;
int wrongAnswer = 0, correctAnswer = 0;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_3->setVisible(false);
    ui->pushButtonDummy->setVisible(false);
    resize(600, 400);
    ui->label_1->setText(QString("%1").arg(wrongAnswer));
    timer = new QTimer(this);

    RandomIdGenerator();
    CreateButton();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::RandomIdGenerator()
{
    for (int i = 0; i < 10; i++) {
        photoIDs[i] = -1;
    }

    for (int i = 0; i < 5; i++) {
        while (1) {
            int temp = QRandomGenerator::global()->bounded(5);
            if (MatrisCheck(temp))
            {
                photoIDs[i] = temp;
                break;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        photoIDs[i + 5] = photoIDs[i];
    }

    for (int i = 0; i < 10; i++) {
        int index1 = QRandomGenerator::global()->bounded(10);
        int index2 = QRandomGenerator::global()->bounded(10);
        int temp = photoIDs[index2];
        photoIDs[index2] = photoIDs[index1];
        photoIDs[index1] = temp;
    }

    QString metin;
    for (int i = 0; i < 10; i++) {
        metin += QString("%1 ").arg(photoIDs[i]);
    }
    ui->label_2->setText(metin);
}


bool MainWindow::MatrisCheck(int temp)
{
    for (int j = 0; j < 10; ++j) {
        if (photoIDs[j] == temp){
            return false;
        }
    }
    return true;
}



void MainWindow::CloseCard()
{
    if (closeKey)
    {
        timer->stop();
        QImage imageCover(":/res/kapak.png");
        QPixmap pixmap = QPixmap::fromImage(imageCover);
        pixmap = pixmap.scaled(buttonSize.width(), buttonSize.height() - 10);
        pushButtonTemp0->setIconSize(buttonSize);
        pushButtonTemp0->setIcon(QIcon(pixmap));
        pushButtonTemp1->setIconSize(buttonSize);
        pushButtonTemp1->setIcon(QIcon(pixmap));
        ui->label_1->setText(QString("%1").arg(wrongAnswer));
        closeKey = false;
        pushButtonTemp0 = ui->pushButtonDummy;
        pushButtonTemp1 = ui->pushButtonDummy;
    }
    else
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(CloseCard()));
        timer->start(500);
        closeKey = true;
    }
}



void MainWindow::ButtonOperation(QPushButton* pushButton, int buttonID)
{
    QImage resim(":/res/" + QString("%1").arg(photoIDs[buttonID]) + ".png");
    QSize buttonSizeTemp = pushButton->size();

    QPixmap pixmap = QPixmap::fromImage(resim);
    pixmap = pixmap.scaled(buttonSizeTemp.width(), buttonSizeTemp.height() - 10);
    pushButton->setIcon(QIcon(pixmap));
    pushButton->setIconSize(buttonSizeTemp);

    buttonSize = buttonSizeTemp;

    if (waitTurn){
        pushButtonTemp0 = pushButton;
        waitTurn = false;
    }
    else {
        pushButtonTemp1 = pushButton;
        if (!MatchCheck()) CloseCard();
        else{
            if (correctAnswer == 5){
                timer->stop();
                FinishGame();
            }
        }
        waitTurn = true;
    }
}




bool MainWindow::MatchCheck()
{
    int index0 = pushButtonTemp0->objectName().at(11).digitValue();
    int index1 = pushButtonTemp1->objectName().at(11).digitValue();

    if (photoIDs[index0] == photoIDs[index1]){
        correctAnswer++;
        return true;
    }
    else{
        wrongAnswer++;
        return false;
    }
}





void MainWindow::on_pushButton_0_clicked()
{
    ButtonOperation(ui->pushButton_0, 0);
}


void MainWindow::on_pushButton_1_clicked()
{
    ButtonOperation(ui->pushButton_1, 1);
}


void MainWindow::on_pushButton_2_clicked()
{
    ButtonOperation(ui->pushButton_2, 2);
}


void MainWindow::on_pushButton_3_clicked()
{
    ButtonOperation(ui->pushButton_3, 3);
}


void MainWindow::on_pushButton_4_clicked()
{
    ButtonOperation(ui->pushButton_4, 4);
}


void MainWindow::on_pushButton_5_clicked()
{
    ButtonOperation(ui->pushButton_5, 5);
}


void MainWindow::on_pushButton_6_clicked()
{
    ButtonOperation(ui->pushButton_6, 6);
}


void MainWindow::on_pushButton_7_clicked()
{
    ButtonOperation(ui->pushButton_7, 7);
}


void MainWindow::on_pushButton_8_clicked()
{
    ButtonOperation(ui->pushButton_8, 8);
}


void MainWindow::on_pushButton_9_clicked()
{
    ButtonOperation(ui->pushButton_9, 9);
}




void MainWindow::CreateButton()
{
    QImage imageCover(":/res/kapak.png");
    QSize buttonSize = ui->pushButton_0->size();
    QPixmap pixmap = QPixmap::fromImage(imageCover);
    pixmap = pixmap.scaled(buttonSize.width(), buttonSize.height() - 10);

    ui->pushButton_0->setIconSize(buttonSize);
    ui->pushButton_0->setIcon(QIcon(pixmap));

    ui->pushButton_1->setIconSize(buttonSize);
    ui->pushButton_1->setIcon(QIcon(pixmap));

    ui->pushButton_2->setIconSize(buttonSize);
    ui->pushButton_2->setIcon(QIcon(pixmap));

    ui->pushButton_3->setIconSize(buttonSize);
    ui->pushButton_3->setIcon(QIcon(pixmap));

    ui->pushButton_4->setIconSize(buttonSize);
    ui->pushButton_4->setIcon(QIcon(pixmap));

    ui->pushButton_5->setIconSize(buttonSize);
    ui->pushButton_5->setIcon(QIcon(pixmap));

    ui->pushButton_6->setIconSize(buttonSize);
    ui->pushButton_6->setIcon(QIcon(pixmap));

    ui->pushButton_7->setIconSize(buttonSize);
    ui->pushButton_7->setIcon(QIcon(pixmap));

    ui->pushButton_8->setIconSize(buttonSize);
    ui->pushButton_8->setIcon(QIcon(pixmap));

    ui->pushButton_9->setIconSize(buttonSize);
    ui->pushButton_9->setIcon(QIcon(pixmap));
}



void MainWindow::FinishGame()
{
    if (finishGameKey){
        timer->stop();
        ui->pushButton_0->deleteLater();
        ui->pushButton_1->deleteLater();
        ui->pushButton_2->deleteLater();
        ui->pushButton_3->deleteLater();
        ui->pushButton_4->deleteLater();
        ui->pushButton_5->deleteLater();
        ui->pushButton_6->deleteLater();
        ui->pushButton_7->deleteLater();
        ui->pushButton_8->deleteLater();
        ui->pushButton_9->deleteLater();
        ui->pushButtonDummy->deleteLater();
        ui->label_2->deleteLater();
        ui->label_3->setVisible(true);
    }
    else {
        connect(timer, SIGNAL(timeout()), this, SLOT(FinishGame()));
        timer->start(500);
        finishGameKey = true;
    }
}




