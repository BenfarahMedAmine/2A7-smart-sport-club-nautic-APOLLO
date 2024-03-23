#include "evenement.h"
#include <QDebug>
#include <QStackedWidget>
#include <QMap>
#include <QFile>
#include <QString>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

evenement:: evenement(int id_event,QString type_event,QString duree,QString sponsor,int montant)
{
 this->id_event=id_event;
 this->type_event=type_event;
 this->duree=duree;
 this->sponsor=sponsor;
 this->montant=montant;
}
evenement:: evenement(QString type_event,QString duree,QString sponsor,int montant)

{
 this->type_event=type_event;
  this->duree=duree;
  this->sponsor=sponsor;
 this->montant=montant;
}


bool evenement::ajouterevenement()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EVENEMENTS (TYPE_EVENT, duree, montant, sponsor) VALUES (:type_event, :duree, :montant, :sponsor)");
    query.bindValue(":type_event", type_event);
    query.bindValue(":duree", duree);
    query.bindValue(":montant", montant);
    query.bindValue(":sponsor", sponsor);


    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête d'insertion :" << query.lastError().text();
        return false;
    }

    return true;
}



QSqlQueryModel* evenement::afficherevenement()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       QSqlDatabase db = QSqlDatabase::database();

       if (!db.isOpen()) {
           qDebug() << "Erreur: Connexion à la base de données non ouverte.";
           return nullptr;
       }

       QSqlQuery query(db);

       if (!query.exec("SELECT * FROM EVENEMENTS")) { // Exécute la requête SQL
           qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
           return nullptr;
       }
       model->setQuery(query);

       return model;
}

bool evenement::deleteEvent(int id_event)
{
    QSqlQuery query;
    query.prepare("DELETE FROM evenements WHERE id_event = :id_event");
    query.bindValue(":id_event", id_event);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression de l'événement :" << query.lastError().text();
        return false;
    }

    return true;
}

bool evenement:: modifierevenement(int ID_EVENT, const QString& TYPE_EVENT, const QString& DUREE, double MONTANT, const QString& SPONSOR)
{
    QSqlQuery query_Update;
    query_Update.prepare("UPDATE EVENEMENTS SET TYPE_EVENT = :type_event, DUREE = :duree, MONTANT = :montant, SPONSOR = :sponsor WHERE ID_EVENT = :id_event");
    query_Update.bindValue(":type_event", TYPE_EVENT);
    query_Update.bindValue(":duree", DUREE);
    query_Update.bindValue(":montant", MONTANT);
    query_Update.bindValue(":sponsor", SPONSOR);
    query_Update.bindValue(":id_event", ID_EVENT);

    bool success = query_Update.exec();
    if (!success)
    {
        qDebug() << "Error updating event:" << query_Update.lastError().text();
        qDebug() << "Query executed:" << query_Update.lastQuery();
    }
    return success;
}

