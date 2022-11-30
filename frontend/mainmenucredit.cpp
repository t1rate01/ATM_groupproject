#include "mainmenucredit.h"
#include "ui_mainmenucredit.h"

mainmenucredit::mainmenucredit(QString t, int cid,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainmenucredit)
{
    ui->setupUi(this);
   token = t;
   id_card = cid;
}

mainmenucredit::~mainmenucredit()
{
    delete ui;
}

void mainmenucredit::cleardata()
{
 id_card=0;
 token="";
}
