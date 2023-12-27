#include "etiket.h"
#include <QMimeData>
#include <QDrag>
#include "mainwindow.h"
#include "ui_mainwindow.h"

etiket::etiket(MainWindow *frm, QWidget *parent, QString dosyaYolu) : QLabel(parent)
{
    anafrm = frm;
    _dosyaYolu = dosyaYolu;
    setFrameShape(QFrame::Box);
    setScaledContents(true);
    setAcceptDrops(true);
}


void etiket::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}


void etiket::dropEvent(QDropEvent *event)
{
    etiket *gelen = qobject_cast<etiket*>(event->source());
    if (gelen && gelen != this) {

        QPoint gelenPoint((gelen->pos().x() + (gelen->height() / 2)), (gelen->pos().y() + (gelen->width() / 2)));
        QPoint hedefPoint((this->pos().x() + (this->height() / 2)), (this->pos().y() + (this->width() / 2)));

        double distance = DistanceCalculator(gelenPoint.x(), gelenPoint.y(), hedefPoint.x(), hedefPoint.y());
        if (distance <= 184)
        {
            QImage birakilan(pixmap().toImage());
            setPixmap(QPixmap::fromImage(gelen->pixmap().toImage()));
            gelen->setPixmap(QPixmap::fromImage(birakilan));

            int temp = gelen->_photoIndex;
            gelen->_photoIndex = _photoIndex;
            _photoIndex = temp;

            temp = anafrm->imageIndex[this->_diziIndex];
            anafrm->imageIndex[this->_diziIndex] = anafrm->imageIndex[gelen->_diziIndex];
            anafrm->imageIndex[gelen->_diziIndex] = temp;

            anafrm->adimSayac++;
            anafrm->ui->label_4->setText(QString("%1").arg(anafrm->adimSayac));
        }

        if (ArrayCheck()) {
            anafrm->ui->label->setText("Oyun tamamlandı");
        }
        else {
            anafrm->ui->label->setText("");
        }

        return;
    }
}



void etiket::mouseMoveEvent(QMouseEvent *event)
{
    QMimeData *mdata = new QMimeData();
    mdata->setImageData(pixmap().toImage());
    QDrag *suruklenen = new QDrag(this);
    suruklenen->setMimeData(mdata);
    suruklenen->setPixmap(mdata->imageData().value<QPixmap>());
    suruklenen->exec(Qt::MoveAction);
}



double etiket::DistanceCalculator(int X1, int Y1, int X2, int Y2)
{
    int deltaX = std::abs(X1 - X2);
    int deltaY = std::abs(Y1 - Y2);
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}



bool etiket::ArrayCheck()
{
    int key = true;
    for (int i = 0; i < 25; ++i) {
        if (anafrm->imageIndex[i] != i) {
            key = false;
        }
    }
    return key;
}












