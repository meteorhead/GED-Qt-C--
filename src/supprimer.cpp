#include "supprimer.h"
#include "ui_supprimer.h"

supprimer::supprimer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::supprimer)
{
    ui->setupUi(this);
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(enterSupprimerIngredient()));
}

supprimer::~supprimer()
{
    delete ui;
}



void supprimer::enterSupprimerIngredient()
{
    suppring = new supprimeringredient(this);
    suppring->exec();

}
