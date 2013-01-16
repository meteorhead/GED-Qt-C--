#ifndef AJOUTERPRODUIT_H
#define AJOUTERPRODUIT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QComboBox>
#include <QCompleter>
#include "Database.h"
#include "delegatebox.h"

namespace Ui {
    class AjouterProduit;
}

class AjouterProduit : public QWidget
{
    Q_OBJECT

public:
    explicit AjouterProduit(QWidget *parent = 0);
    ~AjouterProduit();
    QCompleter *completeop;
    Ui::AjouterProduit *ui;
    QSqlTableModel *model;

    int row;
    void refreshRows();
    void clear();
private slots:
    void refreshrecette(const QString &);

private:


};

#endif // AJOUTERPRODUIT_H
