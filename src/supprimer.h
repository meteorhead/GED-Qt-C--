#ifndef SUPPRIMER_H
#define SUPPRIMER_H

#include <QWidget>
#include "supprimerproduit.h"
#include "supprimeringredient.h"

namespace Ui {
    class supprimer;
}

class supprimer : public QWidget
{
    Q_OBJECT
private slots:

    void enterSupprimerIngredient();
public:
    Ui::supprimer *ui;
    explicit supprimer(QWidget *parent = 0);
    ~supprimer();

private:
    SupprimerProduit *suppro;
    supprimeringredient *suppring;

};

#endif // SUPPRIMER_H
