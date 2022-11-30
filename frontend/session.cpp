#include "session.h"
#include <QDebug>
#include <QObject>

session::session(QString token, QString cardnumber)    // KONSTRUKTORI
{
 sessiontoken=token;                            //TALLENTAA ITSELLEEN LOGINISTA (MAINWINDOW) SAADUT TOKEN JA CARDNUMBER
 sessioncardnumber=cardnumber;
 qDebug()<< "sessionin token on " + sessiontoken;
 getidcard();                   // KUTSUU FUNKTION JOSSA ID_CARD HAKU

 // TIMERI 30SEK
session30timer=new QTimer;
session30timer->start(1000);  // NORMI 30SEK TIMERI JA KYTKENTÄ
connect(session30timer,SIGNAL(timeout()), this, SLOT(timer30slot()));
}

void session::getidcard()                   // HAKEE ID_CARDIN CARDNUMBERIN PERUSTEELLA,
{                                           // VASTAUS TULEE SLOTTIIN getCardIDSlot()
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
{                                                       // VASTAUS TULEE SLOTTIIN getCreditSlot();
    QString site_url="http://localhost:3000/card/cred";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+sessiontoken.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    getcreditmanager = new QNetworkAccessManager(this);  // Olion luonti, muista poistaa (?)
    QJsonObject jsonObj;                                // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("id_card",id_card);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");  // requestin headeri, tarvitsee jotta url encoded muoto kuten loginissa

    connect(getcreditmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getCreditSlot(QNetworkReply*)));    // KYTKEE VASTAUSSIGNAALIN VASTAUSSLOTTIIN
                                                                                                          // VASTAUSSIGNAALI SISÄLTÄÄ DATAN (*REPLY)
    reply = getcreditmanager->post(request, QJsonDocument(jsonObj).toJson());
}


void session::getCardIDSlot(QNetworkReply *reply)   // ID CARDIN SAANTI SESSIONILLE
{                                                   // KUTSUU CREDIT TIEDONHAKUFUNKTION
     cardresponse_data=reply->readAll();
     qDebug()<<"DATA : "+cardresponse_data;

     QJsonDocument json_doc = QJsonDocument::fromJson(cardresponse_data);
         QJsonObject json_obj = json_doc.object();    // Tätä menetelmää voi käyttää kun vastauksena on 1 objekti
         QString id_carddata;                           // Jos vastaus on array (esim logs), käytä QBYTEARRAY
         id_carddata=QString::number(json_obj["id_card"].toInt());
         id_card=id_carddata.toInt();  // Muoto jolla saa vastausdatasta tallennettua tämän olion int muuttujaan arvon
         qDebug()<<"Id card intti on = " <<id_card;


         getsessioncardmanager->deleteLater();   // POISTA KERTAKÄYTTÖ ACCESS OLIO (?)

         getandcheckcredit();   // KUTSU HETI UUTTA POST FUNKTIOTA CREDITIN SAAMISEKSI
}

void session::getCreditSlot(QNetworkReply *reply)   // VASTAANOTTAA CREDITIN, PÄÄTTÄÄ KUMPI
                                                    // MAINMENU AUKEAA JA AVAA
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
            currentwindow=1;
            mainmenu = new MainMenu(sessiontoken, id_card);  // DEBIT MAIN MENU, VÄLITÄ NÄMÄ SAMAT TIEDOT AINA KUN AVAAT IKKUNAOLION
            mainmenu->show();
            connect(mainmenu,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
            connect(mainmenu,SIGNAL(timer10isup()),this,SLOT(backtomainmenu()));// IKKUNA AVATESSA AINA SIGNAALI KYTKETTÄVÄ
        }                                                                          // MUUTA VAIN "mainmenu" OMAN IKKUNAN NIMEKSI ja nimeä signaalisi "resettimer30()"
        if(credit > 0) {
            currentwindow=2;
            creditmenu = new mainmenucredit(sessiontoken, id_card);  // DEBIT CREDIT MAIN MENU, VÄLITÄ NÄMÄ SAMAT TIEDOT AINA KUN AVAAT IKKUNAOLION
            creditmenu->show();

            // TÄNNE TULEE SAMAT IKKUNANAVAUS KYTKENN*T JA VÄLITYKSET
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

    if(timer30>30){
        switch(currentwindow){
        case 0:
            delete this;
            break;
        case 1:
            delete mainmenu;
            delete this;// mainmenu 1 timeout
            break;
        case 2:
            delete creditmenu;
            delete this;// mainmenu credit 2 timeout
            break;
        }
    }

    // TEE ERILLINEN FUNKTIO JOLLA 30SEK TÄYTTYESSÄ/LOGOUT PAINAESSA ISTUNTO TIETOINEEN NOLLATAAN
    // KUTSU TÄSSÄ 30SEK TÄYTYTTYÄ KYSEISTÄ FUNKTIOTA
}

void session::backtomainmenu()
{
    if(credit==0){
        mainmenu->show();
        currentwindow=1;
    }
    if(credit>0){
        creditmenu->show();
        currentwindow=2;
    }
}




