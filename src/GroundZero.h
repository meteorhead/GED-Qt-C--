#ifndef GROUNDZERO_H
#define GROUNDZERO_H
#include <QStackedWidget>
#include "ModifierOp.h"
#include <QSqlQuery>
#include "admin.h"
#include "ui_admin.h"
#include "SupprimerOp.h"
#include "modifierproduit.h"
#include "ui_modifierproduit.h"
#include "login.h"
#include "ui_login.h"
#include "supprimer.h"
#include "ui_supprimer.h"
#include "menuajouter.h"
#include "menuajouterproduit.h"
#include "ajouterproduit.h"
#include "ui_ajouterproduit.h"
#include "ui_menuajouter.h"
#include "delegatebox.h"
#include <QComboBox>


class GroundZero : public QStackedWidget
{
 Q_OBJECT

public:

    explicit GroundZero(QWidget *parent=0);
    
     Login *login;
signals:
  void startadminInsertRows(int id);
  void signalToUpdateCombo();
private slots:
    void enterModif();
    void enterModifProd();
    void resetCompleter();
    void populationOverride();
    void validermodif();
    void enterSupprimer();
    void backToAdmin();
    void SupprimerOperateur();
    void populationOverrideSupprimer();
    void resetCompleterSupprimer();
    void resetCompleterAjouterProduit();
    //void PopulationOverrideProduit();
    void ajouterRecetteProduit();
    void validerAjouterProduit();
    void clearAjout();
    void refreshRowAjout();
    void liftOff();
    void flipOut();
    void enterMenuSupprimer();
    void enterMenuAjouter();
    void fromMenuAjouterToAjouterrecette();
    void returnFromAjouterRecetteToMenuAjouter();
    void execMenuAjouterProduit();
    void execMenuSupprimerProduit();
    void updateCombos();








private:

    Admin *one;
    ModifierOp *two;
    MenuAjouterProduit *menuAjouterProduit;
    QString id_modif;
    SupprimerOp *three;
    ModifierProduit *modifierPr;
    SupprimerProduit *supprimerProduit;
    AjouterProduit *ajouterPr;
    MenuAjouter *menuajouter;
    supprimer *sup;
    bool resultat;
    QString middle;
    DelegateBox *delegate;
    int id;
    QString ancienIndex;
    QString strid;








};




#endif // GROUNDZERO_H
