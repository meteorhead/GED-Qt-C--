#include "admin.h"
#include "ui_admin.h"
//#include <qwt_plot_curve.h>
#include <QDataWidgetMapper>

Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    miseEnForme();
    
    QObject::connect(ui->ajouter,SIGNAL(clicked()),this,SLOT(ajouterOp()));
    QObject::connect(ui->parametrerbutton,SIGNAL(clicked()),this,SLOT(refreshConsultation()));
    QObject::connect(param->ui->valider,SIGNAL(clicked()),this,SLOT(validerrefresh()));
    QObject::connect(param->ui->annuler,SIGNAL(clicked()),this,SLOT(fermer()));
    QObject::connect(ui->buttonparametrer,SIGNAL(clicked()),this,SLOT(refreshFiltres()));
    QObject::connect(ui->buttonparametrertemp,SIGNAL(clicked()),this,SLOT(refreshTemperature()));
    QObject::connect(ui->exportproduits,SIGNAL(clicked()),this,SLOT(exportproduit()));
    QObject::connect(ui->exporterfiltre,SIGNAL(clicked()),this,SLOT(exportFiltres()));
    //QObject::connect(ui->comboProgrammes,SIGNAL(activated(QString)),this,SLOT(refreshProgramme(QString)));
    QObject::connect(ui->comboProgrammes,SIGNAL(activated(QString)),this,SLOT(refreshProgramme(QString)));
    QObject::connect(this,SIGNAL(signalToReloadCombo()),this,SLOT(updateComboProgramme()));
    
}
 QString Admin::middle = " ";



Admin::~Admin()
{
    delete ui;


}


void Admin::miseEnForme()

{
    setFixedSize(800,480);
    deconnexion = new QPushButton("Deconnexion",this);
    //deconnexion->move(600,445);
    //deconnexion->setFixedHeight(25);
    //deconnexion->setFixedWidth(141);
    ui->VLDeconnexion->addWidget(deconnexion);
    ui->frameDeconnexion->setLayout(ui->VLDeconnexion);
    param = new parametrage(this);
    modelconsultation = new QSqlQueryModel;
    modelfiltres = new QSqlQueryModel;
    proxy = new QSqlQueryModel;
   // plotTemp = new QwtPlot(ui->frameCourbe);
   // plotTemp->setFixedSize(380,380);
   // courbeTemperature = new QwtPlotCurve;
   // courbeTemperature->attach(plotTemp);
   // plotTemp->setCanvasBackground(Qt::blue);
    ui->datedebutfiltres->setDisplayFormat("dd/MM/yyyy");
    ui->datefinfiltres->setDisplayFormat("dd/MM/yyyy");
    ui->datedebuttemperature->setDisplayFormat("dd/MM/yyyy");
    ui->datefintemperature->setDisplayFormat("dd/MM/yyyy");
    //plotTemp->show();
    int day = QDate::currentDate().day();
    if (day > 1)
    {
        day -= 1;
	QDate datedebutfiltress(QDate(QDate::currentDate().year(),QDate::currentDate().month(),day));
	ui->datedebutfiltres->setDate(datedebutfiltress);
	ui->datedebuttemperature->setDate(datedebutfiltress);
    }
    else
    {  
    ui->datedebutfiltres->setDate(QDate::currentDate());
    ui->datedebuttemperature->setDate(QDate::currentDate());
    }
    ui->datefinfiltres->setDate(QDate::currentDate());
    
    ui->datefintemperature->setDateTime(QDateTime::currentDateTime());
    programme = new QSqlTableModel();
    programme->setEditStrategy(QSqlTableModel::OnManualSubmit); 
    
    programme->setTable("MatricesEtapesProduits");
    programme->select();
    ui->tableProgramme->setModel(programme);
    ui->tableProgramme->hide();
    ui->tableProgramme->hideColumn(0);
    ui->tableProgramme->hideColumn(1);
    QSqlQuery comboBoxProg("SELECT DISTINCT Nom_Produit from produit where Nom_Produit != \"\" ORDER BY id DESC");
    while(comboBoxProg.next())
      ui->comboProgrammes->addItem(comboBoxProg.value(0).toString());
    
    
    
   
    QSqlQuery stephan("SELECT DISTINCT Stephan from filtres WHERE stephan IS NOT NULL ");
    while(stephan.next())
             ui->combostephanfiltres->addItem(stephan.value(0).toString());


}


void Admin::ajouterOp()
{

    d = new GenericDialog(this);
    d->setFixedWidth(400);
    d->setWindowTitle("Nouvel Operateur");
    d->exec();

}

