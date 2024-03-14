
#include "materiel.h"
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

materiel::materiel()
{
etat="";
prix=0;
id_emp=0;
id_fourni=0;

}
bool materiel::ajouter_mat()
{
    QSqlQuery query;
    query.prepare("INSERT INTO MATERIEL (ETAT, PRIX, ID_EMP, ID_FOURNI) VALUES (:etat, :prix, :id_emp, :id_fourni)");
    query.bindValue(":etat", etat);
    query.bindValue(":prix", prix);
    query.bindValue(":id_emp", id_emp);
    query.bindValue(":id_fourni", id_fourni);

    return query.exec();
}


QSqlQueryModel *materiel::afficher_mat()
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery("SELECT * FROM MATERIEL");
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("id_mat"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("id_emp"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("id_fourni"));
    return modal;
}

bool materiel::updateMaterial(int id_mat, const QString& etat, int prix, int id_emp, int id_fourni)
{
    QSqlQuery query;
    query.prepare("UPDATE MATERIEL SET ETAT = :etat, PRIX = :prix, ID_EMP = :id_emp, ID_FOURNI = :id_fourni WHERE ID_MAT = :id_mat");
    query.bindValue(":etat", etat);
    query.bindValue(":prix", prix);
    query.bindValue(":id_emp", id_emp);
    query.bindValue(":id_fourni", id_fourni);
    query.bindValue(":id_mat", id_mat);

    return query.exec();
}

bool materiel::delete_mat(int id_mat)
{
    QSqlQuery query;
    query.prepare("DELETE FROM MATERIEL WHERE ID_MAT = :id_mat");
    query.bindValue(":id_mat", id_mat);

    return query.exec();
}
