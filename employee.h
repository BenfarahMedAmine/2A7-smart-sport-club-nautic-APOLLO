#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QDebug>
#include <QStackedWidget>
#include <QMap>
#include <QFile>
#include <QString>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Employee
{
private:
    int ID_EMP;
    QString NOM;
    QString PRENOM;
    QString EMAIL;
    QString PASSWORD;
    QString SEXE;
    QString TELEPHONE;
    QString ADRESS;
    QString SALAIRE;
    QString ROLE;
public:
    Employee();
    Employee(QString NOM,QString PRENOM,QString EMAIL,QString PASSWORD,QString SEXE,QString TELEPHONE,QString ADRESS,QString SALAIRE,QString ROLE)
    {
        this->NOM=NOM;
        this->PRENOM=PRENOM;
        this->EMAIL=EMAIL;
        this->PASSWORD=PASSWORD;
        this->SEXE=SEXE;
        this->TELEPHONE=TELEPHONE;
        this->ADRESS=ADRESS;
        this->SALAIRE=SALAIRE;
        this->ROLE=ROLE;

    }
    bool Ajouter_Employe();
    QSqlQueryModel * Afficher_Employe();
    bool Delete_Employe(int ID_EMP);
    bool Update_Employe(int ID_EMP, const QString& NOM, const QString& PRENOM,const QString& EMAIL,const QString& PASSWORD, const QString& SEXE, const QString& TELEPHONE, const QString& ADRESS, const QString& SALAIRE, const QString& ROLE);
};

#endif // EMPLOYEE_H
