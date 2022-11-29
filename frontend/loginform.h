#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>

namespace Ui {
class LoginForm;
}

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
