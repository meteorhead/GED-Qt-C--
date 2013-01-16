#ifndef MENUAJOUTER_H
#define MENUAJOUTER_H

#include <QWidget>
#include "ajouteringredient.h"
#include "menuajouterproduit.h"


namespace Ui {
    class MenuAjouter;
}

class MenuAjouter : public QWidget
{
    Q_OBJECT


    
public:
    explicit MenuAjouter(QWidget *parent = 0);
    Ui::MenuAjouter *ui;
    ~MenuAjouter();

public slots:

    void demarrerAjouterIngredients();


private:
 AjouterIngredient *ajouting;
 //MenuAjouterProduit *ajoutprod;

};

#endif // MENUAJOUTER_H
