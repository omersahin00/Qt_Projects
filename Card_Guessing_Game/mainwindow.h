#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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
    void CloseCard();
    void RandomIdGenerator();
    bool MatrisCheck(int temp);
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void ButtonOperation(QPushButton* pushButton, int buttonID);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void CreateButton();
    bool MatchCheck();
    void FinishGame();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
