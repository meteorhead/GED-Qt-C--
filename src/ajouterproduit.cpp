#include "ajouterproduit.h"
#include "ui_ajouterproduit.h"

AjouterProduit::AjouterProduit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AjouterProduit)
{
    ui->setupUi(this);
    QString mod;
    //completeop->setModel(model);
    QSqlQuery last("select Distinct Nom_Produit from produit WHERE Nom_Produit != \"\" ORDER BY id DESC");
    QStringList produits;
    while(last.next())
    {
        mod = last.value(0).toString();
        produits << mod;
    }

    model = new QSqlTableModel;
    model->setTable("ingredients");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    QSqlQuery checkProduit("SELECT DISTINCT Nom_Produit FROM produit WHERE Nom_Produit != \"\" ORDER BY id DESC");
    while (checkProduit.next())
       ui->comboPr->addItem(checkProduit.value(0).toString());
  /* envoi d'un signal à l'ajout d'une nouvelle recette pour faire l'update de l'index matriceproduits*/


    row = model->rowCount();
    completeop = new QCompleter(produits);
    completeop->setCompletionMode(QCompleter::PopupCompletion);
    completeop->setCaseSensitivity(Qt::CaseInsensitive);
    ui->comboPr->setCompleter(completeop);

    QObject::connect(ui->comboPr,SIGNAL(activated(QString)),this,SLOT(refreshrecette(const QString &)));
}

AjouterProduit::~AjouterProduit()
{
    delete ui;
}

void AjouterProduit::refreshRows()
{

    row = model->rowCount();
    for (int i=0;i<row;i++)
        ui->tabproduit->hideRow(i);



}
void AjouterProduit::clear()
{
    ui->linerecette->clear();
    ui->lineEST->clear();
    ui->lineGS->clear();
    ui->linePH->clear();
    ui->lineT->clear();
    ui->tabproduit->setVisible(false);
}


void AjouterProduit::refreshrecette(const QString &str)

{
    QString label;
    QSqlQuery refreshrecette(QString("SELECT DISTINCT Id_Recette from produit WHERE Nom_Produit = ").append("\""+str+"\"").append(" AND Id_Recette != \"\" ORDER BY id DESC LIMIT 1"));
    while(refreshrecette.next())
    {
     label = refreshrecette.value(0).toString();

    }

    ui->laberecette->setText(label);
}
