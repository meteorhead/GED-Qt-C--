#include "GroundZero.h"

GroundZero::GroundZero(QWidget *parent):QStackedWidget(parent)
{

    Database *cloud = new Database();
    cloud->openConnection();
    two = new ModifierOp(this);
    one = new Admin(this);
    three = new SupprimerOp(this);
    modifierPr = new ModifierProduit(this);
    ajouterPr = new AjouterProduit(this);
    login = new Login(this);
    sup = new supprimer(this);
    menuajouter = new MenuAjouter();
    delegate = new DelegateBox;
    menuAjouterProduit = new MenuAjouterProduit(this);
    supprimerProduit = new SupprimerProduit(this);
    
    
    addWidget(login);
    addWidget(one);
    addWidget(two);
    addWidget(three);
    addWidget(modifierPr);
    addWidget(ajouterPr);
    addWidget(sup);
    addWidget(menuajouter);
    

    setCurrentWidget(one);
    QObject::connect(one->ui->modifier,SIGNAL(clicked()),this,SLOT(enterModif()));
    QObject::connect(one->ui->ajouterProd,SIGNAL(clicked()),this,SLOT(enterMenuAjouter()));
    QObject::connect(two->retour,SIGNAL(clicked()),this,SLOT(backToAdmin()));
    QObject::connect(one->ui->supprimer,SIGNAL(clicked()),this,SLOT(enterSupprimer()));
    QObject::connect(three->back,SIGNAL(clicked()),this,SLOT(backToAdmin()));
    QObject::connect(two->login,SIGNAL(textChanged(QString)),this,SLOT(resetCompleter()));
    QObject::connect(three->login,SIGNAL(returnPressed()),this,SLOT(populationOverrideSupprimer()));
    //QObject::connect(ajouterPr->ui->comboPr,SIGNAL(activated(int)),this,SLOT(PopulationOverrideProduit()));
    QObject::connect(three->login,SIGNAL(textChanged(QString)),this,SLOT(resetCompleterSupprimer()));
    QObject::connect(two->login,SIGNAL(returnPressed()),this,SLOT(populationOverride()));
    QObject::connect(two->valider,SIGNAL(clicked()),this,SLOT(validermodif()));
    QObject::connect(three->supprimer,SIGNAL(clicked()),this,SLOT(SupprimerOperateur()));
    QObject::connect(one->ui->modifierprod,SIGNAL(clicked()),this,SLOT(enterModifProd()));
    QObject::connect(ajouterPr->ui->retour,SIGNAL(clicked()),this,SLOT(backToAdmin()));
    QObject::connect(modifierPr->ui->retour,SIGNAL(clicked()),this,SLOT(backToAdmin()));
    QObject::connect(ajouterPr->ui->ajouter,SIGNAL(clicked()),this,SLOT(ajouterRecetteProduit()));
    QObject::connect(one->ui->ajouterProd,SIGNAL(clicked()),this,SLOT(clearAjout()));
    QObject::connect(one->ui->ajouterProd,SIGNAL(clicked()),this,SLOT(refreshRowAjout()));
    QObject::connect(ajouterPr->ui->valideraj,SIGNAL(clicked()),this,SLOT(validerAjouterProduit()));
    QObject::connect(login->ui->connexion,SIGNAL(clicked()),this,SLOT(liftOff()));
    QObject::connect(login,SIGNAL(triggerUnderground()),this,SLOT(liftOff()));
    QObject::connect(one->deconnexion,SIGNAL(clicked()),this,SLOT(flipOut()));
    QObject::connect(one->ui->bouton_supprimer,SIGNAL(clicked()),this,SLOT(enterMenuSupprimer()));
    QObject::connect(sup->ui->retour,SIGNAL(clicked()),this,SLOT(backToAdmin()));
    QObject::connect(menuajouter->ui->retour,SIGNAL(clicked()),this,SLOT(backToAdmin()));
    QObject::connect(menuajouter->ui->ajouterRecette,SIGNAL(clicked()),this,SLOT(fromMenuAjouterToAjouterrecette()));
    connect(menuajouter->ui->ajouterProduit,SIGNAL(clicked()),this,SLOT(execMenuAjouterProduit()));
    connect(sup->ui->pushButton,SIGNAL(clicked()),this,SLOT(execMenuSupprimerProduit()));
    //connect(this,SIGNAL(startadminInsertRows(int)),one,SLOT(insertProgrammeRows(int)));
    connect(one->ui->validerProgramme,SIGNAL(clicked()),one,SLOT(validerProgramme()));
    connect(this,SIGNAL(signalToUpdateCombo()),one,SLOT(updateComboProgramme()));
    connect(supprimerProduit,SIGNAL(signalToUpdateCombo()),this,SLOT(updateCombos()));
    connect(menuAjouterProduit,SIGNAL(signalToUpdateCombo()),this,SLOT(updateCombos()));
    connect(menuAjouterProduit,SIGNAL(signalToUpdateCombo()),supprimerProduit,SLOT(refreshProduits()));
   
    
	 
	





}

