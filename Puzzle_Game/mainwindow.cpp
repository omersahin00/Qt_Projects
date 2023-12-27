#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "etiket.h"
#include <QPixmap>
#include <QImage>
#include <QRandomGenerator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CreateButtons();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::CreateButtons()
{
    for (int i = 0; i < 25; ++i)
    {
        int photoIndex = RandomIndexGenerator();
        imageIndex[i] = photoIndex;

        QString dosyaYolu = ":/res/images/" + QString("%1").arg(photoIndex) + ".png";
        QImage buttonImage(dosyaYolu);
        etiket *button = new etiket(this, this, dosyaYolu);
        button->_photoIndex = photoIndex;
        button->_diziIndex = i;

        button->setGeometry((i % 5) * 130, (i / 5) * 130, 130, 130);
        QPixmap buttonPixmap = QPixmap::fromImage(buttonImage);
        buttonPixmap.scaled(button->width(), button->height());
        button->setPixmap(buttonPixmap);
        button->show();
        button->setVisible(true);
    }
}



int MainWindow::RandomIndexGenerator()
{
    if (!key) {
        if (indexTemp == 23){
            indexTemp++;
            return 24;
        }
        else if (indexTemp == 24) return 23;
        else return indexTemp++;
    }

    int index;
    while (1) {
        bool key = true;
        index = QRandomGenerator::global()->bounded(25);
        for (int var = 0; var < indexList.size(); ++var) {
            if (indexList.at(var) == index) {
                key = false;
                break;
            }
        }
        if (key == true) {
            indexList.append(index);
            break;
        }
    }
    return index;
}



