void Admin::refreshConsultation()
{   int day = QDate::currentDate().day();
    
    if (day > 1)
    {
        day -= 1;
	QDateTime datetime(QDate(QDate::currentDate().year(),QDate::currentDate().month(),day),QTime::currentTime());
	param->ui->datedebut->setDateTime(datetime);
    }
   else
       param->ui->datedebut->setDateTime(QDateTime::currentDateTime());
    
    param->ui->datefin->setDateTime(QDateTime::currentDateTime());
    param->exec();
   
}


void Admin::validerrefresh()
{
    steph = param->ui->combostephan->currentText();
    produit = param->ui->comboproduit->currentText();
    datedebut = param->ui->datedebut->dateTime().toString("yyyy-MM-dd hh:mm:ss");
  
    datefin = param->ui->datefin->dateTime().toString("yyyy-MM-dd hh:mm:ss");

    QString str = "SELECT * FROM enregistrements WHERE stephan = ";
    str.append("\""+steph+"\"").append(" AND Nom_Produit = ").append("\""+produit+"\"").append(" AND Debut Between ").append("\""+datedebut+"\"").append(" AND ").append("\""+datefin+"\"");

    qDebug() << str;
    modelconsultation->setQuery(QString("SELECT * FROM enregistrements WHERE stephan = ").append("\""+steph+"\"").append(" AND Nom_Produit = ").append("\""+produit+"\"").append(" AND Debut Between ").append("\""+datedebut+"\"").append(" AND ").append("\""+datefin+"\""));
    QSqlQuery getId(QString("SELECT id FROM produit WHERE Nom_Produit = ").append("\""+produit+"\"").append(" ORDER BY id DESC LIMIT 1"));
            while (getId.next())
            index = getId.value(0).toString();



            for (int i=18;i<34;i++)
               {
        modelconsultation->setHeaderData(i,Qt::Horizontal," ");
               }

            proxy->setQuery(QString("SELECT ingredients FROM ingredients WHERE ingredients.indexx = ").append("\""+index+"\""));


            int j=19;
            for (int i=0;i<16;i++)
            {
                    QModelIndex index = proxy->index(i,0);
                    strtemp =proxy->data(index).toString();

                    modelconsultation->setHeaderData(j,Qt::Horizontal,strtemp);
                    j++;
            }





    ui->tabconsultation->setModel(modelconsultation);
    ui->tabconsultation->hideColumn(0);
    ui->tabconsultation->hideColumn(2);
    ui->tabconsultation->resizeColumnsToContents();


    fermer();


}

void Admin::fermer()
{


    param->close();
}

void Admin::refreshFiltres()
{   

    modelfiltres->setQuery(QString("SELECT * FROM filtres WHERE stephan = ").append("\""+ui->combostephanfiltres->currentText()+"\"").append(" AND Heure_Changement Between ").append("\""+ui->datedebutfiltres->dateTime().toString("yyyy-MM-dd hh:mm:ss")+"\"").append(" AND ").append("\""+ui->datefinfiltres->dateTime().toString("yyyy-MM-dd hh:mm:ss")+"\""));
    //QString test = "SELECT * FROM filtres WHERE stephan = ";
    //test.append("\""+ui->combostephanfiltres->currentText()+"\"").append(" AND Heure_Changement Between ").append("\""+datedebut+"\"").append(" AND ").append("\""+datefin+"\"");
    
    ui->tabfiltres->setModel(modelfiltres);
    ui->tabfiltres->hideColumn(0);
    ui->tabfiltres->hideColumn(7);
    ui->tabfiltres->resizeColumnsToContents();

}


void Admin::exportproduit()
{   QString dateexport = QDate::currentDate().toString();
    QFile file(QString("/home/ghaith/test.csv"));
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        int rowCount = modelconsultation->rowCount();
        int columnCount = modelconsultation->columnCount();
        QTextStream out(&file);
        out << ";";

        for (int j=0;j<columnCount;j++)
        {
        QString tr = modelconsultation->headerData(j,Qt::Horizontal).toString();
        out << tr;
        out << ";";
        }
        out << "\n";
        out << ";";
        for(int row =0; row < rowCount; row++)
        {
        for(int column = 0; column < columnCount; ++column) {
            QModelIndex index = modelconsultation->index(row,column);

            if(column == columnCount-1)
            out << "\n";

            out << modelconsultation->data(index).toString();
            out << ";";


        }


}


        file.close();
    }


