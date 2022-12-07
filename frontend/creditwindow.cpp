#include "creditwindow.h"
#include "ui_creditwindow.h"
#include <QDebug>
#include <QByteArray>


CreditWindow::CreditWindow(QString givenToken, int idcard,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreditWindow)
{
    //AJASTIN
    connect(timer10sek,SIGNAL(timeout()),this,SLOT(timer10Slot()));
    ui->setupUi(this);
    id_card = idcard;
    token = givenToken;

}

CreditWindow::~CreditWindow()
{
    delete ui;
}

void CreditWindow::getbalance()
{
    //HAKEE TILIN SALDON
    QString site_url="http://localhost:3000/account/credit/"+QString::number(id_card);
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getBalanceManager = new QNetworkAccessManager(this);
    connect(getBalanceManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getBalanceSlot(QNetworkReply*)));
    reply = getBalanceManager->get(request);
}

void CreditWindow::getowner()
{
    //HAKEE TILINOMISTAJAN TIEDOT
    QString site_url="http://localhost:3000/owner/fname"; //mites sukunimi??
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getOwnerInfoManager = new QNetworkAccessManager(this);

    QJsonObject jsonObj;  // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("id_card",id_card);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(getOwnerInfoManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getOwnerInfoSlot(QNetworkReply*)));
    reply = getOwnerInfoManager->post(request, QJsonDocument(jsonObj).toJson());
}

void CreditWindow::startwindowtimer()
{
    timer10sek->start(1000);
}

void CreditWindow::resets()
{
    time10=0;
    emit resettimer30();
}

void CreditWindow::getBalanceSlot(QNetworkReply *reply)
{
    account_balance_data=reply->readAll();
    qDebug()<<"TILITIEDOT : "+account_balance_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(account_balance_data);
    QJsonObject json_obj = json_doc.object();
    QString balancedata;
    int balance;
    balancedata=QString::number(json_obj["credit_balance"].toInt());
    balance=balancedata.toInt();
    qDebug()<<"Kortin saldo on  " <<balance;

    ui->label_balance->setText("Your available credit is: "+ QString::number(balance));
    getowner();
}

void CreditWindow::getwithdrawdataSlot(QNetworkReply *reply)
{
    withdraw_data=reply->readAll();
    qDebug()<<"DATA : "+withdraw_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(withdraw_data);
        QJsonObject json_obj = json_doc.object();    // Tätä menetelmää voi käyttää kun vastauksena on 1 objekti
        int test;                           // Jos vastaus on array (esim logs), käytä QBYTEARRAY
        test=json_obj["affectedRows"].toInt();
        creditwithdrawmanager->deleteLater();
        if(test>0){
            timer10sek->stop();
            emit nextwindow(6);
            this->close();
        }
        if(test==0){
            resets();
            ui->label_error->setText("Insufficient funds");
        }
}

void CreditWindow::customAmount(int amount)
{
    this->show();
    resets();
    withdraw(amount);
}

void CreditWindow::showUI()
{
    resets();
    this->show();
}

void CreditWindow::withdraw(int amount)
{
    QString site_url="http://localhost:3000/card/creditwithdraw";
    QNetworkRequest request(site_url);

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    QJsonObject jsonObj;  // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("id_card", id_card);
    jsonObj.insert("amount", amount);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    creditwithdrawmanager = new QNetworkAccessManager(this);
    connect(creditwithdrawmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getwithdrawdataSlot(QNetworkReply*)));
    reply = creditwithdrawmanager->post(request,QJsonDocument(jsonObj).toJson());
}

void CreditWindow::getOwnerInfoSlot(QNetworkReply *reply)
{
    owner_data=reply->readAll();
    qDebug()<<"DATA : "+owner_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(owner_data);
    QJsonObject json_obj = json_doc.object();
    QString ownerdata;
    ownerdata=json_obj["fname"].toString();
    qDebug()<<"Tilinomistaja on  " <<ownerdata;

    ui->label_info->setText("Account owner is: "+ ownerdata+ "");
}

void CreditWindow::on_btn20_clicked()
{
    resets();
    withdraw(20);
}

void CreditWindow::on_btn40_clicked()
{
    resets();
    withdraw(40);
}

void CreditWindow::on_btn60_clicked()
{
    resets();
    withdraw(60);
}

void CreditWindow::on_btn100_clicked()
{
    resets();
    withdraw(100);
}

void CreditWindow::on_btn200_clicked()
{
    resets();
    withdraw(200);
}


void CreditWindow::on_btn500_clicked()
{
    resets();
  withdraw(500);
}


void CreditWindow::on_btnBack_clicked()
{
    timer10sek->stop();
    emit backtomainmenu();
    this->close();
}

void CreditWindow::timer10Slot()
{
    time10++;
    if (time10>10){
        timer10sek->stop();
        emit backtomainmenu();
        this->close();
    }
}

void CreditWindow::on_btnOther_clicked()
{
    amountWindow = new CreditAmountWindow(this);
    connect(amountWindow, SIGNAL(customAmount(int)), this, SLOT(customAmount(int)));
    connect(amountWindow, SIGNAL(back()), this, SLOT(showUI()));
    amountWindow->show();
    resets();
    this->hide();
}