void GroundZero::enterModif()
{
    removeWidget(one);
    setCurrentWidget(two);


}

void GroundZero::enterSupprimer()
{

    removeWidget(one);
    setCurrentWidget(three);


}


void GroundZero::enterModifProd()
{
    removeWidget(one);
    setCurrentWidget(modifierPr);


}



void GroundZero::backToAdmin()
{

    addWidget(one);
    setCurrentWidget(one);

}


void GroundZero::resetCompleter()
{


    QString mod;
    QSqlQuery last("select login from operateurs");
    QStringList logins;
    while(last.next())
    {
        mod = last.value(0).toString();
        logins << mod;
    }
    two->completeop = new QCompleter(logins);
    two->completeop->setCompletionMode(QCompleter::PopupCompletion);
    two->completeop->setCaseSensitivity(Qt::CaseInsensitive);
    two->login->setCompleter(two->completeop);



}


void GroundZero::populationOverride()
{
    QString login = two->login->text();
    QString matricule;
    QSqlQuery populate(QString("SELECT login,matricule_RH,id from operateurs where login = ").append("\""+login+"\""));
    while(populate.next())
    {
        login = populate.value(0).toString();
        matricule = populate.value(1).toString();
        two->matricule->setText(matricule);
        id_modif = populate.value(2).toString();

     }

}

void GroundZero::validermodif()
{
QString login;
QString pass;
QString matricule;

if (two->login->text().isEmpty() || two->matricule->text().isEmpty())
 {

    QMessageBox::critical(this,"Erreur","Vous devez remplir les champs login et matricule_RH",QMessageBox::Ok);
    return;
}
else
{   QString mat = two->matricule->text();
    QString matriculeop;
    int i=0;
    QSqlQuery recherchemat(QString("SELECT matricule_RH from operateurs where matricule_RH = ").append("\""+mat+"\""));
    while(recherchemat.next())
    {
    matriculeop = recherchemat.value(0).toString();
    i++;
    }

        if (i > 1)
        {
        QMessageBox::warning(this,"Avertissement","Un operateur ayant la même matricule existe déjà",QMessageBox::Ok);
        }
        else
        {
            if(!two->password->text().isEmpty())
            {
             QSqlQuery query(QString("UPDATE operateurs SET login = ").append("\""+two->login->text()+"\"").append(", password = ").append("\""+two->password->text()+"\"").append(", matricule_RH = ").append("\""+two->matricule->text()+"\"").append(" WHERE id = ").append("\""+id_modif+"\""));


               if (query.exec())
               {

                   QMessageBox::information(this,"Notice",QString("l'opérateur ").append("\""+two->login->text()+"\"").append(" a été modifié avec succès"));
                   two->login->clear();
                   two->matricule->clear();
                   two->password->clear();
               }

               else
                   QMessageBox::critical(this,"Erreur","Echec de l'ajout, veuillez vérifier votre connexion à la base de données",QMessageBox::Ok);

             }

               else
               {
                       QSqlQuery requete(QString("UPDATE operateurs SET login = ").append("\""+two->login->text()+"\"").append(", matricule_RH = ").append("\""+two->matricule->text()+"\"").append(" WHERE id = ").append("\""+id_modif+"\""));
                      bool ok=   requete.exec();
                      if (ok)
                      {

                          QMessageBox::information(this,"Notice",QString("l'opérateur ").append("\""+two->login->text()+"\"").append(" a été modifié avec succès"));
                          two->login->clear();
                          two->password->clear();
                          two->matricule->clear();
                      }

                      else
                          QMessageBox::critical(this,"Erreur","Echec de l'ajout, veuillez vérifier votre connexion à la base de données",QMessageBox::Ok);



               }



        }



}






}

