#ifndef MODELPRODUIT_H
#define MODELPRODUIT_H

#include <QSqlQueryModel>



class Admin;



class ModelProduit : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit ModelProduit(QObject *parent=0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:

    bool setIngredient(int id, const QString &Ingredient);
    bool setQuantite(int id, const QString &Quantite);
    bool setLot(int id, const QString &lot);
    void refresh();
};

#endif // MODELPRODUIT_H
