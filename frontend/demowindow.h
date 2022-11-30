#ifndef DEMOWINDOW_H
#define DEMOWINDOW_H

#include <QMainWindow>

namespace Ui {
class demowindow;
}

class demowindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit demowindow(QWidget *parent = nullptr);
    ~demowindow();

private:
    Ui::demowindow *ui;
};

#endif // DEMOWINDOW_H
