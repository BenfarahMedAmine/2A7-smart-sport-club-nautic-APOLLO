#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseurs.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString Nom = ui->lineEdit_nom->text();
    QString Materiel =ui->comboBox_materiel->currentText();
    QString Nombre =ui->lineEdit_nombre->text();
    QString Date =ui->dateEdit->date().toString("yyyy-MM-dd");
    QString Tel =ui->lineEdit_tel->text();

    if( Nom.isEmpty()){
        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides."),QMessageBox::Cancel);

    }
    else{
        //refresh
        //contract con(0,type,date,date2,date3);
       fournisseurs fournisseurs(0,Nom,Materiel, Nombre.toInt(),Tel.toInt(),Date);
        fournisseurs.Ajouterfournisseurs();
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                 "Click cancel to exit."),QMessageBox::Cancel);
        ui->comboBox_materiel->setCurrentIndex(0);
        ui->lineEdit_nom->clear();
        ui->lineEdit_tel->clear();
        ui->lineEdit_nombre->clear();
        ui->dateEdit->clear();
    }

}
