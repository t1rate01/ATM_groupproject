#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>


namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QString, int, QWidget *parent = nullptr);
    ~MainMenu();
    void getData();
    int id_card;
signals:
    void resettimer30();

private:
    Ui::MainMenu *ui;
    QString token;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
private slots:
    void getDataSlot (QNetworkReply *reply);
    void on_btn_Cardidhaku_clicked();
};

#endif // MAINMENU_H
