#include "menuajouterproduit.h"
#include "ui_menuajouterproduit.h"
#include "ajouterproduit.h"
#include "ui_ajouterproduit.h"

MenuAjouterProduit::MenuAjouterProduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuAjouterProduit)
{
    ui->setupUi(this);
    setWindowTitle("Ajouter Produit");
    
     resultatAjout = false;
    QObject::connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(valider_ajouter()));
    QObject::connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(close()));
    
}

MenuAjouterProduit::~MenuAjouterProduit()
{
    delete ui;
}


void MenuAjouterProduit::valider_ajouter()
{ int id = -1;
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"Erreur","Veuillez entrer un nom de produit à ajouter",QMessageBox::Ok);
        return;
    }
    else
    {
        QString str = ui->lineEdit->text();
        QSqlQuery requete(QString("SELECT id FROM produit where Nom_Produit = ").append("\""+str+"\""));
        while(requete.next())
        {
            id = requete.value(0).toInt();
            

        }
        if (id == -1)
        {  int choix = QMessageBox::question(this,"Notice!",(QString("Etes vous sûrs de vouloir ajouter le produit").append("\""+str+"\"")),QMessageBox::Yes,QMessageBox::No);
                    if (choix == QMessageBox::Yes )
                    {
                    QSqlQuery query;
                    query.prepare("INSERT INTO produit (Nom_Produit) "
                           "VALUES (:produit)");
                    query.bindValue(":produit", ui->lineEdit->text());

                    bool ok = query.exec();
                    if (ok)
                    {
                        QMessageBox::information(this,"info!","Ajout effectué avec succès",QMessageBox::Ok);                        
                        //ajouter ici refresh combobox produits 
			nomProduit = ui->lineEdit->text();
                        ui->lineEdit->text().clear();
		        resultatAjout = true;
                        emit signalToUpdateCombo();

                    }
                    else
		      resultatAjout = false;
                    }
                    if (choix == QMessageBox::No)
                        return;

        }
                    else if (id > -1)
                    {
                        QMessageBox::critical(this,"Erreur!","Le produit existe déjà!",QMessageBox::Ok);
                        return;
                    }

           }
     }
