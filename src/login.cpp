#include "login.h"
#include "ui_login.h"



Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setFixedSize(800,480);
    ui->connexion->installEventFilter(this);
    QObject::connect(ui->connexion,SIGNAL(clicked()),this,SLOT(check()));

}

Login::~Login()
{
    delete ui;
    //delete connexion;
}

bool Login::check()
{

    QString login = ui->log->text();

    QString password = ui->pass->text();
    operateur = login;
    

    QString str = "SELECT id from Admin where login = ";
    str.append("\""+login+"\"").append(" AND password = ").append("\""+password+"\"");

    QSqlQuery verify(str);

    while(verify.next())
        id = verify.value(0).toString();
       
    if (!id.isNull())
    {
        id.clear();
        return true;

    }

    else

    {

        return false;

    }
}

void Login::eraserHead()
{

    ui->log->clear();
    ui->pass->clear();
}


bool Login::eventFilter(QObject* connex, QEvent* e)
{ 
  if ((connex = ui->connexion) && (e->type() == QEvent::KeyPress))
    {
      QKeyEvent *keyevent = static_cast<QKeyEvent *>(e);
      if (keyevent->key() == Qt::Key_Return)
      { 
	if(check())
	{  emit triggerUnderground();
	   return true;
        }
      }
  
}
return QObject::eventFilter(connex, e);
}