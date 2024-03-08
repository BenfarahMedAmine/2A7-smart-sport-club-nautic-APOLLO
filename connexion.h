#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QtSql/QSqlDatabase>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QApplication>


class connexion
{
    QSqlDatabase db;
public:
    void executerRequete(const QString& requete);
    connexion();
    bool createconnect();
    void closeconnect();
};

#endif // CONNEXION_H
