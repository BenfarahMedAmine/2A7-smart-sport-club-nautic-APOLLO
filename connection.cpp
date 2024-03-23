#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet");
    db.setUserName("Anas");
    db.setPassword("esprit18");
    if (db.open())
        test=true;
    return  test;
}
void Connection::closeconnection()
{
    db.close();
}
QSqlDatabase Connection::getdb()
{
    return db;
}
