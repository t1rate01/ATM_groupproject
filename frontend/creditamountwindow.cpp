#include "creditamountwindow.h"
#include "ui_creditamountwindow.h"

CreditAmountWindow::CreditAmountWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditAmountWindow)
{
    ui->setupUi(this);
}

CreditAmountWindow::~CreditAmountWindow()
{
    delete ui;
}

void CreditAmountWindow::on_withdraw_btn_clicked()
{
    emit customAmount(ui->withdraw_amount->text().toInt());
    this->close();
}


void CreditAmountWindow::on_back_btn_clicked()
{
    emit back();
    this->close();
}

