#include "connexion.h"

connexion::connexion()
{

}

bool connexion::createconnect()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("PoolPilot");
db.setUserName("sinda");
db.setPassword("sinda");

if (db.open())
test=true;




return test;
}

void connexion::closeconnect(){ db.close(); }
