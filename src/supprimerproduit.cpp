#include "supprimerproduit.h"
#include "ui_supprimerproduit.h"

SupprimerProduit::SupprimerProduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SupprimerProduit)
{
    ui->setupUi(this);
    setWindowTitle("Supprimer Produit");
    table = new QSqlQueryModel;
    ui->comboproduit->clear();
    QSqlQuery stephan("SELECT DISTINCT Nom_Produit from produit where Nom_Produit != \"\" ");
    while(stephan.next())
             ui->comboproduit->addItem(stephan.value(0).toString());

    QObject::connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(valider_supprimer()));
    QObject::connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(close()));
    QObject::connect(ui->comboproduit,SIGNAL(activated(QString)),this,SLOT(refreshrecettes()));
}

SupprimerProduit::~SupprimerProduit()
{
    delete ui;
}

void SupprimerProduit::valider_supprimer()
{if(ui->checkBox->isChecked())
      {
        int choix = QMessageBox::question(this,"Notice!",(QString("Voulez vous supprimer la recette").append("\""+ui->comborecette->currentText()+"\"").append("ainsi que le produit ").append("\""+ui->comboproduit->currentText()+"\"")),QMessageBox::Yes,QMessageBox::No);

        if (choix == QMessageBox::Yes)
        {   QString null = "NULL";
            table->setQuery(QString("UPDATE produit SET Id_Recette = null WHERE Nom_Produit = ").append("\""+ui->comboproduit->currentText()+"\"").append(" AND Id_Recette =").append("\""+ui->comborecette->currentText()+"\""));
            table->setQuery(QString("UPDATE produit SET Nom_Produit = null WHERE Nom_Produit = ").append("\""+ui->comboproduit->currentText()+"\""));
            int i = -1;
            QSqlQuery verif(QString("SELECT Nom_Produit,Id_Recette FROM produit WHERE Nom_Produit = ").append("\""+ui->comboproduit->currentText()+"\"").append(" AND Id_Recette = ").append("\""+ui->comborecette->currentText()+"\""));
            while (verif.next())
            {
                i++;

            }
            if (i==-1)
            QMessageBox::information(this,"Notice","La recette a été supprimée avec succès",QMessageBox::Ok);
	    emit signalToUpdateCombo();

        }
        if (choix == QMessageBox::No)

            return;
    }
        else
        {
        int choix = QMessageBox::question(this,"Notice",QString("Voulez vous supprimer la recette ").append("\""+ui->comborecette->currentText()+"\" ?"),QMessageBox::Yes,QMessageBox::No);

        if (choix == QMessageBox::Yes)
        {
        table->setQuery(QString("UPDATE produit SET Id_Recette = null WHERE Nom_Produit = ").append("\""+ui->comboproduit->currentText()+"\"").append(" AND Id_Recette = ").append("\""+ui->comborecette->currentText()+"\""));
        int i = -1;
        QSqlQuery verif(QString("SELECT DISTINCT Id_Recette FROM produit WHERE ID_Recette != \"\" AND Nom_Produit = ").append("\""+ui->comboproduit->currentText()+"\"").append(" AND Id_Recette = ").append("\""+ui->comborecette->currentText()+"\""));
        while (verif.next())
        {
            i++;

        }
        if (i==-1)
        QMessageBox::information(this,"Notice","La recette a été supprimée avec succès",QMessageBox::Ok);
	
	emit signalToUpdateCombo();

         }
        if (choix == QMessageBox::No)
            return;

        }
    }


void SupprimerProduit::refreshrecettes()
{
    QString str = ui->comboproduit->currentText();
    ui->comborecette->clear();

    QSqlQuery recette(QString("Select Id_Recette from produit where Nom_Produit =").append("\""+str+"\"").append(" AND Id_Recette != \"\" ORDER BY id DESC LIMIT 1"));
    while(recette.next())
    {
        ui->comborecette->addItem(recette.value(0).toString());
    }


}
void SupprimerProduit::refreshProduits()
{
  
ui->comboproduit->clear();
QSqlQuery stephan("SELECT DISTINCT Nom_Produit from produit WHERE Nom_Produit != \"\" ");
         while(stephan.next())
             ui->comboproduit->addItem(stephan.value(0).toString());
}
