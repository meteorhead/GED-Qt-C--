#ifndef ADMIN_H
#define ADMIN_H


#include "ModelProduit.h"
#include <QWidget>
#include <QDialog>
#include "Database.h"
#include "GenericDialog.h"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QtCore/QFile>
#include "parametrage.h"
#include "ui_parametrage.h"
#include <QComboBox>
#include <QDate>
//#include <qwt_plot.h>
//#include <qwt_plot_curve.h>


namespace Ui {
    class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT
signals:
  void signalToReloadCombo();
public:
    explicit Admin(QWidget *parent = 0);
    ~Admin();
    Ui::Admin *ui;
    GenericDialog *d;
    QSqlTableModel *model;
    QSqlQueryModel *modelconsultation;
    QSqlQueryModel *modelfiltres;
    QSqlQueryModel *proxy;
    QSqlTableModel *programme;
    parametrage *param;
    QString steph;
    QString produit;
    QString datedebut;
    QString datefin;
    QString index;
    QString strtemp;
    static QString middle;
    QPushButton *deconnexion;

public slots:
  
 void updateComboProgramme();

private slots:

   void ajouterOp();
   void miseEnForme();
   void refreshConsultation();
   void validerrefresh();
   void fermer();
   void refreshFiltres();
   void refreshTemperature();
   void exportproduit();
   void exportFiltres();
   void insertProgrammeRows(int id);
   void validerProgramme();
   void refreshProgramme(QString t);
  
  





private:

 int rowCountProg;
 int idRefreshTableProgramme;
 QString indexProduit;
 //QwtPlot *plotTemp;
 //QwtPlotCurve *courbeTemperature;

};

#endif // ADMIN_H
