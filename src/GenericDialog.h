#ifndef GENERICDIALOG_H
#define GENERICDIALOG_H

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
#include "Database.h"
#include <QAbstractItemView>
#include <QTimer>
#include <QDateTimeEdit>

#include "Database.h"


class GenericDialog : public QDialog
 {
    Q_OBJECT

public:
    explicit GenericDialog(QWidget *parent=0);
    void setform();

private slots:
   void soumettre_op();
   void annuler_op();

private:

    QLineEdit    *login;
    QLineEdit    *password;  
    QLineEdit    *password1;
    QLineEdit    *matricule;
    QPushButton  *valid;
    QPushButton *annuler;
    QFormLayout  *form;
    QHBoxLayout   *horizontal;
    QVBoxLayout   *layout;
    QGroupBox *box;
    QGridLayout *grid;

};


#endif // GENERICDIALOG_H
