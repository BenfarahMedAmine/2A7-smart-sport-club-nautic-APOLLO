#include "employee.h"
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

Employee::Employee()
{
    NOM = "";
    PRENOM = "";
    EMAIL="";
    PASSWORD="";
    SEXE = "";
    TELEPHONE ="";
    ADRESS = "";
    SALAIRE ="";
    ROLE = "";
}

bool Employee::Ajouter_Employe()
{
    QSqlQuery query_Insert;
    query_Insert.prepare("INSERT INTO EMPLOYEE (NOM,PRENOM,EMAIL,PASSWORD,TELEPHONE,SALAIRE,ADRESS,SEXE,ROLE) VALUES (:nom,:prenom,:email,:password,:sexe,:telephone,:adress,:salaire,:role)");
    query_Insert.bindValue(":nom", NOM);
    query_Insert.bindValue(":prenom", PRENOM);
    query_Insert.bindValue(":email", EMAIL);
    query_Insert.bindValue(":password", PASSWORD);
    query_Insert.bindValue(":telephone", TELEPHONE);
    query_Insert.bindValue(":salaire", SALAIRE);
    query_Insert.bindValue(":adress", ADRESS);
    query_Insert.bindValue(":sexe", SEXE);
    query_Insert.bindValue(":role", ROLE);
    bool success = query_Insert.exec();
    if (!success) {
        qDebug() << "Error inserting employee:" << query_Insert.lastError().text();
    }
    return success;
}

QSqlQueryModel* Employee::Afficher_Employe()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EMP, NOM, PRENOM, EMAIL, PASSWORD, TELEPHONE, SALAIRE, ADRESS, SEXE, ROLE FROM EMPLOYEE");
    // Adjust the order of setting header data to match the desired column order
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMP"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PASSWORD"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ADRESS"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("ROLE"));

    if (model->lastError().isValid()) {
        qDebug() << "Error loading employee data:" << model->lastError().text();
    }
    return model;
}


bool Employee::Delete_Employe(int ID_EMP)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYEE WHERE ID_EMP = :ID_EMP");
    query.bindValue(":ID_EMP", ID_EMP);
    bool success = query.exec();
    if (!success) {
        qDebug() << "Error deleting employee:" << query.lastError().text();
    }
    return success;
}
bool Employee::Update_Employe(int ID_EMP, const QString& NOM, const QString& PRENOM, const QString& EMAIL, const QString& PASSWORD, const QString& SEXE, const QString& TELEPHONE, const QString& ADRESS, const QString& SALAIRE, const QString& ROLE)
{
    qDebug() << "Updating employee with values:";
    qDebug() << "ID_EMP:" << ID_EMP;
    qDebug() << "NOM:" << NOM;
    qDebug() << "PRENOM:" << PRENOM;
    qDebug() << "EMAIL:" << EMAIL;
    qDebug() << "PASSWORD:" << PASSWORD;
    qDebug() << "TELEPHONE:" << TELEPHONE;
    qDebug() << "ADRESS:" << ADRESS;
    qDebug() << "SALAIRE:" << SALAIRE;
    qDebug() << "SEXE:" << SEXE;
    qDebug() << "ROLE:" << ROLE;

    QSqlQuery query_Update;
    query_Update.prepare("UPDATE EMPLOYEE SET NOM = :nom, PRENOM = :prenom, EMAIL=:email, PASSWORD=:password, TELEPHONE = :telephone, SALAIRE = :salaire, ADRESS = :adress , SEXE = :sexe, ROLE = :role WHERE ID_EMP = :id_emp");
    query_Update.bindValue(":nom", NOM);
    query_Update.bindValue(":prenom", PRENOM);
    query_Update.bindValue(":email", EMAIL);
    query_Update.bindValue(":password", PASSWORD);
    query_Update.bindValue(":telephone", TELEPHONE);
    query_Update.bindValue(":salaire", SALAIRE);
    query_Update.bindValue(":adress", ADRESS);
    query_Update.bindValue(":sexe", SEXE);
    query_Update.bindValue(":role", ROLE);
    query_Update.bindValue(":id_emp", ID_EMP);

    bool success = query_Update.exec();
    if (!success) {
        qDebug() << "Error updating employee:" << query_Update.lastError().text();
        qDebug() << "Query executed:" << query_Update.lastQuery();
    }
    return success;
}




