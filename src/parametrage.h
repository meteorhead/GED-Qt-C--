#ifndef PARAMETRAGE_H
#define PARAMETRAGE_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
    class parametrage;
}

class parametrage : public QDialog
{
    Q_OBJECT

public:
    explicit parametrage(QWidget *parent = 0);
    ~parametrage();
    Ui::parametrage *ui;


private:


};

#endif // PARAMETRAGE_H
