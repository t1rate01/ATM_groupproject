#include "session.h"
#include <QDebug>
#include <QObject>

session::session(QString token, QString cardnumber)
{
 sessiontoken=token;
 sessioncardnumber=cardnumber;
 qDebug()<< "sessionin token on " + sessiontoken;
 getidcard();

 // TIMERI 30SEK
session30timer=new QTimer;
session30timer->start(1000);
connect(session30timer,SIGNAL(timeout()), this, SLOT(timer30slot()));
}

void session::getidcard()                   // HAKEE ID_CARDIN CARDNUMBERIN PERUSTEELLA
{
    QString site_url="http://localhost:3000/card/cid";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+sessiontoken.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getsessioncardmanager = new QNetworkAccessManager(this);  // toiminnoille jokaiselle oma manageri (?)

    QJsonObject jsonObj;  // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("cardnumber",sessioncardnumber);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");  // requestin headeri, tarvitsee jotta url encoded muoto kuten loginissa
                                                                                // tarvitseeko olla juuri application/json, miksi ?
    connect(getsessioncardmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getCardIDSlot(QNetworkReply*)));

    reply = getsessioncardmanager->post(request, QJsonDocument(jsonObj).toJson());
}

void session::getandcheckcredit()                   // HAKEE KORTIN CREDITIN ID_CARD PERUSTEELLA
{
    QString site_url="http://localhost:3000/card/cred";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+sessiontoken.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getcreditmanager = new QNetworkAccessManager(this);
    QJsonObject jsonObj;

    jsonObj.insert("id_card",id_card);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");  // requestin headeri, tarvitsee jotta url encoded muoto kuten loginissa

    connect(getcreditmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getCreditSlot(QNetworkReply*)));

    reply = getcreditmanager->post(request, QJsonDocument(jsonObj).toJson());
}



void session::getCardIDSlot(QNetworkReply *reply)   // ID CARDIN SAANTI SESSIONILLE
{                                                   // MAIN MENU LUONTI JA TOKEN JA ID_CARD VÄLITYS
     cardresponse_data=reply->readAll();
     qDebug()<<"DATA : "+cardresponse_data;

     QJsonDocument json_doc = QJsonDocument::fromJson(cardresponse_data);
         QJsonObject json_obj = json_doc.object();
         QString id_carddata;
         id_carddata=QString::number(json_obj["id_card"].toInt());
         id_card=id_carddata.toInt();  /// !!!!!!!!!!!!!!!!!!!!
         qDebug()<<"Id card intti on = " <<id_card;


         getsessioncardmanager->deleteLater();   // POISTA KERTAKÄYTTÖ ACCESS OLIO

         getandcheckcredit();   // KUTSU HETI UUTTA POST FUNKTIOTA
}

void session::getCreditSlot(QNetworkReply *reply)   // VASTAANOTTAA CREDITIN, PÄÄTTÄÄ KUMPI
                                                    // MAINMENU AUKEAA
{
    creditresponse_data=reply->readAll();
    qDebug()<<"DATA : "+creditresponse_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(creditresponse_data);
        QJsonObject json_obj = json_doc.object();
        QString creditdata;
        creditdata=QString::number(json_obj["credit"].toInt());
        credit=creditdata.toInt();  /// !!!!!!!!!!!!!!!!!!!!
        qDebug()<<"Creditti inttinä on = " <<credit;
        reply->deleteLater();
        getcreditmanager->deleteLater();

        if(credit == 0){
            mainmenu = new MainMenu(sessiontoken, id_card);  // DEBIT MAIN MENU
            mainmenu->show();
            connect(mainmenu,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
        }
        if(credit > 0) {
            creditmenu = new mainmenucredit(sessiontoken, id_card);  // DEBIT CREDIT MAIN MENU
            creditmenu->show();
        }

}

void session::resettimerslot()    // Signaalislot johon valikko-olioiden resetsignaali kytketään
{
 timer30=0;
}

void session::timer30slot()     // perus QTimerin signaalislotti
{
    timer30++;
    qDebug()<<"Session time is " << timer30;

    // TEE TOIMINTO JOLLA 30SEK TÄYTTYESSÄ ISTUNTO TIETOINEEN NOLLATAAN
}




