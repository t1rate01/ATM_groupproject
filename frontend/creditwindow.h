#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
#include "creditamountwindow.h"

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreditWindow(QString, int,QWidget *parent = nullptr);
    ~CreditWindow();

    void resetAllTimers();
    void getbalance();
    void getowner();
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
    void customAmount(int);

    void showUI();
    void on_btnOther_clicked();

signals:
    void resettimer30();
    void backtomainmenu();
    void nextwindow(int);


private:
    Ui::CreditWindow *ui;
    QTimer * timer10sek = new QTimer;
    QString token;
    int account_balance;
    int id_card;
    int time10=0;
    void withdraw(int);

    QNetworkAccessManager *getOwnerInfoManager;
    QNetworkAccessManager * creditwithdrawmanager;
    QNetworkReply *reply;
    QByteArray owner_data;
    QByteArray withdraw_data;
    QNetworkAccessManager *getBalanceManager;
    QByteArray account_balance_data;
    CreditAmountWindow *amountWindow;
};

#endif // CREDITWINDOW_H
