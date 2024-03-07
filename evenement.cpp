#include "evenement.h"
#include <QDebug>
#include <QSqlError>
#include <vector>
evenement:: evenement(int id ,QString type_event,QString duree,QString sponsor,int montant)

{

 this->id=id;
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


bool evenement::ajouter()
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



QSqlQueryModel* evenement::afficher()
{
  /*  QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery(" SELECT * FROM EVENEMENTS ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type_event "));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr(" duree "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr(" montant "));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr(" sponsor "));
    qDebug() << "Nombre de lignes récupérées depuis la base de données : " << model->rowCount();

return model ;*/
    QSqlQueryModel* model = new QSqlQueryModel();
       QSqlDatabase db = QSqlDatabase::database(); // Récupère la connexion active à la base de données

       if (!db.isOpen()) { // Vérifie si la connexion est ouverte
           qDebug() << "Erreur: Connexion à la base de données non ouverte.";
           return nullptr; // Retourne un modèle nul en cas d'erreur
       }

       QSqlQuery query(db); // Utilise la connexion active pour la requête

       if (!query.exec("SELECT * FROM EVENEMENTS")) { // Exécute la requête SQL
           qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
           return nullptr; // Retourne un modèle nul en cas d'erreur
       }

       model->setQuery(query); // Définit le modèle de données avec les résultats de la requête

       return model; // Retourne le modèle de données
}
/*
bool evenement::supprimer(int id)
{ QSqlQuery query ;
  QString res=QString ::number(id);
query.prepare((" Delete from evenements where ID= :id"));
query.bindValue(":id",res);
return query.exec();
}*/
bool evenement::deleteEvent(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM evenements WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression de l'événement :" << query.lastError().text();
        return false;
    }

    return true;
}

bool evenement::modifier(int id)
{
    QString rid=QString::number(id);

        QSqlQuery query;
           query.prepare(QString("update evenements set type_event=:type_event,duree=:duree,montant=:montant,sponsor=:sponsor where id=:id"));

           query.bindValue(":id",rid);
           query.bindValue(":type_event",type_event);
           query.bindValue(":duree", duree);

           query.bindValue(":montant",montant);
           query.bindValue(":sponsor", sponsor);


         return  query.exec();
}


