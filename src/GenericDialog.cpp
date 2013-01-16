#include "GenericDialog.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "Database.h"
#include <QAbstractItemView>
#include <QTimer>
#include <QDateTimeEdit>
#include <QSqlQuery>


GenericDialog::GenericDialog(QWidget *parent):QDialog(parent)
{


    valid = new QPushButton("Valider");
    annuler = new QPushButton("Annuler");
    login = new QLineEdit;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    password1 = new QLineEdit;
    password1->setEchoMode(QLineEdit::Password);
    matricule = new QLineEdit;
    setform();
    grid = new QGridLayout;
    grid->addWidget(annuler,0,4,1,1,Qt::AlignRight);
    grid->addWidget(valid,0,4,1,1,Qt::AlignHCenter);
    layout = new QVBoxLayout();
    layout->addWidget(box);
    layout->addLayout(grid);
    setLayout(layout);
    resize(250,300);

    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annuler_op()));
    QObject::connect(valid,SIGNAL(clicked()),this,SLOT(soumettre_op()));



}


void GenericDialog::setform()
{

    box = new QGroupBox("Ajouter Opérateur");
    form = new QFormLayout;
    form->addRow("Login",login);
    form->addRow("Matricule",matricule);
    form->addRow("Mot de Passe",password);
    form->addRow("Confirmer Mot de Passe",password1);
    box->setLayout(form);
    box->setFixedSize(300,175);
}

void GenericDialog::soumettre_op()
{   QString log = login->text();
    QString pass = password->text();
    QString pass1 = password1->text();
    QString mat = matricule->text();

    if ((log.isEmpty()) || (pass.isEmpty()) || (pass1.isEmpty()) || (mat.isEmpty()))
    {
        QMessageBox::critical(this,"Erreur!","Veuillez rentrer les informations manquantes",QMessageBox::Ok);
        return;
    }
    else

        if(password->text() != password1->text())
        {
            QMessageBox::critical(this,"Erreur!","les Mots de passe entrés ne correspondent pas!",QMessageBox::Ok);
            return   ;
        }
        else
        {
             QString id;
             QString matriculeop;
             QString matt;
             QSqlQuery recherchemat(QString("SELECT matricule_RH from operateurs where matricule_RH = ").append("\""+mat+"\""));
             while(recherchemat.next())
             matriculeop = recherchemat.value(0).toString();

                 if (matricule->text()==matriculeop)
                 QMessageBox::warning(this,"Avertissement","Un operateur ayant la même matricule existe déjà",QMessageBox::Ok);


             QSqlQuery rechercheop(QString("SELECT id,matricule_RH from operateurs where login =  ").append("\""+log+"\"").append(" AND matricule_RH = ").append("\""+mat+"\""));
             while(rechercheop.next())
                {
                 id = rechercheop.value(0).toString();
               matt = recherchemat.value(1).toString();
             }
                     if (id.isNull() && matriculeop.isNull())

             {
                 QSqlQuery query;
                      query.prepare("INSERT INTO operateurs (login, password,matricule_RH) "
                                    "VALUES (:login, :password, :matricule)");
                      query.bindValue(":login", login->text());
                      query.bindValue(":password", password->text());
                      query.bindValue(":matricule", matricule->text());
                    bool ok =   query.exec();
                    if (ok)
                    {

                        QMessageBox::information(this,"Notice",QString("l'opérateur ").append("\""+login->text()+"\"").append(" a été ajouté avec succès"));
                        close();
                    }

                    else
                        QMessageBox::critical(this,"Erreur","Echec de l'ajout, veuillez vérifier votre connexion à la base de données",QMessageBox::Ok);


             }
                 }
          }









void GenericDialog::annuler_op()
{
    int choix = QMessageBox::question(this,"Notice","Voulez vous vraiment annuler?",QMessageBox::Yes,QMessageBox::No);
            if (choix == QMessageBox::Yes)

            close();

            else
                return;

}
