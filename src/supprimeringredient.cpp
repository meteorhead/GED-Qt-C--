#include "supprimeringredient.h"
#include "ui_supprimeringredient.h"

supprimeringredient::supprimeringredient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supprimeringredient)
{
    ui->setupUi(this);
    setWindowTitle("Supprimer Ingrédients");
 
    table = new QSqlQueryModel;

    QSqlQuery requete("SELECT DISTINCT ingredients FROM ingredients where ingredients != \"\"");
    while(requete.next())
    {
      ui->comboIngredients->addItem(requete.value(0).toString());
    }
    QObject::connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(valider_supprimer()));
    QObject::connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(close()));

}

supprimeringredient::~supprimeringredient()
{
    delete ui;
}

void supprimeringredient::valider_supprimer()
{
    int choix = QMessageBox::question(this,"Notice!","Voulez vous supprimer l\'ingredient suivant ?",QMessageBox::Yes,QMessageBox::No);

        if (choix == QMessageBox::Yes)
        {
            table->setQuery(QString("UPDATE ingredients SET ingredients = null WHERE ingredients = ").append("\""+ui->comboIngredients->currentText()+"\""));
            QSqlQuery verif(QString("SELECT ingredients FROM ingredients WHERE ingredients.ingredients != \"\" AND ingredients = ").append("\""+ui->comboIngredients->currentText()+"\""));
            int i = -1;
            while (verif.next())
            {
                i++;

            }
            if (i == -1)
	    {
                QMessageBox::information(this,"Notice","L\'ingredient a été supprimé avec succès",QMessageBox::Ok);
		QSqlQuery requete("SELECT DISTINCT ingredients FROM produit where ingredients != \"\"");
    while(requete.next())
    {
      ui->comboIngredients->addItem(requete.value(0).toString());
    }
		
	    }

             }
            if (choix == QMessageBox::No)
                return;



}