void GroundZero::populationOverrideSupprimer()
{
    QString login = three->login->text();
    QString matricule;
    QSqlQuery populate(QString("SELECT login,matricule_RH,id from operateurs where login = ").append("\""+login+"\""));
    while(populate.next())
    {
        login = populate.value(0).toString();
        matricule = populate.value(1).toString();
        three->matricule->setText(matricule);
        id_modif = populate.value(2).toString();

     }

}


void GroundZero::resetCompleterSupprimer()
{

    QString mod;
    QSqlQuery last("select login from operateurs where login !=  """);
    QStringList logins;
    while(last.next())
    {
        mod = last.value(0).toString();
        logins << mod;
    }
    three->completeop = new QCompleter(logins);
    three->completeop->setCompletionMode(QCompleter::PopupCompletion);
    three->completeop->setCaseSensitivity(Qt::CaseInsensitive);
    three->login->setCompleter(three->completeop);



}

void GroundZero::resetCompleterAjouterProduit()
{



    QString mod;
    //completeop->setModel(model);
    QSqlQuery last("select Distinct Nom_Produit from produit order by id DESC");
    QStringList produits;
    while(last.next())
    {
        mod = last.value(0).toString();
        produits << mod;
    }
        //
    ajouterPr->completeop = new QCompleter(produits);
    ajouterPr->completeop->setCompletionMode(QCompleter::PopupCompletion);
    ajouterPr->completeop->setCaseSensitivity(Qt::CaseInsensitive);
    ajouterPr->ui->comboPr->setCompleter(ajouterPr->completeop);
}





void GroundZero::SupprimerOperateur()
{

    if (three->login->text().isEmpty() || three->matricule->text().isEmpty())
     {

        QMessageBox::critical(this,"Erreur","Vous devez remplir les champs login et matricule",QMessageBox::Ok);
        return;
    }

    else
    {
        QSqlQuery query(QString("DELETE from operateurs WHERE login = ").append("\""+three->login->text()+"\"").append(" AND matricule_RH = ").append("\""+three->matricule->text()+"\""));

                bool ok=   query.exec();
                if (ok)
                {
                    int choix = QMessageBox::question(this,"Notice",QString("Voulez vous vraiment supprimer").append("\""+three->login->text()+"\"").append(" ?"),QMessageBox::Yes,QMessageBox::No);
                    if(choix == QMessageBox::Yes)
                    {
		      QSqlQuery lastt;
		      lastt.exec("select Distinct Nom_Produit from produit order by id DESC");
                    QMessageBox::information(this,"Notice",QString("l'opérateur ").append("\""+three->login->text()+"\"").append(" a été supprimé avec succès"));
                    three->login->clear();

                    three->matricule->clear();
                    }
                    if(choix == QMessageBox::No)
                        return;

                }

                else
                    QMessageBox::critical(this,"Erreur","Echec de l'ajout, veuillez vérifier votre connexion à la base de données",QMessageBox::Ok);



         }

}


/*
void GroundZero::PopulationOverrideProduit()
{

   ajouterPr->ui->comboPr->clear();

    QSqlQuery checkProduit("SELECT DISTINCT Nom_Produit FROM produit WHERE Nom_Produit IS NOT NULL");
    while (checkProduit.next())
    {   ajouterPr->ui->comboPr->addItem(checkProduit.value(0).toString());


    }

    }
*/

