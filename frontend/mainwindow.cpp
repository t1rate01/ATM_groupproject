#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_login_clicked()
{

    cardnumber = ui->lineEdit_cardnum->text();
    password = ui->lineEdit_password->text();
    qDebug()<<cardnumber + " " + password;
    if(cardnumber.length()<3){
        ui->label_loginresponse->setText("Please enter a valid cardnumber");
        ui->lineEdit_cardnum->clear();
        ui->lineEdit_password->clear();
    }
    else if (password.length()<1){
        ui->label_loginresponse->setText("Please enter a valid password");
        ui->lineEdit_cardnum->clear();
        ui->lineEdit_password->clear();
    }
    else {

    QJsonObject jsonObj;
    jsonObj.insert("cardnumber",cardnumber);
    jsonObj.insert("password",password);

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    if (response_data.length() > 20 && response_data != "false"){
    token = response_data;
        qDebug()<<"Token on " + token;
        ui->label_loginresponse->setText("Login succesful, opening menu...");          
         // mainmenu = new MainMenu(token, cardnumber); kokeilu tehdä sessionin construktorissa
        sessio = new session(token, cardnumber);
        // mainmenu->show();
        //this->close();  ehkä myös delete this, mieti toteutusta
        reply->deleteLater();
        loginManager->deleteLater();
    }
    else {
        qDebug()<< response_data;
        ui->label_loginresponse->setText(response_data);
    }


}


