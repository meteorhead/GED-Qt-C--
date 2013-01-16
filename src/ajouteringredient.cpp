#include "ajouteringredient.h"
#include "ui_ajouteringredient.h"

AjouterIngredient::AjouterIngredient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterIngredient)
{
    ui->setupUi(this);
    setWindowTitle("Ajouter Ingredient");


    QObject::connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(valider_ajouter()));
    QObject::connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(close()));
}

AjouterIngredient::~AjouterIngredient()
{
    delete ui;
}



void AjouterIngredient::valider_ajouter()
{ int id = -1;
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"Erreur","Veuillez entrer un nom d'ingrédient à ajouter",QMessageBox::Ok);
        return;
    }
    else
    {
        QString str = ui->lineEdit->text();
        QSqlQuery requete(QString("SELECT id FROM produit where ingredients = ").append("\""+str+"\""));
        while(requete.next())
        {
            id = requete.value(0).toInt();

        }
        if (id == -1)
        {  int choix = QMessageBox::question(this,"Notice!",(QString("Etes vous surs de vouloir ajouter l\'ingredient ").append("\""+str+"\"")),QMessageBox::Yes,QMessageBox::No);
                    if (choix == QMessageBox::Yes )
                    {
                    QSqlQuery query;
                    query.prepare("INSERT INTO ingredients (ingredients) "
                           "VALUES (:ing)");
                    query.bindValue(":ing", ui->lineEdit->text());

                    bool ok = query.exec();
                    if (ok)
                    {
                        QMessageBox::information(this,"info!","Ajout effectué avec succès",QMessageBox::Ok);
                        ui->lineEdit->text().clear();

                    }
                    }
                    if (choix == QMessageBox::No)
                        return;

                    }
         else
                    {
            QMessageBox::critical(this,"Erreur!","L\'ingredient existe déjà!",QMessageBox::Ok);
                        return;
                    }

           }
     }