void GroundZero::ajouterRecetteProduit()
{
    QString prod = ajouterPr->ui->comboPr->currentText();
    QString recette = ajouterPr->ui->linerecette->text();
    QString EST = ajouterPr->ui->lineEST->text();
    QString GS = ajouterPr->ui->lineGS->text();
    QString PH = ajouterPr->ui->linePH->text();
    QString T = ajouterPr->ui->lineT->text();
    

    if ((prod.isEmpty()) || (recette.isEmpty()))
    {
        QMessageBox::critical(this,"Erreur!","Veuillez remplir les données relatives au produit et recette",QMessageBox::Ok);
        return;
    }
   else
    {
       /* QSqlQuery checkduplicate(QString("SELECT Id_Recette FROM Produit WHERE Id_Recette = ").append(""+recette+"").append(" AND Nom_Produit"));
               while(checkduplicate.next())
                   {
                      count++;
                   }
        if (count > 0)
        {
            QMessageBox::critical(this,"Erreur","Code Recette dupliqué pour ce produit", QMessageBox::Ok);
            return;
         }
        else
       {    */

            QSqlQuery query;
            query.prepare("INSERT INTO produit (Nom_Produit, Id_Recette,EST_TH,GS_TH,PH_TH,T_CIBLE) "
                           "VALUES (:produit, :recette, :EST, :GS, :PH, :T)");
             query.bindValue(":produit", prod);
             query.bindValue(":recette", recette);
             query.bindValue(":EST",EST);
             query.bindValue(":GS",GS);
             query.bindValue(":PH",PH);
             query.bindValue(":T",T);
             QSqlQuery recet;
             recet.prepare("INSERT INTO produit (Nom_Produit,Id_Recette)"
                                       "VALUES (:nompr,:recet)");
             recet.bindValue(":nompr",prod);
             recet.bindValue(":recet",recette);
             strid = ajouterPr->ui->comboPr->currentText();
             QSqlQuery extractAncienIndex(QString("SELECT id from produit WHERE Nom_Produit=").append("\""+strid+"\""));
             while (extractAncienIndex.next())
                ancienIndex = extractAncienIndex.value(0).toString();
            
            bool insert = recet.exec();


           bool ok = query.exec();
           if (ok && insert)

           {


               refreshRowAjout();
               ajouterPr->ui->tabproduit->setVisible(true);

             int idIngredient;
               QSqlQuery retId("SELECT id FROM produit ORDER BY id DESC LIMIT 1");
               while (retId.next())
                   id = retId.value(0).toInt();
               QSqlQuery retIdIng("SELECT id FROM ingredients Order By id DESC LIMIT 1");
               while (retIdIng.next())
                   idIngredient = retIdIng.value(0).toInt();

               one->programme->rowCount();
               ajouterPr->model->insertRows(ajouterPr->row,16);
	     
	      
            for(int i=0;i<16;i++)
                           {int j=ajouterPr->row;
                             j = j+i;
                           ajouterPr->model->setData(ajouterPr->model->index(j,1),id);
                           }



               ajouterPr->ui->tabproduit->setModel(ajouterPr->model);
               ajouterPr->ui->tabproduit->setItemDelegateForColumn(2,delegate);

                //int rowhide = ajouterPr->row;

                for(int i=0;i<ajouterPr->row;i++)
                {
                    ajouterPr->ui->tabproduit->hideRow(i);
                }

              ajouterPr->ui->tabproduit->hideColumn(0);
              ajouterPr->ui->tabproduit->hideColumn(1);


           }


           if(!ok)
            {   QMessageBox::critical(this,"Erreur","Echec de l'ajout",QMessageBox::Ok);
                return;
            }
          }

    }






void GroundZero::validerAjouterProduit()
{
    
    int choix = QMessageBox::question(this,"Confirmation","Voulez vous valider les informations saisies ?",QMessageBox::Yes,QMessageBox::No);

    if (choix == QMessageBox::Yes)
    {


        bool ok = ajouterPr->model->submitAll();

        if (ok)
           {

            clearAjout();
           QString newId;
            QMessageBox::information(this,"Notice","Ajout effectué avec succès",QMessageBox::Ok);
       QSqlQuery extractNewIndex(QString("SELECT id from produit WHERE Nom_Produit=").append("\""+strid+"\"").append(" AND ID_Recette != \"\" ORDER by id DESC LIMIT 1"));
         while (extractNewIndex.next())
             newId = extractNewIndex.value(0).toString();
      
         QSqlQuery query;
          query.exec(QString("UPDATE MatricesEtapesProduits SET indexproduit=").append("\""+newId+"\"").append(" WHERE indexproduit=").append("\""+ancienIndex+"\""));
             

           }
        else { QMessageBox::critical(this,"Erreur","Echec de l'ajout",QMessageBox::Ok);
       
        }

      }


    if (choix == QMessageBox::No)

        return;
}


