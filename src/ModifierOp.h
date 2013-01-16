#ifndef MODIFIEROP_H
#define MODIFIEROP_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>
#include <QGridLayout>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QCompleter>
#include "Database.h"



class ModifierOp : public QWidget

{
    Q_OBJECT
public:

    explicit ModifierOp(QWidget *parent=0);
    QPushButton *valider;
    QPushButton *retour;
    void setCompleter();
    QLineEdit    *login;
     QCompleter *completeop;
     QLineEdit    *password;
     QLineEdit    *matricule;

private slots:


private:



    QFormLayout  *form;
    QHBoxLayout   *horizontal;
    QVBoxLayout   *layout;
    QGroupBox *box;
    QGridLayout *grid;
    QSqlTableModel *model;





};


#endif // MODIFIEROP_H
