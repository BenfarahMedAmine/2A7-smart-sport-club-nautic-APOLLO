#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Projet C++");
db.setUserName("abdelraouf");
db.setPassword("abdelraouf");
if (db.open())
test=true;
    return  test;
}
void Connection::closeconnection(){db.close();}