void GroundZero::clearAjout()
{




    ajouterPr->ui->linerecette->clear();
    ajouterPr->ui->lineEST->clear();
    ajouterPr->ui->lineGS->clear();
    ajouterPr->ui->linePH->clear();
    ajouterPr->ui->lineT->clear();
    ajouterPr->ui->tabproduit->setVisible(false);

}

void GroundZero::refreshRowAjout()
{

    ajouterPr->row = ajouterPr->model->rowCount();
    for (int i=0;i<ajouterPr->row;i++)
        ajouterPr->ui->tabproduit->hideRow(i);


}


void GroundZero::liftOff()
{
    resultat = false;

    resultat = login->check();
    

    if (resultat)
    {


        removeWidget(login);
        Admin::middle = login->ui->log->text();
        setCurrentWidget(one);

}
    else
    {
    QMessageBox::critical(this,"Erreur Login","Veuillez vérifiez votre Login et Mot de Passe",QMessageBox::Ok);
    }

}

void GroundZero::flipOut()
{

   int choice =  QMessageBox::question(this,"Notice!","Voulez-vous vraiment vous déconnecter?",QMessageBox::Yes,QMessageBox::No);

   if (choice==QMessageBox::Yes)
   {

           addWidget(login);
           login->eraserHead();
           setCurrentWidget(login);




    }

if (choice==QMessageBox::No)

       return;


}

void GroundZero::enterMenuSupprimer()
{

    //addWidget(su);
    setCurrentWidget(sup);

}


void GroundZero::enterMenuAjouter()
{
    removeWidget(one);
    addWidget(menuajouter);
    setCurrentWidget(menuajouter);

}

void GroundZero::fromMenuAjouterToAjouterrecette()
{
    removeWidget(menuajouter);
    setCurrentWidget(ajouterPr);



}

void GroundZero::returnFromAjouterRecetteToMenuAjouter()
{  addWidget(menuajouter);
    removeWidget(ajouterPr);
   setCurrentWidget(menuajouter);


}

void GroundZero::execMenuAjouterProduit()
{
menuAjouterProduit->exec();
if (menuAjouterProduit->resultatAjout)
  { int id;
         QSqlQuery squery(QString("SELECT id from produit where Nom_Produit=").append("\""+menuAjouterProduit->nomProduit+"\"").append("Order By id DESC LIMIT 1"));
	 while (squery.next())
	   id = squery.value(0).toInt();
	 emit signalToUpdateCombo();
     ajouterPr->ui->comboPr->clear();
     QSqlQuery checkProduit("SELECT DISTINCT Nom_Produit FROM produit WHERE Nom_Produit != \"\" ORDER BY id DESC");
     while (checkProduit.next())
        ajouterPr->ui->comboPr->addItem(checkProduit.value(0).toString());
	 }
	
}

void GroundZero::execMenuSupprimerProduit()
{
  supprimerProduit->exec();


}

void GroundZero::updateCombos()
{    ajouterPr->ui->comboPr->clear();
     one->ui->comboProgrammes->clear();
     modifierPr->ui->comboproduit->clear();
     QSqlQuery checkProduit("SELECT DISTINCT Nom_Produit FROM produit WHERE Nom_Produit != \"\" ORDER BY id DESC");
     while (checkProduit.next())
     { 
        ajouterPr->ui->comboPr->addItem(checkProduit.value(0).toString());
	one->ui->comboProgrammes->addItem(checkProduit.value(0).toString());
	modifierPr->ui->comboproduit->addItem(checkProduit.value(0).toString());
     }
  
}