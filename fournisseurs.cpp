#include "fournisseurs.h"

fournisseurs::fournisseurs()
{

}

bool fournisseurs::Ajouterfournisseurs()
{
    QSqlQuery query;

    query.prepare("INSERT INTO fournisseurs (Nom, Materiel, Nombre, Telephone, Date_f) VALUES (:Nom, :Materiel, :Nombre, :Telephone, :Date)");

    query.bindValue(":Nom", Nom);
    query.bindValue(":Materiel", Materiel);
    query.bindValue(":Nombre", Nombre);
    query.bindValue(":Telephone", Telephone);
    query.bindValue(":Date", Date);


    return query.exec();
}
QSqlQueryModel *fournisseurs::Afficherfournisseurs()
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    modal->setQuery("SELECT * FROM fournisseurs");
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Materiel"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("Telephone"));
    modal->setHeaderData(5, Qt::Horizontal, QObject::tr("Date"));


    return modal;
}
bool fournisseurs::Modifierfournisseurs()
{
    QSqlQuery query;

    query.prepare("UPDATE fournisseurs SET Nom = :Nom, Materiel = :Materiel, Nombre = :Nombre, Telephone = :Telephone, Date_f = :Date WHERE Id = :Id");

    query.bindValue(":Nom", Nom);
    query.bindValue(":Materiel", Materiel);
    query.bindValue(":Nombre", Nombre);
    query.bindValue(":Telephone", Telephone);
    query.bindValue(":Date", Date);
    query.bindValue(":Id", Id);

    return query.exec();
}
bool fournisseurs::Supprimerfournisseurs()
{
    QSqlQuery query;

    query.prepare("DELETE FROM fournisseurs WHERE Id = :Id");
    query.bindValue(":Id", Id);

    return query.exec();
}
