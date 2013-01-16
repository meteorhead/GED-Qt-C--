#include "Database.h"
#include <QFile>
#include <sstream>
QByteArray ipServer = "0";
Database::Database(QWidget *parent) : QWidget(parent)
{  
    QFile file("/etc/stephan/ipserver.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          return;

    while (!file.atEnd())
    {

      ipServer = file.readLine();

    }
    
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ipServer); //192.168.23.10
    db.setDatabaseName("stephan");
    db.setUserName("Chef_Stephan");//Chef_Stephan
    db.setPassword("stephan"); //stephan



}

void Database::openConnection(){

    if (!db.open())
    {  QMessageBox::critical(0,QObject::tr("Database Error"),
                             db.lastError().text());
     }



}

QSqlDatabase Database::getDb(){

    return db;
}


bool Database::checkDB()
{
    return db.open();

}

