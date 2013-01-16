#ifndef SUPPRIMEROP_H
#define SUPPRIMEROP_H

#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QSqlTableModel>
#include <QWidget>
#include "Database.h"
#include <QCompleter>
#include <QSqlQuery>

class SupprimerOp : public QWidget

{
    Q_OBJECT
public:

    explicit SupprimerOp(QWidget *parent=0);
    QPushButton *supprimer;
    QPushButton *back;
    QLineEdit    *login;
     QCompleter *completeop;
     QLineEdit    *matricule;
     void setCompleter();

private slots:


private:



    QFormLayout  *form;
    QHBoxLayout   *horizontal;
    QVBoxLayout   *layout;
    QGroupBox *box;
    QGridLayout *grid;
    QSqlTableModel *model;





};


#endif // SUPPRIMEROP_H
