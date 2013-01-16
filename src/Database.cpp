#include "Database.h"


Database::Database()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("41.224.243.211"); //192.168.10.151
    db.setDatabaseName("stephan");
    db.setUserName("Chef_Stephan");//stephan_admin
    db.setPassword("stephan"); //SimuLabo


}

void Database::openConnection(){

    if (!db.open())
    {  QMessageBox::critical(0,QObject::tr("Database Error"),
                             db.lastError().text());
     }

    else ;

}

QSqlDatabase Database::getDb(){

    return db;
}

