#ifndef SUPPRIMERPRODUIT_H
#define SUPPRIMERPRODUIT_H

#include <QDialog>
#include "Database.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
    class SupprimerProduit;
}

class SupprimerProduit : public QDialog
{
    Q_OBJECT

signals:
  void signalToUpdateCombo();
public:
    explicit SupprimerProduit(QWidget *parent = 0);
    ~SupprimerProduit();
    Ui::SupprimerProduit *ui;
public slots:
    void valider_supprimer();
    void refreshrecettes();
    void refreshProduits();
   

private:
    
    QSqlQueryModel *table;
};

#endif // SUPPRIMERPRODUIT_H
