#ifndef CONNECTION_H
#define CONNECTION_H
#include <QDebug>
#include <QStackedWidget>
#include <QMap>
#include <QFile>
#include <QString>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
class Connection
{
    QSqlDatabase db;
public:
    Connection();
     bool createconnect();
     void closeconnection();
};

#endif // CONNECTION_H
