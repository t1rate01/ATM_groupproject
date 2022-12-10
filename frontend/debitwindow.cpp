#include "debitwindow.h"
#include "ui_debitwindow.h"
#include <QDebug>
#include <QByteArray>

DebitWindow::DebitWindow(QString givenToken, int idcard,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebitWindow)
{
    //AJASTIN
    connect(timer10sek,SIGNAL(timeout()),this,SLOT(timer10Slot()));
    ui->setupUi(this);
    id_card = idcard;
    token = givenToken;

}

DebitWindow::~DebitWindow()
{
    delete ui;
}

void DebitWindow::getbalance()
{
    //HAKEE TILIN SALDON
    QString site_url="http://localhost:3000/account/"+QString::number(id_card);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getBalanceManager = new QNetworkAccessManager(this);
    connect(getBalanceManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getBalanceSlot(QNetworkReply*)));
    reply = getBalanceManager->get(request);
}

void DebitWindow::resets()
{
    time10=0;
    emit resettimer30();
}
void DebitWindow::getowner()
{
    //HAKEE TILINOMISTAJAN TIEDOT
    QString site_url="http://localhost:3000/owner/alldata/" + QString::number(id_card); //mites sukunimi??
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getOwnerInfoManager = new QNetworkAccessManager(this);

    connect(getOwnerInfoManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getOwnerInfoSlot(QNetworkReply*)));
    reply = getOwnerInfoManager->get(request);
}

void DebitWindow::getsavingsmode()
{
    emit askSaveMode();
}

void DebitWindow::startwindowtimer()
{
    timer10sek->start(1000);
}

void DebitWindow::getBalanceSlot(QNetworkReply *reply)
{
    account_balance_data=reply->readAll();
    qDebug()<<"TILITIEDOT : "+account_balance_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(account_balance_data);
    QJsonObject json_obj = json_doc.object();
    QString balancedata;
    int balance;
    balancedata=QString::number(json_obj["account_balance"].toInt());
    balance=balancedata.toInt();
    currentBalance=balance;
    qDebug()<<"Kortin saldo on  " <<balance;

    ui->label_balance->setText("Your account balance is: "+ QString::number(balance));
    getowner();
}

void DebitWindow::getwithdrawdataSlot(QNetworkReply *reply)
{
    withdraw_data=reply->readAll();
    qDebug()<<"DATA : "+withdraw_data;
    getbalance();
    timer10sek->stop();
    emit nextwindow(6);
    this->close();
    /*QJsonDocument json_doc = QJsonDocument::fromJson(withdraw_data);
        QJsonObject json_obj = json_doc.object();    // Tätä menetelmää voi käyttää kun vastauksena on 1 objekti
        int test=currentBalance;// Jos vastaus on array (esim logs), käytä QBYTEARRAY
        test=json_obj["affectedRows"].toInt();
        debitwithdrawmanager->deleteLater();
        if(test>currentBalance){
            timer10sek->stop();
            emit nextwindow(6);
            this->close();
            getbalance();
        }
        if(test==currentBalance){
            resets();
            ui->label_error->setText("Insufficient funds");
            getbalance();
        }*/
}

void DebitWindow::showUI()
{
    resets();
    this->show();
}

void DebitWindow::customAmount(int amount)
{
    this->show();
    resets();
    withdraw(amount);
}

void DebitWindow::receiveSaveModeSlot(int save)
{
 savingsmode=save;
}

void DebitWindow::withdraw(int amount)
{
    if((currentBalance-amount-((amount/100)*savingsmode))>=0){
    // HAKEE DEBITBALANCEN TIETOKANNASTA
    QString site_url="http://localhost:3000/card/debitwithdraw";
    QNetworkRequest request((site_url));

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    QJsonObject jsonObj;  // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("id_card",id_card);
    jsonObj.insert("amount",amount);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    debitwithdrawmanager = new QNetworkAccessManager(this);
    connect(debitwithdrawmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getwithdrawdataSlot(QNetworkReply*)));
    reply = debitwithdrawmanager->post(request,QJsonDocument(jsonObj).toJson());
    }
    else {
        resets();
        ui->label_error->setText("Insufficient funds");
    }
}

void DebitWindow::getOwnerInfoSlot(QNetworkReply *reply)
{
    owner_data=reply->readAll();
    qDebug()<<"DATA : "+owner_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(owner_data);
    QJsonObject json_obj = json_doc.object();
    QString ownerfname = json_obj["fname"].toString();
    QString ownerlname = json_obj["lname"].toString();
    QString address = json_obj["address"].toString();
    QString phonenumber = json_obj["phonenumber"].toString();
    QString email = json_obj["email"].toString();
    QString ownerInfo =
            "Account owner: " + ownerfname + " " + ownerlname + "\n" +
            "Address: " + address + "\n" +
            "Phonenumber: " + phonenumber + "\n"
            "Email: " + email + "\n";
    ui->label_info->setText(ownerInfo);
}

void DebitWindow::on_btn20_clicked()
{
    time10=0;
    resets();
    withdraw(20);
}


void DebitWindow::on_btn40_clicked()
{
    time10=0;
    resets();
    withdraw(40);

}


void DebitWindow::on_btn60_clicked()
{
    time10=0;
    resets();
    withdraw(60);

}


void DebitWindow::on_btn100_clicked()
{
    time10=0;
    resets();
    withdraw(100);
}


void DebitWindow::on_btn200_clicked()
{
    time10=0;
    resets();
    withdraw(200);
}


void DebitWindow::on_btn500_clicked()
{
  time10=0;
  resets();
  withdraw(500);
}


void DebitWindow::on_btnBack_clicked()
{
    timer10sek->stop();
    emit backtomainmenu();
    this->close();
}

void DebitWindow::timer10Slot()
{
    time10++;
    if (time10>10){
        timer10sek->stop();
        emit backtomainmenu();
        this->close();
    }
}

void DebitWindow::on_btnOther_clicked()
{
        amountWindow = new DebitAmountWindow(this);
        connect(amountWindow, SIGNAL(customAmount(int)), this, SLOT(customAmount(int)));
        connect(amountWindow, SIGNAL(back()), this, SLOT(showUI()));
        amountWindow->show();
        resets();
        this->hide();
}

