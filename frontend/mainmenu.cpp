#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>

MainMenu::MainMenu(QString t,int idcard, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    token = t;
    id_card = idcard;
    timer10 = new QTimer;
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::resetAllTimers()
{
    sessiontime10=0;
    emit resettimer30();
}

void MainMenu::timer10slot()
{
    sessiontime10++;
    if (sessiontime10){
        emit timer10isup();
    }
}


