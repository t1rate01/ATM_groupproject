#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>

MainMenu::MainMenu(QString t,int idcard, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    token = t;
    ui->label_tokendemo->setText(token);  // POISTA MYÖHEMMIN TÄSSÄ NÄKYY TOKEN
    id_card = idcard;



   /* QString data_url="http://localhost:3000/card/cid";
    QNetworkRequest request((data_url));
    //WEBTOKEN ALKU
    QByteArray myToken = "Bearer "+ token.toLocal8Bit();   // Arrayhyn menevä käännös
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    QJsonObject jsonObj;
    jsonObj.insert("cardnumber",cnum);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    postManager = new QNetworkAccessManager(this);

    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getDataSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson()); */    /// SINGLETONIIIN JA LAITA DELAYTA
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::getDataSlot(QNetworkReply *reply)
{

}

void MainMenu::on_btn_Cardidhaku_clicked()
{
 emit resettimer30();
}

