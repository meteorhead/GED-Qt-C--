#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QWidget>
#include <QtDebug>
#include <QSqlError>

extern QByteArray ipServer;
class Database : public QWidget{
  Q_OBJECT
public:
    explicit Database(QWidget *parent = 0);
    void openConnection();
    QSqlDatabase getDb();
    bool checkDB();
    QSqlDatabase db;
private :
   static bool connectionStatus;

};

#endif // DATABASECONNECTION_H
