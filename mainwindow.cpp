#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseurs.h"
#include "connexion.h"
#include <QSqlQuery>
#include <QPushButton>
#include <QtWidgets>
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>

QSqlDatabase db;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(fourni.Afficherfournisseurs());
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
    connect(ui->update, &QPushButton::clicked, this, &MainWindow::onUpdateButtonClicked);
    connect(ui->update, &QPushButton::clicked, this, [this]() { navigateToPage(0); });
    connect(ui->miseajour, &QPushButton::clicked, this, &MainWindow::onmiseajourButtonClicked);
    connect(ui->miseajour, &QPushButton::clicked, this, [this]() { navigateToPage(1); });


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
    QString Date_f =ui->dateEdit->date().toString("yyyy-MM-dd");
    QString Telephone =ui->lineEdit_tel->text();
    QString Statut;


    /*bool statutValide = false;
    while (!statutValide) {
        // Afficher un message à l'utilisateur pour sélectionner un statut
        QMessageBox::information(this, "Sélection du statut", "Veuillez choisir un statut pour le fournisseur :");

        // Lire la valeur sélectionnée par l'utilisateur
        if (ui->enregistree->isChecked()) {
            Statut = "Enregistrée";}
        else if (ui->attente->isChecked()) {
            Statut = "En attente de réception";}
        else if (ui->incomplete->isChecked()) {
            Statut = "Réception incomplète";}
        else if (ui->finalisee->isChecked()) {
            Statut = "Réception finalisée";
        }

        // Vérifier si la valeur est valide
        if (Statut == "Enregistrée" || Statut == "En attente de réception" || Statut == "Réception incomplète" || Statut == "Réception finalisée")
        {
            statutValide = true;}
        else {
            // Afficher un message d'erreur si la valeur est invalide
            QMessageBox::warning(this, "Erreur de statut", "Le statut sélectionné est invalide. Veuillez choisir une valeur parmi : Enregistrée, En attente, Incomplète, Finalisée.");
        }
    }*/

    // Vérifier si un statut a été sélectionné
        if (ui->enregistree->isChecked()) {
            Statut = "Enregistree";
        } else if (ui->attente->isChecked()) {
            Statut = "En attente de reception";
        } else if (ui->incomplete->isChecked()) {
            Statut = "Reception incomplete";
        } else if (ui->finalisee->isChecked()) {
            Statut = "Reception finalisee";
        } else {
            QMessageBox::warning(this, "Erreur de statut", "Veuillez choisir un statut pour le fournisseur.");
            return; // Sortir de la fonction si aucun statut n'est sélectionné
        }


  /*  if( Nom.isEmpty()){
        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir le nom du fournisseur."),QMessageBox::Cancel);

    }*/
        QRegExp nomRegex("^[^0-9]*$"); // Ne contient pas de chiffres
            if(!nomRegex.exactMatch(Nom))
            {
                QMessageBox::critical(this, "Erreur", "Veuillez saisir un nom de représentant valide.");
                return;
            }

    if( Nombre.isEmpty()){
        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir le nombre."),QMessageBox::Cancel);

    }
            bool ok;
                int numValue = Telephone.toInt(&ok); // Convertit la chaîne en un entier
                if(!ok || Telephone.length() != 8 )
                {
                    QMessageBox::critical(this, "Erreur", "Le numéro du fournisseur doit être un nombre de 8 chiffres.");
                    return;
                }


    /*if( Telephone.isEmpty()){
        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir le telephone."),QMessageBox::Cancel);

    }*/

      fournisseurs f(0, Nom, Materiel, Nombre.toInt(), Telephone.toInt(), Date_f, Statut);
      bool test=f.Ajouterfournisseurs();
      if (test) //si requete executée
        {
            //refresh (actualiser)
            ui->tableView->setModel(fourni.Afficherfournisseurs());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                 "Click cancel to exit."),QMessageBox::Cancel);
        }
        else //si requete non executée
      {  QMessageBox::critical(nullptr, QObject::tr("OK"),
                         QObject::tr("Ajout non effectué\n"
                                     "Click cancel to exit."),QMessageBox::Cancel);
      }

       // Réinitialiser les champs
        ui->comboBox_materiel->setCurrentIndex(0);
        ui->lineEdit_nom->clear();
        ui->lineEdit_tel->clear();
        ui->lineEdit_nombre->clear();
        ui->dateEdit->clear();
        ui->enregistree->setChecked(false);
        ui->attente->setChecked(false);
        ui->incomplete->setChecked(false);
        ui->finalisee->setChecked(false);



}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        qDebug() << "Selected Index Row:" << row;
        int Id = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();
        qDebug() << "Selected Fournisseur ID:" << Id;
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirm Deletion",
                                             "Are you sure you want to delete the fournisseur with Id: " + QString::number(Id) + "?",
                                             QMessageBox::Yes|QMessageBox::No);

        if (confirmation == QMessageBox::Yes) {
            fournisseurs F;
            bool success = F.supprimerfournisseur(Id);
            if(success) {
                ui->tableView->setModel(fourni.Afficherfournisseurs());
                QMessageBox::information(this, "Fournisseur Supprimé", "Le fournisseur selectionne a ete supprime.");
            } else {
                QMessageBox::warning(this, "Error", "Failed to delete fournisseur.");
            }
        }
    } else {
        QMessageBox::warning(this, "No fournisseur Selected", "Please select a fournisseur to delete.");
    }
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QTabWidget* tWidget = ui->tabWidget;
    QWidget* page = tWidget->widget(1);
    QLineEdit* Id = page->findChild<QLineEdit*>("Id");

    if (!Id) {
        qDebug() << "ID LineEdit not found on page";
        return;
    }

    QString value = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
    Id->setText(value);
    connexion c;
    c.closeconnect();
    QSqlQuery qry;

    qry.prepare("select Nom,Materiel,Nombre,Telephone,Date_f,Statut from fournisseurs where Id=:Id");
    qry.bindValue(":Id", value);
    if (qry.exec())
    {
        while (qry.next())
        {
            ui->lineEdit_nom->setText(qry.value(0).toString());
            ui->comboBox_materiel->setCurrentText(qry.value(1).toString());
            ui->lineEdit_nombre->setText(qry.value(2).toString());

            QString date;
            date =qry.value(3).toString();
            /*QDate Date_f = QDate::fromString(data,"yyyy-MM-dd");
            ui->dateEdit->setDate(Date_f);*/
            if (!date.isEmpty()) {
                QDate Date_f = QDate::fromString(date, "yyyy-MM-dd");
                if (Date_f.isValid()) {
                    ui->dateEdit->setDate(Date_f);
                } else {
                    qDebug() << "Invalid date format:" << date;
                }
            } else {
                qDebug() << "Empty date value retrieved from database.";
            }


            ui->lineEdit_tel->setText(qry.value(4).toString());
            QString Statut = qry.value(5).toString();
            if (Statut == "Enregistree") {
                ui->enregistree->setChecked(true);
            }else {
                ui->enregistree->setChecked(false);
            }

            int numbercoloumn;
            numbercoloumn=ui->tableView->model()->columnCount();
            qDebug()<<numbercoloumn;
        }
    }
    else {
        qDebug() << "Query failed:" << qry.lastError().text();
    }
}

