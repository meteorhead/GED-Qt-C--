#include "menuajouter.h"
#include "ui_menuajouter.h"

MenuAjouter::MenuAjouter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuAjouter)
{
    ui->setupUi(this);
      
    
    
    connect(ui->ajouterIngredient,SIGNAL(clicked()),this,SLOT(demarrerAjouterIngredients()));
 
}

MenuAjouter::~MenuAjouter()
{
    delete ui;
}


void MenuAjouter::demarrerAjouterIngredients()
{
    ajouting = new AjouterIngredient(this);
    ajouting->exec();

}



