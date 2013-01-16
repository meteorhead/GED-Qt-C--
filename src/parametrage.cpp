#include "parametrage.h"
#include "ui_parametrage.h"

parametrage::parametrage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parametrage)
{
    ui->setupUi(this);

    QSqlQuery querystephan("SELECT Distinct stephan from enregistrements");
                    while(querystephan.next())
                        ui->combostephan->addItem(querystephan.value(0).toString());

    QSqlQuery queryproduct("SELECT Distinct Nom_Produit from enregistrements");
                    while(queryproduct.next())
                        ui->comboproduit->addItem(queryproduct.value(0).toString());

}

parametrage::~parametrage()
{
    delete ui;
}
