#include "delegatebox.h"
//#include "DelegateBox.h"
#include <QtGui>

DelegateBox::DelegateBox(QObject *parent):QItemDelegate(parent)
{


}


QWidget *DelegateBox::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/*index*/ ) const
{   
    QComboBox *editor = new QComboBox(parent);

    QSqlQuery requete("SELECT DISTINCT ingredients from ingredients where ingredients != \"\" ");

    while (requete.next())
    {

        editor->addItem(requete.value(0).toString());

    }

    return editor;

}


void DelegateBox::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    QComboBox *spinBox = static_cast<QComboBox*>(editor);
    if (!value.isNull())
    spinBox->addItem(value);
    }

void DelegateBox::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QComboBox *spinBox = static_cast<QComboBox*>(editor);
    QString value = spinBox->currentText();
    model->setData(index, value, Qt::EditRole);

}

void DelegateBox::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}



