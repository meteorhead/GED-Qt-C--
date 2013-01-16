#ifndef MENUAJOUTERPRODUIT_H
#define MENUAJOUTERPRODUIT_H

#include <QDialog>
#include "Database.h"
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
    class MenuAjouterProduit;
}

class MenuAjouterProduit : public QDialog
{
    Q_OBJECT

public:
    explicit MenuAjouterProduit(QWidget *parent = 0);
    ~MenuAjouterProduit();
    bool resultatAjout;
    QString nomProduit;
signals:
void signalToUpdateCombo();
public slots:
    void valider_ajouter();
    
    


private:
    Ui::MenuAjouterProduit *ui;
    QSqlQueryModel *table;
    int idProgramme;
};

#endif // MENUAJOUTERPRODUIT_H
