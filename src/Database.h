#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QtDebug>
#include <QSqlError>

class Database {
public:
    Database();
    void openConnection();
    QSqlDatabase getDb();
private :
    QSqlDatabase db;

};

#endif // DATABASECONNECTION_H