void MainWindow::onUpdateButtonClicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Row Selected", "Please select an employee to update.");
        return;
    }
    int row = selectedIndexes.first().row();
    QString Nom = ui->tableView->model()->index(row, 1).data().toString();
    QString Materiel = ui->tableView->model()->index(row, 2).data().toString();
    QString Nombre = ui->tableView->model()->index(row, 3).data().toString();
    QString Date_f = ui->tableView->model()->index(row, 4).data().toString();
    QString Telephone = ui->tableView->model()->index(row, 5).data().toString();
    QString Statut = ui->tableView->model()->index(row, 6).data().toString();

    ui->lineEdit_nom->setText(Nom);
    ui->comboBox_materiel->setCurrentText(Materiel);
    ui->lineEdit_nombre->setText(Nombre);
    QDate date = QDate::fromString(Date_f, "yyyy-MM-dd");
    ui->dateEdit->setDate(date);
    ui->lineEdit_tel->setText(Telephone);

    if (Statut == "Enregistree") {
        ui->enregistree->setChecked(true);
    }else {
        ui->enregistree->setChecked(false);
    }
    if (Statut == "En attente de reception") {
        ui->attente->setChecked(true);
    }else {
        ui->attente->setChecked(false);
    }
    if (Statut == "Reception incomplete") {
        ui->incomplete->setChecked(true);
    }else {
        ui->incomplete->setChecked(false);
    }
    if (Statut == "Reception finalisee") {
        ui->finalisee->setChecked(true);
    }else {
        ui->finalisee->setChecked(false);
    }
    navigateToPage(0);
}

void MainWindow::onmiseajourButtonClicked()
{
    QString Nom = ui->lineEdit_nom->text();
    QString Materiel = ui->comboBox_materiel->currentText();
    QString Nombre = ui->lineEdit_nombre->text();
    QString Date_f =ui->dateEdit->date().toString("yyyy-MM-dd");
    QString Telephone = ui->lineEdit_tel->text();
    QString Statut;
    if (ui->enregistree->isChecked()) {
        Statut = "Enregistree";
    } else if (ui->attente->isChecked()) {
        Statut = "En attente de reception";
    } else if (ui->incomplete->isChecked()) {
        Statut = "Reception incomplete";
    } else if (ui->finalisee->isChecked()) {
        Statut = "Reception finalisee";
    }

    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Row Selected", "SVP faite selectionner un fournisseur à modifier.");
        return;
    }
    int row = selectedIndexes.first().row();
    int Id = ui->tableView->model()->index(row, 0).data().toInt();
    fournisseurs Fourni;
    bool success = Fourni.updatefournisseur(Id, Nom, Materiel, Nombre.toInt(), Telephone.toInt(), Date_f, Statut);
    if (success) {
        QMessageBox::information(this, "Update Successful", "Les informations du fournisseur a été modifié avec succès.");
        navigateToPage(1);
        ui->tableView->setModel(fourni.Afficherfournisseurs());
        ui->lineEdit_nom->clear();
                ui->comboBox_materiel->setCurrentIndex(0);
                ui->lineEdit_nombre->clear();
                ui->dateEdit->clear();
                ui->lineEdit_tel->clear();
                ui->enregistree->setChecked(false);
                ui->attente->setChecked(false);
                ui->incomplete->setChecked(false);
                ui->finalisee->setChecked(false);
    } else {
        QMessageBox::warning(this, "Update Failed", "La modification a échoué.");
    }
}

/*void MainWindow::onUpdateClicked() {
    ui->cadd->setVisible(false);
    ui->cupdate->setVisible(true);*/

void MainWindow::navigateToPage(int pageIndex)
{
    ui->tabWidget->setCurrentIndex(pageIndex);
}

