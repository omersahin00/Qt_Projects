#ifndef ETIKET_H
#define ETIKET_H

#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include "mainwindow.h"


class etiket : public QLabel
{
    Q_OBJECT
public:
    explicit etiket(MainWindow *frm, QWidget *parent = nullptr, QString dosyaYolu = "");
    MainWindow *anafrm;
    QString _dosyaYolu;
    int _photoIndex;
    int _diziIndex;

private:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    double DistanceCalculator(int X1, int Y1, int X2, int Y2);
    bool ArrayCheck();

signals:

};

#endif // ETIKET_H
