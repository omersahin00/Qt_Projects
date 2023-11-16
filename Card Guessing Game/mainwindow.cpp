#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QRandomGenerator>
#include <QTimer>
#include <QMouseEvent>


QTimer *createTimer;
QTimer *moveTimer;
QTimer *destroyTimer;
QList<QLabel *> labelList;
bool createKey = false;
bool moveKey = false;
bool destroyKey = false;
int successfulCounter = 0;
int unsuccessfulCounter = 0;
QLabel *destroyLabel = nullptr;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetTimers();
    WindowSetBackground();
    CreateLabels();
    LabelMove();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePoint = event->pos();
    if (!destroyTimer->isActive())
        LabelClickCheck(mousePoint.x(), mousePoint.y());
}




void MainWindow::LabelClickCheck(int mouseX, int mouseY)
{
    for (int i = 0; i < labelList.size(); i++) {
        QLabel *duckLabel = labelList.at(i);
        if ((mouseX >= duckLabel->pos().x() && mouseX <= (duckLabel->pos().x() + 30)) &&
            (mouseY >= duckLabel->pos().y() && mouseY <= (duckLabel->pos().y() + 30))){
            destroyLabel = duckLabel;
            DestroyLabel();
            ui->label_counter1->setText(QString("%1").arg(++successfulCounter));
        }
    }
}





void MainWindow::DestroyLabel()
{
    if (destroyKey) {
        destroyKey = false;
        destroyTimer->stop();
        destroyLabel->deleteLater();
        destroyLabel = nullptr;
    }
    else {
        destroyKey = true;
        labelList.removeOne(destroyLabel);
        QImage image(":/res/vurulma.png");
        QPixmap pixmap = QPixmap::fromImage(image);
        pixmap = pixmap.scaled(30, 30);
        destroyLabel->setPixmap(pixmap);
        destroyTimer->start(600);
    }
}





void MainWindow::LabelMove()
{
    if (moveKey)
    {
        moveKey = false;
        moveTimer->stop();
        for (int i = 0; i < labelList.size(); i++) {
            QLabel *label = labelList.at(i);
            if (label->pos().y() >= ui->label_background->height()){
                labelList.removeOne(label);
                label->deleteLater();
                ui->label_counter2->setText(QString("%1").arg(++unsuccessfulCounter));
            }
            else
                label->move(label->pos().x(), label->pos().y() + 5);
        }
        LabelMove();
    }
    else
    {
        moveKey = true;
        moveTimer->start(100);
    }
}






void MainWindow::CreateLabels()
{
    if (createKey){
        createKey = false;
        createTimer->stop();
        CreateDuckLabel();
        CreateLabels();
    }
    else {
        createKey = true;
        createTimer->start(1000);
    }
}







void MainWindow::CreateDuckLabel()
{
    QImage duckImage(":/res/ordek.png");
    QPixmap duckPixmap = QPixmap::fromImage(duckImage);
    QLabel *label = new QLabel(this);
    int randomNum = QRandomGenerator::global()->bounded((ui->label_background->width() - 20));
    label->setGeometry(randomNum, 0, 30, 30);
    duckPixmap = duckPixmap.scaled(label->size());
    label->setPixmap(duckPixmap);
    labelList.append(label);
    label->show();
}





void MainWindow::WindowSetBackground()
{
    this->setStyleSheet("background-color: white;");
    ui->label_Text1->setStyleSheet("color: green");
    ui->label_Text2->setStyleSheet("color: red");
    ui->label_counter1->setStyleSheet("color: green");
    ui->label_counter2->setStyleSheet("color: red");
    QImage image(":/res/arkaPlan.png");
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap = pixmap.scaled(ui->label_background->size());
    ui->label_background->setPixmap(pixmap);
}




void MainWindow::SetTimers()
{
    createTimer = new QTimer(this);
    connect(createTimer, SIGNAL(timeout()), this, SLOT(CreateLabels()));

    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(LabelMove()));

    destroyTimer = new QTimer(this);
    connect(destroyTimer, SIGNAL(timeout()), this, SLOT(DestroyLabel()));
}



