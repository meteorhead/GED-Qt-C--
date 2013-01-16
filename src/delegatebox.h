#ifndef DELEGATEBOX_H
#define DELEGATEBOX_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QComboBox>
#include "Database.h"
#include <QSqlQuery>
#include <QStringList>
class DelegateBox : public QItemDelegate
{
    Q_OBJECT

public:
    DelegateBox (QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


#endif
