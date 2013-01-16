#include <QtSql>

#include "ModelProduit.h"
#include "modifierproduit.h"

 ModelProduit::ModelProduit(QObject *parent)
     : QSqlQueryModel(parent)
 {

 }

 Qt::ItemFlags ModelProduit::flags(
         const QModelIndex &index) const
 {
     Qt::ItemFlags flags = QSqlQueryModel::flags(index);
     if (index.column()==1 || index.column()==2 || index.column()==3)
         flags |= Qt::ItemIsEditable;
     return flags;
 }

 bool ModelProduit::setData(const QModelIndex &index, const QVariant &value, int /* role */)
  {
      if (index.column() < 1 || index.column() > 3)
          return false;


      QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
      int id = data(primaryKeyIndex).toInt();

      clear();

      bool ok;
      if (index.column()==1) {
          ok = setIngredient(id, value.toString());
      }
      //if (index.column() == 1) {
      //    ok = setIngredient(id, value.toString());
      //}

      if (index.column() == 2) {
          ok = setQuantite(id, value.toString());
      }

      if(index.column()==3)
          ok = setLot(id,value.toString());
      refresh();
      return ok;
  }



  bool ModelProduit::setQuantite(int id, const QString &Quantite)
  {
      QSqlQuery query;
      query.prepare("update ingredients set Quantite = ? where id = ?");
      query.addBindValue(Quantite);
      query.addBindValue(id);
      return query.exec();
  }


  bool ModelProduit::setLot(int id, const QString &Lot)
  {
      QSqlQuery query;
      query.prepare("update ingredients set Lot = ? where id = ?");
      query.addBindValue(Lot);
      query.addBindValue(id);
      return query.exec();
  }

  bool ModelProduit::setIngredient(int id, const QString &Ingredient)
  {
      QSqlQuery query;
      query.prepare("update ingredients set ingredients = ? where id = ?");
      query.addBindValue(Ingredient);
      query.addBindValue(id);
      return query.exec();
  }
void ModelProduit::refresh()
{

setQuery(QString("SELECT ingredients.id,ingredients,Quantite,Lot,Gout FROM ingredients,produit WHERE ingredients.ingredients != \"\" AND produit.id = ").append("\""+ModifierProduit::nomprod+"\"").append(" AND ingredients.indexx = produit.id"));


}
