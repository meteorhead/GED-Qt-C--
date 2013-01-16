#ifndef MODIFIERPRODUIT_H
#define MODIFIERPRODUIT_H
#include "ModelProduit.h"
#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>


namespace Ui {
    class ModifierProduit;
}

class ModifierProduit : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierProduit(QWidget *parent = 0);
    QSqlTableModel *modeltheo;
    ModelProduit *prod;
    static QString nomprod;
    Ui::ModifierProduit *ui;
    ~ModifierProduit();
private slots:

    void refreshproduit(QString);
    void refreshRecettes(QString);

private:

    QString idproduit;


};

#endif // MODIFIERPRODUIT_H
