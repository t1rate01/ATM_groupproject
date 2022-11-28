#ifndef MAINMENUCREDIT_H
#define MAINMENUCREDIT_H

#include <QMainWindow>


namespace Ui {
class mainmenucredit;
}

class mainmenucredit : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainmenucredit(QString, int, QWidget *parent = nullptr);
    ~mainmenucredit();

private:
    Ui::mainmenucredit *ui;
    QString token;
    int id_card;
};

#endif // MAINMENUCREDIT_H
