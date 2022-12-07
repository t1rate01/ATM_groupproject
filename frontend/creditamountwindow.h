#ifndef CREDITAMOUNTWINDOW_H
#define CREDITAMOUNTWINDOW_H
#include <QDialog>

namespace Ui {
class CreditAmountWindow;
}

class CreditAmountWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreditAmountWindow(QWidget *parent = nullptr);
    ~CreditAmountWindow();

signals:
    void customAmount(int);
    void back();

private slots:
    void on_withdraw_btn_clicked();

    void on_back_btn_clicked();

private:
    Ui::CreditAmountWindow *ui;
};

#endif // CREDITAMOUNTWINDOW_H
