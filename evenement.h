#ifndef EVENEMENT_H
#define EVENEMENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDebug>
#include <vector>
class evenement
{
private:
   int id;
  QString type_event,sponsor,duree;
  int montant;
public:
  // constructeur

  evenement(){}
  evenement(int,QString,QString,QString,int);
  evenement(QString type_event,QString duree,QString sponsor,int montant);
  QList<int> getMontants();

  // Getters
  int getID() {return id;}
  QString getTYPE_EVENT(){return type_event;}
  QString getDUREE(){return duree;}
  QString getSPONSOR(){return sponsor;}
  int getMONTANT(){return montant;}


  //setters
  void setID(int id ){ this->id=id;}
  void setTYPE_EVENT(QString t){ type_event=t;}
  void setDUREE(QString d){ duree=d;}
  void setSPONSOR(QString s){ sponsor=s;}
  void setMONTANT(int m){ montant=m; }
  // fonctionalite

 bool ajouter();
 QSqlQueryModel * afficher() ;
 //bool  supprimer(int);
 bool deleteEvent(int id);
 bool modifier(int id);
};


#endif // EVENEMENT_H
