#include "demowindow.h"
#include "ui_demowindow.h"

demowindow::demowindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::demowindow)
{
    ui->setupUi(this);
}

demowindow::~demowindow()
{
    delete ui;
}