void Admin::exportFiltres()
{
    QFile file(QString("c://filtres.csv"));
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        int rowCount = modelfiltres->rowCount();
        int columnCount = modelfiltres->columnCount();
        columnCount++;
        QTextStream out(&file);
        out << ";";

        for (int j=0;j<columnCount-1;j++)
        {
        QString tr = modelfiltres->headerData(j,Qt::Horizontal).toString();
        out << tr;
        out << ";";
        }
        out << "\n";
        out << ";";
        for(int row =0; row < rowCount; row++)
        {
        for(int column = 0; column < columnCount; ++column) {
            QModelIndex index = modelfiltres->index(row,column);

            if(column == columnCount-1)
            out << "\n";

            out << modelfiltres->data(index).toString();
            out << ";";


        }


}


        file.close();
    }




void Admin::insertProgrammeRows(int id)
{                        ui->tableProgramme->show();
                     
	                 rowCountProg = programme->rowCount();
			 for (int i=0;i<rowCountProg;i++)
			 {
			   ui->tableProgramme->hideRow(i);
			 }
		         programme->insertRows(rowCountProg,20);
			 int tempRow = programme->rowCount();
			 
			 
			 int k = 0;
			  
                          for (int i=rowCountProg;i<tempRow;i++)
			  {
			   programme->setData(programme->index(rowCountProg+k,2),k+1);
                           programme->setData(programme->index(rowCountProg+k,1),id);
			   k++;
                           } 
                        idRefreshTableProgramme = id;
                           //ui->tableProgramme->setModel(programme); 
			   //emit this->signalToReloadCombo();
}  


void Admin::validerProgramme()
{
  
 if(programme->submitAll())
 {      
        programme->setFilter(QString("indexproduit = %1").arg(indexProduit));
	
  
 }
 
   

}

void Admin::refreshProgramme(QString t)
{  
  
QSqlQuery getId(QString("SELECT id FROM produit WHERE Nom_Produit = ").append("\""+t+"\"").append(" ORDER BY id DESC LIMIT 1"));
            while (getId.next())
	    {
            indexProduit = getId.value(0).toString();
	    
	    }

QString indexMatriceProduit;
int j=0;
QSqlQuery getIdProduit(QString("SELECT id FROM MatricesEtapesProduits  WHERE indexproduit = ").append("\""+indexProduit+"\"").append(" ORDER BY id DESC LIMIT 1"));
            while (getIdProduit.next())
	    {
            indexMatriceProduit = getIdProduit.value(0).toString();
	    j++;
	    }
	    
	    
      if (j > 0)
      {
	programme->setFilter(QString("indexproduit = %1").arg(indexProduit));
        programme->select();
        ui->tableProgramme->show();
	
      }
      else
      {
	
      
	insertProgrammeRows(indexProduit.toInt());
	
      }
  
}

void Admin::updateComboProgramme()
{ ui->comboProgrammes->clear();
int i=0;
  QSqlQuery comboBoxProg("SELECT DISTINCT Nom_Produit from produit WHERE Nom_Produit != \"\" ORDER BY id DESC");
    while(comboBoxProg.next())
    {
      ui->comboProgrammes->addItem(comboBoxProg.value(0).toString());
      i++;
    }
    if (i==0)
      ui->tableProgramme->hide();
    else
      ui->tableProgramme->show();
    
}

void Admin::refreshTemperature()
{
  
QVector<double > xDate ;
QVector<double > yTemp;

int day = QDate::currentDate().day();
QString datedebutTemp;
    if (day > 1)
    {
        day -= 1;
	QDateTime datedebutfiltress(QDate(QDate::currentDate().year(),QDate::currentDate().month(),day),QTime::currentTime());
	datedebutTemp = datedebutfiltress.toString("yyyy-MM-dd hh:mm:ss");
	
    }
   else
     datedebutTemp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    
   QString datefinTemp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
   
     QString Temp = "SELECT id,datetime,RA_AV_tempProgSet FROM holdingregs WHERE datetime Between ";
    Temp.append("\""+ui->datedebuttemperature->dateTime().toString("yyyy-MM-dd hh:mm:ss")+"\"").append(" AND ").append("\""+ui->datefintemperature->dateTime().toString("yyyy-MM-dd hh:mm:ss")+"\"");
    QSqlQuery queryTemp(Temp);
  
    while(queryTemp.next())
    {
      //xDate.append(queryTemp.value(0).toDouble());
      xDate.append((double) queryTemp.value(0).toDouble());
      qDebug() << queryTemp.value(1).toDouble();
      //yTemp.append(queryTemp.value(2).toDouble());
      
    }
   // courbeTemperature->setSamples(xDate.data(),yTemp.data(),xDate.size());
      
    //courbeTemperature->setSamples();
     qDebug() << Temp;
     // plotTemp->replot();
     // plotTemp->show();

}
