#include "debitbalance.h"
#include "ui_debitbalance.h"
#include <QDebug>

Debitbalance::Debitbalance(QString givenToken, int idcard, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Debitbalance)

{
    connect(timer10sek,SIGNAL(timeout()),this,SLOT(timer10Slot()));
    timer10sek->start(1000);
    ui->setupUi(this);
    token = givenToken;
    id_card = idcard;
//    account_balance = debitbalance;

    // HAKEE DEBITBALANCEN TIETOKANNASTA
    QString site_url="http://localhost:3000/account/account_balance";
    QNetworkRequest request((site_url));

    getdebitbalancemanager = new QNetworkAccessManager(this);

    QJsonObject jsonObj;  // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("account_balance",account_balance);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(getdebitbalancemanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getdebitbalanceSlot(QNetworkReply*)));
    reply = getdebitbalancemanager->post(request, QJsonDocument(jsonObj).toJson());

}

Debitbalance::~Debitbalance()
{
    delete ui;
}

void Debitbalance::getdebitbalanceSlot(QNetworkReply *reply)
{
    debitbalance_data=reply->readAll();
    qDebug()<<"DATA : "+debitbalance_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(debitbalance_data);
        QJsonObject json_obj = json_doc.object();    // Tätä menetelmää voi käyttää kun vastauksena on 1 objekti
        QString debitbalancedata;                           // Jos vastaus on array (esim logs), käytä QBYTEARRAY
        debitbalancedata=json_obj["account_balance"].toString();
        qDebug()<<"Debit saldo on  " <<debitbalancedata;
        ui->label_debitbalance->setText("Your debit balance is:\n" + debitbalancedata+ " €.");
}


void Debitbalance::timer10Slot()
{
    time10++;
    if (time10>10){
        timer10sek->stop();
        emit backtomainmenu();
        this->close();
    }
}
