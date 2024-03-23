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
   int id_event;
  QString type_event,sponsor,duree;
  int montant;
public:
  // constructeur
  evenement(){}
  evenement(int,QString,QString,QString,int);
  evenement(QString type_event,QString duree,QString sponsor,int montant);


  // Getters
  int getIDevenet() {return id_event;}
  QString getTYPE_EVENT(){return type_event;}
  QString getDUREE(){return duree;}
  QString getSPONSOR(){return sponsor;}
  int getMONTANT(){return montant;}


  //setters
  void setID(int id_event ){ this->id_event=id_event;}
  void setTYPE_EVENT(QString t){ type_event=t;}
  void setDUREE(QString d){ duree=d;}
  void setSPONSOR(QString s){ sponsor=s;}
  void setMONTANT(int m){ montant=m; }

  // fonctionalite
 bool ajouterevenement();
 QSqlQueryModel * afficherevenement() ;
 bool deleteEvent(int id_event);
 bool modifierevenement(int ID_EVENT, const QString& TYPE_EVENT, const QString& DUREE, double MONTANT, const QString& SPONSOR);
};


#endif // EVENEMENT_H
