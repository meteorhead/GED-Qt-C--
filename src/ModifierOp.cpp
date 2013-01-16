#include "ModifierOp.h"
#include <QDebug>



ModifierOp::ModifierOp(QWidget *parent): QWidget(parent)
{
    model = new QSqlTableModel();
    model->setTable("operateurs");
    model->select();
    setStyleSheet(        "QWidget#ModifierOp {"
                          "background: white;"
                          "}"
                          "QPushButton {"
"color: white;"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);"
"border-width: 1px;"
"border-color: #339;"
"border-style: solid;"
"border-radius: 7;"
"padding: 3px;"
"padding-left: 5px;"
"font-weight: bold;"
"font-size: 13px;"
"padding-right: 5px;"
"min-width: 90px;"
"max-width: 90px;"
"min-height: 12px;"
"max-height: 16px;"
"}"

                          "QLineEdit {"
                          "padding: 1px;"
                          "border-style: solid;"
                          "border: 2px solid gray;"
                          "border-radius: 8px;"
			  "max-width:160px;"
			  "min-width:160px;"
                          "}"
			  "QLabel {"
                          "color: black;"
                          "font-weight: bold;"
                          "}"
	                  
			  "QGroupBox {"
                          "border: 3px solid gray;"
                          "border-radius: 40px;"
                          "background: white;"
                           "background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #eef, stop: 1 #ccf);"
                          "}"
			  
      
    );
setWindowTitle("Modifier Operateur");
valider = new QPushButton("Valider");
retour = new QPushButton("Retour");
login = new QLineEdit;
setCompleter();
password = new QLineEdit;
password->setEchoMode(QLineEdit::Password);
matricule = new QLineEdit;
box = new QGroupBox(this);
form = new QFormLayout;
form->addRow("Login",login);
form->addRow("Matricule",matricule);
form->addRow("Password",password);
box->setLayout(form);
box->move(200,200);
grid = new QGridLayout;
grid->addWidget(retour,0,4,1,1,Qt::AlignLeft);
grid->addWidget(valider,0,6,1,1,Qt::AlignHCenter);
layout = new QVBoxLayout();
layout->addWidget(box);
layout->addLayout(grid);
setLayout(layout);
QFrame *frame = new QFrame(this);
frame->setLayout(layout);
frame->setFixedSize(400,400);
frame->move(200,0);


}

void ModifierOp::setCompleter()
{

    QString mod;
    //completeop->setModel(model);
    QSqlQuery last("select login from operateurs");
    QStringList logins;
    while(last.next())
    {
        mod = last.value(0).toString();
        logins << mod;
    }
        //
    completeop = new QCompleter(logins);
    //completeop->setCompletionColumn(1);
    completeop->setCompletionMode(QCompleter::PopupCompletion);
    completeop->setCaseSensitivity(Qt::CaseInsensitive);
    login->setCompleter(completeop);

}



