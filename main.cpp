#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test = c.createconnect();
    MainWindow w;
    if (test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    // Appliquer le style CSS à la fenêtre principale
    w.show();
    return a.exec();
}
