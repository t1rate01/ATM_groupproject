#ifndef DEBITWINDOW_H
#define DEBITWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
#include "debitamountwindow.h"

namespace Ui {
class DebitWindow;
}

class DebitWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebitWindow(QString, int,QWidget *parent = nullptr);
    ~DebitWindow();

    void resetAllTimers();
    void getbalance();
    void getowner();
    void getsavingsmode();
    void startwindowtimer();
    void resets();
private slots:
    void on_btn20_clicked();
    void on_btn40_clicked();
    void on_btn60_clicked();
    void on_btn100_clicked();
    void on_btn200_clicked();
    void on_btn500_clicked();
    void on_btnBack_clicked();
    void timer10Slot();
    void getOwnerInfoSlot(QNetworkReply *reply);
    void getBalanceSlot(QNetworkReply *reply);
    void getwithdrawdataSlot(QNetworkReply * reply);
    void showUI();
    void customAmount(int);
    void receiveSaveModeSlot(int);


    void on_btnOther_clicked();

signals:
    void resettimer30();
    void backtomainmenu();
    void nextwindow(int);
    void askSaveMode();

private:
    Ui::DebitWindow *ui;
    QTimer * timer10sek = new QTimer;
    QString token;
    int account_balance;
    int id_card;
    int time10=0;
    void withdraw(int);
    DebitAmountWindow * amountWindow;
    int currentBalance=0;
    int savingsmode;

    QNetworkAccessManager *getOwnerInfoManager;
    QNetworkAccessManager * debitwithdrawmanager;
    QNetworkReply *reply;
    QByteArray owner_data;
    QByteArray withdraw_data;
    QNetworkAccessManager *getBalanceManager;
    QByteArray account_balance_data;
};

#endif // DEBITWINDOW_H
