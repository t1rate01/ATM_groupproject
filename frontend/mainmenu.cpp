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

