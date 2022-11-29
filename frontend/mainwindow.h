#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainmenu.h>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "session.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int id_card;
    QString cardnumber;
    QString password;
    QString token;
signals:
    void reset30timer();

private slots:
    void on_btn_login_clicked();
    void loginSlot (QNetworkReply *reply);   // loginiin

private:
    Ui::MainWindow *ui;
    session * sessio;
    MainMenu * mainmenu;
    QNetworkAccessManager * loginManager;// loginia varten
    QNetworkReply *reply;
    QByteArray response_data;

};
#endif // MAINWINDOW_H
