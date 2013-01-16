#ifndef SUPPRIMERINGREDIENT_H
#define SUPPRIMERINGREDIENT_H

#include <QDialog>
#include <QSqlQuery>
#include "Database.h"
#include <QCheckBox>
#include <QSqlQueryModel>

namespace Ui {
    class supprimeringredient;
}

class supprimeringredient : public QDialog
{
    Q_OBJECT

public:
    explicit supprimeringredient(QWidget *parent = 0);
    ~supprimeringredient();
public slots:
    void valider_supprimer();

private:
    Ui::supprimeringredient *ui;
    QSqlQueryModel *table;

};

#endif // SUPPRIMERINGREDIENT_H
