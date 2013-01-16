#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlQuery>
#include <QPushButton>
#include "Database.h"
#include <QLineEdit>
#include <QKeyEvent>


namespace Ui {
    class Login;
}

class Login : public QWidget
{
    Q_OBJECT
signals:
  void triggerUnderground();
public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    QPushButton *connexion;
    QString operateur;
    Ui::Login *ui;
    virtual bool eventFilter(QObject*connex , QEvent* e);


public slots:
    bool check();
    void eraserHead();


private:

    QString id;



};

#endif // LOGIN_H
