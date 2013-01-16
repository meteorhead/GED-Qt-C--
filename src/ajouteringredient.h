#ifndef AJOUTERINGREDIENT_H
#define AJOUTERINGREDIENT_H

#include <QDialog>
#include "Database.h"
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
    class AjouterIngredient;
}

class AjouterIngredient : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterIngredient(QWidget *parent = 0);
    ~AjouterIngredient();

private slots:
    void valider_ajouter();

private:
    Ui::AjouterIngredient *ui;

};

#endif // AJOUTERINGREDIENT_H
