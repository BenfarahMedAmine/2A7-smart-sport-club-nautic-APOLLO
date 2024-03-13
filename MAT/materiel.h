#ifndef INVITE_H
#define INVITE_H

#include "connection.h"
#include <QString>
#include "QMessageBox"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QLineEdit>
#include <QTableView>
#include <QMessageBox>
#include <QSqlQueryModel>
class materiel
{
private:
    int id_mat;
    QString etat;
    int prix;
    int id_emp;
    int id_fourni;

public:
    materiel();
    materiel(QString etat,int prix,int id_emp, int id_fourni)
    {
        this->etat = etat;
        this->prix =prix;
        this->id_emp = id_emp;
        this->id_fourni = id_fourni;

    }


    bool ajouter_mat();
    QSqlQueryModel *afficher_mat();
    bool delete_mat(int id_mat);
    bool updateMaterial(int id_mat, const QString& etat, int prix, int id_emp, int id_fourni);

};

#endif // INVITE_H
