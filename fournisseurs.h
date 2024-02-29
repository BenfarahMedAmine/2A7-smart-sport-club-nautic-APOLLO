#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class fournisseurs
{
private:
    int Id;
    QString Nom;
    QString Materiel;
    int Nombre;
    int Telephone;
    QString Date;


public:
    fournisseurs();
    fournisseurs(int Id, QString Nom, QString Materiel, int Nombre, int Telephone, QString Date)
    {
        this->Id = Id;
        this->Nom = Nom;
        this->Materiel = Materiel;
        this->Nombre = Nombre;
        this->Telephone = Telephone;
        this->Date = Date;

    }

    // Setters
    void setID(int i) { Id = i; }
    void setNom(QString n) { Nom = n; }
    void setMateriel(QString n) { Materiel = n; }
    void setNombre(int e) { Nombre = e; }
    void setTelephone(int p) { Telephone = p; }
    void setDate(QString b) { Date = b; }


    // Getters
    int getID() { return Id; }
    QString getNom() { return Nom; }
    QString getMateriel() { return Materiel; }
    int getNombre() { return Nombre; }
    int getTelephone() { return Telephone; }
    QString getDate() { return Date; }


    bool Ajouterfournisseurs();
    QSqlQueryModel *Afficherfournisseurs();
    bool Modifierfournisseurs();
    bool Supprimerfournisseurs();
    QSqlQueryModel *Rechercherfournisseurs(QString value);
    QSqlQueryModel *Trierfournisseurs(QString croissance, QString critere);
};

#endif // FOURNISSEURS_H
