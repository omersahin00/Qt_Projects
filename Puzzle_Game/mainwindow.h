#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void CreateButtons();
    int RandomIndexGenerator();
    int imageIndex[25];
    int adimSayac = 0;
    QList<int> indexList;
    int indexTemp = 0;
    bool key = true;

private:
};
#endif // MAINWINDOW_H
