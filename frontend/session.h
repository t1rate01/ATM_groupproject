#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "mainmenu.h"
#include "mainmenucredit.h"
#include <QTimer>

class session : public QObject
{
    Q_OBJECT
public:
    session(QString, QString);
    void getidcard();
    void getandcheckcredit();

private:
    QString sessiontoken;
    QString sessioncardnumber;
    int id_card;
    int credit;
    int timer30=0;
    QNetworkAccessManager * getsessioncardmanager; // sessionin id card hakua varten
    QNetworkAccessManager * getcreditmanager;
    QByteArray creditresponse_data;
    QNetworkReply *reply;
    QByteArray cardresponse_data;
    MainMenu * mainmenu;
    mainmenucredit * creditmenu;
    QTimer * session30timer;
signals:
private slots:
    void getCardIDSlot (QNetworkReply *reply);
    void getCreditSlot (QNetworkReply *reply);
    void resettimerslot();
    void timer30slot();



};

#endif // SESSION_H
