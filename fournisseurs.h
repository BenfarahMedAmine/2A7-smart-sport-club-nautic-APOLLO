#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>


class fournisseurs
{
private:
    int Id;
    QString Nom;
    QString Materiel;
    int Nombre;
    int Telephone;
    QString Date_f;
    QString Statut;


public:
    fournisseurs(){}
    fournisseurs(int, QString, QString, int, int, QString, QString);



    // Getters
    int getID() { return Id; }
    QString getNom() { return Nom; }
    QString getMateriel() { return Materiel; }
    int getNombre() { return Nombre; }
    int getTelephone() { return Telephone; }
    QString getDate_f() { return Date_f; }
    QString getStatut() { return Statut; }

    // Setters
    void setID(int i) { Id = i; }
    void setNom(QString n) { Nom = n; }
    void setMateriel(QString m) { Materiel = m; }
    void setNombre(int nb) { Nombre = nb; }
    void setTelephone(int t) { Telephone = t; }
    void setDate_f(QString d) { Date_f = d; }
    void setStatut(QString s) { Statut = s; }



    bool Ajouterfournisseurs();
    QSqlQueryModel *Afficherfournisseurs();
    /*bool Modifierfournisseurs();*/
    bool supprimerfournisseur(int ID_F);

     bool updatefournisseur(int ID, const QString& NOM, const QString& MATERIEL, int NOMBRE, int TELEPHONE, const QString& DATE_F, const QString& STATUT);
};

#endif // FOURNISSEURS_H
