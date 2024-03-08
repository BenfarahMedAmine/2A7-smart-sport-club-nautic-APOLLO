#include "fournisseurs.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

fournisseurs::fournisseurs(int Id, QString Nom, QString Materiel, int Nombre, int Telephone, QString Date_f, QString Statut)
{
    this->Id = Id;
    this->Nom = Nom;
    this->Materiel = Materiel;
    this->Nombre = Nombre;
    this->Telephone = Telephone;
    this->Date_f = Date_f;
    this->Statut = Statut;
}

bool fournisseurs::Ajouterfournisseurs()
{
    QSqlQuery query;

    query.prepare("INSERT INTO fournisseurs (Nom, Materiel, Nombre, Telephone, Date_f, Statut) VALUES (:Nom, :Materiel, :Nombre, :Telephone, :Date, :Statut)");

    query.bindValue(":Nom", Nom);
    query.bindValue(":Materiel", Materiel);
    query.bindValue(":Nombre", Nombre);
    query.bindValue(":Telephone", Telephone);
    query.bindValue(":Date_f", Date_f);
    query.bindValue(":Statut", Statut);

    bool success = query.exec();
    if (!success) {
        qDebug() << "Error d insertion fournisseurs:" << query.lastError().text();
    }
    return success;
}
QSqlQueryModel *fournisseurs::Afficherfournisseurs()
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    modal->setQuery("SELECT * FROM fournisseurs");
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Materiel"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("Telephone"));
    modal->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_f"));
    modal->setHeaderData(6, Qt::Horizontal, QObject::tr("Statut"));


    return modal;
}



bool fournisseurs::supprimerfournisseur(int Id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM fournisseurs WHERE Id = :Id");
    query.bindValue(":Id", Id);
    bool success = query.exec();
    if (!success) {
        qDebug() << "Error deleting fournisseur:" << query.lastError().text();
    }
    return success;
}

bool fournisseurs::updatefournisseur(int ID, const QString& NOM, const QString& MATERIEL, int NOMBRE, int TELEPHONE, const QString& DATE_F, const QString& STATUT)
{
    qDebug() << "Updating fournisseur with values:";
    qDebug() << "Id:" << Id;
    qDebug() << "Nom:" << Nom;
    qDebug() << "Materiel:" << Materiel;
    qDebug() << "Nombre:" << Nombre;
    qDebug() << "Telephone:" << Telephone;
    qDebug() << "Date_f:" << Date_f;
    qDebug() << "Statut:" << Statut;


    QSqlQuery query_Update;
    query_Update.prepare("UPDATE FOURNISSEURS SET NOM = :Nom, MATERIEL = :Materiel, NOMBRE = :Nombre, TELEPHONE = :Telephone, DATE_F = :Date_f, STATUT = :Statut WHERE ID = :Id");
    query_Update.bindValue(":Nom", NOM);
    query_Update.bindValue(":Materiel", MATERIEL);
    query_Update.bindValue(":Nombre", NOMBRE);
    query_Update.bindValue(":Telephone", TELEPHONE);
    query_Update.bindValue(":Date_f", DATE_F);
    query_Update.bindValue(":Statut", STATUT);
    query_Update.bindValue(":Id", ID);

    bool success = query_Update.exec();
    if (!success) {
        qDebug() << "Error updating fournisseur:" << query_Update.lastError().text();
        qDebug() << "Query executed:" << query_Update.lastQuery();
    }
    return success;
}


