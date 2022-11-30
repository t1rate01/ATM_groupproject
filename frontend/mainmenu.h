#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QTimer>


namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QString, int, QWidget *parent = nullptr);
    ~MainMenu();
    int sessiontime10=0;
    void resetAllTimers();
    void cleardata();

signals:
    void resettimer30();
    void timer10isup();

private:
    QTimer * timer10;
    Ui::MainMenu *ui;
    int id_card;
    QString token;

private slots:
    void timer10slot();
};

#endif // MAINMENU_H
