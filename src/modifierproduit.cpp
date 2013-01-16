#include "modifierproduit.h"
#include "ui_modifierproduit.h"

ModifierProduit::ModifierProduit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifierProduit)
{
    ui->setupUi(this);

    modeltheo = new QSqlTableModel;
    modeltheo->setTable("produit");
    prod = new ModelProduit;



    //ui->tabingredients->setModel(modelquery);
    QSqlQuery queryproduct("SELECT DISTINCT Nom_Produit from produit where Nom_Produit != \"\" ");
            while(queryproduct.next())
            {
                ui->comboproduit->addItem(queryproduct.value(0).toString());

             }


            QObject::connect(ui->comboproduit,SIGNAL(activated(QString)),this,SLOT(refreshproduit(QString)));
            QObject::connect(ui->comborecette,SIGNAL(activated(QString)),this,SLOT(refreshRecettes(QString)));

}

QString ModifierProduit::nomprod = " ";

ModifierProduit::~ModifierProduit()
{
    delete ui;
}

void ModifierProduit::refreshproduit(QString produit)
{

    ////////////////////////////////// Tab produit /////////////////////////////////////////////



        QSqlQuery recette(QString("SELECT DISTINCT Id_Recette from produit WHERE Id_Recette != \"\"  AND Nom_Produit = ").append("\""+ui->comboproduit->currentText()+"\""));
        ui->comborecette->clear();
        while(recette.next())
                {

                       ui->comborecette->addItem(recette.value(0).toString());
                       ui->comborecette->setEditable(true);

                 }





}

void ModifierProduit::refreshRecettes(QString recette)
{

    QSqlQuery idExtract(QString("SELECT id FROM produit WHERE Nom_Produit = ").append("\""+ui->comboproduit->currentText()+"\"").append(" AND Id_Recette = ").append("\""+recette+"\""));
            while(idExtract.next())
    {
                idproduit = idExtract.value(0).toString();
    }

   prod->setQuery(QString("SELECT ingredients.id,ingredients,Quantite,Lot,Gout FROM ingredients,produit WHERE produit.id = ").append("\""+idproduit+"\"").append(" AND ingredients.indexx = produit.id"));




     ModifierProduit::nomprod = idproduit;


            modeltheo->setFilter(QString("id = ").append("\""+idproduit+"\""));
            ui->tabtheo->setModel(modeltheo);
            ui->tabtheo2->setModel(modeltheo);
            ui->tabtheo3->setModel(modeltheo);
            ui->tabtheo4->setModel(modeltheo);
            ui->tabingredients->setModel(prod);
            modeltheo->select();
            for (int i=0;i<3;i++)
                ui->tabtheo->hideColumn(i);
            for (int i=4;i<7;i++)
                ui->tabtheo->hideColumn(i);
            for (int i=0;i<4;i++)
                ui->tabtheo2->hideColumn(i);
            for (int i=5;i<7;i++)
                ui->tabtheo2->hideColumn(i);
            for (int i=0;i<5;i++)
                ui->tabtheo3->hideColumn(i);

                ui->tabtheo3->hideColumn(6);
            for (int i=0;i<6;i++)
                ui->tabtheo4->hideColumn(i);



            modeltheo->setHeaderData(3, Qt::Horizontal, QObject::tr("EST Th"));
            modeltheo->setHeaderData(4,Qt::Horizontal,QObject::tr("GS Th"));
            modeltheo->setHeaderData(5,Qt::Horizontal,QObject::tr("PH Th"));
            modeltheo->setHeaderData(6,Qt::Horizontal,QObject::tr("T° Cible"));
            ui->tabingredients->resizeColumnsToContents();
            ui->tabingredients->hideColumn(0);




}


