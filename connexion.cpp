#include "connexion.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

connexion::connexion()
{

}

bool connexion::createconnect()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("PoolPilot");
db.setUserName("sinda");
db.setPassword("sinda");

if (db.open())
test=true;




return test;
}



void connexion::closeconnect(){ db.close(); }

void connexion::executerRequete(const QString& requete)
{
    QSqlQuery query(db);
    if (!query.exec(requete)) {
        qDebug() << "Erreur d'exécution de la requête : " << query.lastError().text();
    }
}
