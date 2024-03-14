#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include <iostream>
#include <QMessageBox>
#include <QDebug>
#include "connection.h"
#include <QtCharts>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QRegularExpression>
#include <QAxWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsView>
#include <QtCharts/QPieSeries>


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());


    series = new QtCharts::QPieSeries();
       chartView = new QtCharts::QChartView();
       chartView->setRenderHint(QPainter::Antialiasing);











    connect(ui->pushButton_9,&QPushButton::clicked,this,&MainWindow::clicker_list);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&MainWindow::clicker_list1);
    connect(ui->pushButton_10,&QPushButton::clicked,this,&MainWindow::clicker_list1);
    connect(ui->pushButton_10,&QPushButton::clicked,this,&MainWindow::clicker_list1);
    connect(ui->pushButton_11,&QPushButton::clicked,this,&MainWindow::clicker_list3);
    //connect(ui->pushButton_delete,&QPushButton::clicked,this,&MainWindow::clicker_delete);
    connect(ui->pushButton_add,&QPushButton::clicked,this,&MainWindow::clicker_add);
    connect(ui->pushButton_modifier,&QPushButton::clicked,this,&MainWindow::clicker_update);

    connect(ui->delete_2, &QPushButton::clicked, this, &MainWindow::on_deleteButtonEvent_clicked);





    connect(ui->pushButton_refresh, &QPushButton::clicked, this, &MainWindow::refreshTable);
    connect(ui->lineEdit_search, &QLineEdit::textChanged, this, &MainWindow::searchEvent);
    connect(ui->pushButton_asc, &QPushButton::clicked, this, &MainWindow::sortAscending);
    connect(ui->pushButton_desc, &QPushButton::clicked, this, &MainWindow::sortDescending);
    connect(ui->exportPdfButton, &QPushButton::clicked, this, &MainWindow::exportPdfEvent);
    connect(ui->exportCsvButton, &QPushButton::clicked, this, &MainWindow::exportCsv);

    connect(ui->pushButton_statistique_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_statistique_2_clicked);

    connect(ui->goevent, &QPushButton::clicked, this, &MainWindow::on_goevent_clicked);






    //tache materiels
    connect(ui->materiel, &QPushButton::clicked, this, &MainWindow::on_pushButton_4_clicked);
    connect(ui->tableView_2, &QTableView::activated, this, &MainWindow::on_tableView_activated);
    connect(ui->delete_3, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
    connect(ui->updatemat, &QPushButton::clicked, this, &MainWindow::onUpdateButtonClicked);
    connect(ui->cupdate, &QPushButton::clicked, this, &MainWindow::onMUpdateButtonClicked);
    connect(ui->cadd, &QPushButton::clicked, this, [this]() { navigateToPage(6); });
    connect(ui->cupdate, &QPushButton::clicked, this, [this]() { navigateToPage(6); });
    connect(ui->ListMat, &QPushButton::clicked, this, [this]() { navigateToPage(6); });
    connect(ui->AddMat, &QPushButton::clicked, this, [this]() { navigateToPage(7); });
    connect(ui->updatemat, &QPushButton::clicked, this, [this]() { navigateToPage(7); });
    //connect(ui->Stat, &QPushButton::clicked, this, [this]() { navigateToPage(2); });
    connect(ui->pdf, &QPushButton::clicked, this, &MainWindow::exportPdf);
    ui->tableView_2->setEditTriggers(QAbstractItemView::AnyKeyPressed);
    QStackedWidget* stackedWidget = ui->stackedWidget;
    QWidget * page = stackedWidget->widget(6);
    QTableView * tableView_2= page->findChild<QTableView*>("tableView_2");
    materiel m;
      ui->tableView_2->setModel(m.afficher_mat());
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString lastClickedButton;
void MainWindow::clicker_list()
{
   ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::clicker_list1()
{
   ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::clicker_list2()
{
   ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::clicker_list3()
{
   ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::clicker_delete()
{
   ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::clicker_statistics()
{
    ui->stackedWidget->setCurrentIndex(1);


}


void MainWindow::clicker_add()
{
   ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::clicker_update()
{
   ui->stackedWidget->setCurrentIndex(2);
}

#include <QRegularExpression>

void MainWindow::on_pushButton_ajouter_clicked()
{
    QString type_event = ui->lineEdit_type_event->text();
    QString duree = ui->lineEdit_duree->text();
    QString sponsor = ui->lineEdit_sponsor->text();
    QString montant_str = ui->lineEdit_montant->text();

    // Vérification si les champs de saisie ne sont pas vides
    if (type_event.isEmpty() || duree.isEmpty() || sponsor.isEmpty() || montant_str.isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return; // Sortie de la fonction
    }

    // Vérification si le montant est un entier valide
    bool montant_ok;
    int montant = montant_str.toInt(&montant_ok);
    if (!montant_ok)
    {
        QMessageBox::critical(this, "Erreur", "Montant invalide. Veuillez entrer un nombre entier.");
        return; // Sortie de la fonction
    }

    // Vérification si les chaînes ne contiennent pas de caractères spéciaux
    QRegularExpression regex("^[a-zA-Z0-9_]*$");
    if (!regex.match(type_event).hasMatch() || !regex.match(duree).hasMatch() || !regex.match(sponsor).hasMatch())
    {
        QMessageBox::critical(this, "Erreur", "Les champs ne doivent pas contenir de caractères spéciaux.");
        return; // Sortie de la fonction
    }

    qDebug() << "Type d'événement : " << type_event;
    qDebug() << "Duree : " << duree;
    qDebug() << "Sponsor : " << sponsor;
    qDebug() << "Montant : " << montant;

    // Création de l'objet evenement et ajout dans la base de données
    evenement E(type_event, duree, sponsor, montant);
    bool test = E.ajouter();
    if (test)
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Succès"),
                                 QObject::tr("Ajout effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}



/*void MainWindow::on_pushButton_supprimer_clicked()
{ int id =ui->lineEdit_ID_2->text().toInt();
    bool test=Etmp.supprimer(id);
    if (test)
    { ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr(" suppression effectué .\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok "),
                              QObject::tr(" suppression non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}*/
void MainWindow::on_deleteButtonEvent_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        qDebug() << "Selected Index Row:" << row;
        int eventID = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();
        qDebug() << "Selected Event ID:" << eventID;
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirm Deletion",
                                             "Are you sure you want to delete the event with ID: " + QString::number(eventID) + "?",
                                             QMessageBox::Yes|QMessageBox::No);

        if (confirmation == QMessageBox::Yes) {
            evenement E;
            bool success = E.deleteEvent(eventID);
            if(success) {
                ui->tableView->setModel(E.afficher());
                QMessageBox::information(this, "Event Deleted", "The selected event has been deleted.");
            } else {
                QMessageBox::warning(this, "Error", "Failed to delete event.");
            }
        }
    } else {
        QMessageBox::warning(this, "No Event Selected", "Please select an event to delete.");
    }
}

void MainWindow::on_pushButton_update_clicked()
{
    QString id_str = ui->lineEdit_ID_3->text();
    QString type_event = ui->lineEdit_type_event_2->text();
    QString duree = ui->lineEdit_duree_2->text();
    QString montant_str = ui->lineEdit_montant_2->text();
    QString sponsor = ui->lineEdit_sponsor_2->text();

    // Vérification que tous les champs sont remplis
    if (id_str.isEmpty() || type_event.isEmpty() || duree.isEmpty() || montant_str.isEmpty() || sponsor.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Veuillez remplir tous les champs."), QMessageBox::Cancel);
        return;
    }

    // Vérification que les champs ne contiennent pas de caractères spéciaux
    QRegularExpression regex("^[a-zA-Z0-9_]*$");
    if (!regex.match(type_event).hasMatch() || !regex.match(duree).hasMatch() || !regex.match(sponsor).hasMatch()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Les champs ne doivent pas contenir de caractères spéciaux."), QMessageBox::Cancel);
        return;
    }

    // Vérification que les champs numériques contiennent des valeurs valides
    bool id_ok, montant_ok;
    int id = id_str.toInt(&id_ok);
    int montant = montant_str.toInt(&montant_ok);
    if (!id_ok || !montant_ok) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("ID ou montant invalide. Veuillez entrer des nombres entiers."), QMessageBox::Cancel);
        return;
    }

    // Toutes les validations sont passées, procéder à la mise à jour
    evenement e(id, type_event, duree, sponsor, montant);
    bool test = e.modifier(id);

    if (test) {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Mise à jour effectuée."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                 QObject::tr("Mise à jour non effectuée."), QMessageBox::Cancel);
    }
}

void MainWindow::refreshTable()
{
    ui->tableView->setModel(Etmp.afficher());
}

void MainWindow::searchEvent(const QString &text)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Utilisez LIKE pour rechercher les événements qui contiennent le terme de recherche
    query.prepare("SELECT * FROM evenements WHERE type_event LIKE :search OR duree LIKE :search OR sponsor LIKE :search");
    query.bindValue(":search", "%" + text + "%");

    if (query.exec())
    {
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
    else
    {
        qDebug() << "Erreur lors de la recherche : " << query.lastError().text();
    }
}
void MainWindow::sortAscending()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM evenements ORDER BY montant ASC");
    ui->tableView->setModel(model);
}

void MainWindow::sortDescending()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM evenements ORDER BY montant DESC");
    ui->tableView->setModel(model);
}

void MainWindow::exportPdfEvent()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", "", "PDF files (*.pdf)");
    if (!fileName.isEmpty())
    {
        exportToPdfEvent(fileName, ui->tableView); // Utilisez votre QTableView ici
    }
}

void MainWindow::exportToPdfEvent(const QString &fileName, QTableView *tableView)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QPainter painter;
    painter.begin(&printer);

    double xscale = printer.pageRect().width() / double(tableView->width());
    double yscale = printer.pageRect().height() / double(tableView->height());
    double scale = qMin(xscale, yscale);

    painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                      printer.paperRect().y() + printer.pageRect().height() / 2);
    painter.scale(scale, scale);
    painter.translate(-tableView->width() / 2, -tableView->height() / 2);

    tableView->render(&painter);
    painter.end();
}







//EXELL




void MainWindow::exportCsv()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "events.csv", tr("CSV Files (*.csv);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8"); // Set UTF-8 encoding
    // Column headers
    out << "ID" << ";" << "TYPE_EVENT" << ";" << "DUREE" << ";" << "MONTANT" << ";" << "SPONSOR" << "\n";

    QSqlQuery query("SELECT * FROM EVENEMENTS");
    if (!query.exec()) {
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        out << query.value("ID").toInt() << ";"
            << query.value("TYPE_EVENT").toString() << ";"
            << query.value("DUREE").toString() << ";"
            << query.value("MONTANT").toInt() << ";"
            << query.value("SPONSOR").toString() << "\n";
    }
}




//
void MainWindow::on_statisticsButton_clicked()
{
    // Déplace l'affichage vers l'index 5 du stacked widget
    ui->stackedWidget->setCurrentIndex(5);

    // Prépare la requête SQL pour récupérer le montant total par type d'événement
    QSqlQuery montantQuery;
    montantQuery.prepare("SELECT type_event, SUM(montant) AS total_amount FROM evenements GROUP BY type_event");
    montantQuery.exec();

    // Crée une série de données pour le graphique en secteurs (camembert)
    QPieSeries *pieSeries = new QPieSeries();
    while (montantQuery.next())
    {
        QString eventType = montantQuery.value("type_event").toString();
        int totalAmount = montantQuery.value("total_amount").toInt();
        pieSeries->append(eventType, totalAmount);
    }

    // Crée un graphique et ajoute la série de données
    QChart *chart = new QChart();
     chart->addSeries(pieSeries);
    chart->setTitle("Répartition par Montant");

    // Crée une vue pour afficher le graphique
    QChartView *chartView = new QChartView(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    // Insère la vue du graphique à l'index 5 du stacked widget
    ui->stackedWidget->insertWidget(5, chartView);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

}




void MainWindow::on_pushButton_statistique_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    // Prépare la requête SQL pour récupérer le montant total par type d'événement
    QSqlQuery montantQuery;
    montantQuery.prepare("SELECT type_event, SUM(montant) AS total_amount FROM evenements GROUP BY type_event");
    montantQuery.exec();

    // Crée une série de données pour le graphique en secteurs (camembert)
    QPieSeries *pieSeries = new QPieSeries();
    while (montantQuery.next())
    {
        QString eventType = montantQuery.value("type_event").toString();
        int totalAmount = montantQuery.value("total_amount").toInt();
        pieSeries->append(eventType, totalAmount);
    }

    // Crée un graphique et ajoute la série de données
    QChart *chart = new QChart();
     chart->addSeries(pieSeries);
    chart->setTitle("Répartition par Montant");

    // Crée une vue pour afficher le graphique
    QChartView *chartView = new QChartView(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    // Insère la vue du graphique à l'index 5 du stacked widget
    ui->stackedWidget->insertWidget(5, chartView);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);

}


// tache materiels

void MainWindow::navigateToPage(int pageIndex)
{
    ui->stackedWidget->setCurrentIndex(pageIndex);
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QStackedWidget* stackedWidget = ui->stackedWidget;
    QWidget* page = stackedWidget->widget(6);
    QLineEdit* id = page->findChild<QLineEdit*>("id");

    if (!id) {
        qDebug() << "ID LineEdit not found on page";
        return;
    }

    QString value = ui->tableView_2->model()->data(ui->tableView_2->model()->index(index.row(), 0)).toString();
    id->setText(value);
    Connection c;
    c.closeconnection();
    QSqlQuery qry;

    qry.prepare("SELECT ID_MAT, ETAT, PRIX, ID_EMP, ID_FOURNI FROM MATERIEL where ID_MAT=:id");
    qry.bindValue(":id", value);
    if (qry.exec())
    {
        while (qry.next())
        {
            ui->ETAT->setText(qry.value(0).toString());
            ui->PRIX->setText(qry.value(1).toString());
            ui->IDEMP->setText(qry.value(3).toString());
            ui->IDFOR->setText(qry.value(4).toString());
            int numbercoloumn;
            numbercoloumn=ui->tableView_2->model()->columnCount();
            qDebug()<<numbercoloumn;
        }
    }
    else {
        qDebug() << "Query failed:" << qry.lastError().text();
    }
}
void MainWindow::on_cadd_clicked()
{
    QString etat = ui->ETAT->text();
    QString prix = ui->PRIX->text();
    QString id_emp = ui->IDEMP->text();
    QString id_fourni = ui->IDFOR->text();
    materiel Materiel(etat, prix.toFloat(), id_emp.toInt(), id_fourni.toInt());

    bool test = Materiel.ajouter_mat();
    ui->tableView_2->setModel(Materiel.afficher_mat());
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
            QObject::tr("Ajout effectue\n"
                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
            QObject::tr("Ajout non effectuer\n"
                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_2->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        qDebug() << "Selected Index Row:" << row;
        int id_mat = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 0)).toInt();
        qDebug() << "Selected Employee ID:" << id_mat;
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirm Deletion",
                                             "Are you sure you want to delete the employee with ID: " + QString::number(id_mat) + "?",
                                             QMessageBox::Yes|QMessageBox::No);

        if (confirmation == QMessageBox::Yes) {
           materiel Materiel;
           bool success = Materiel.delete_mat(id_mat);
            if(success) {
                ui->tableView_2->setModel(Materiel.afficher_mat());
                QMessageBox::information(this, "Employee Deleted", "The selected employee has been deleted.");
            } else {
                QMessageBox::warning(this, "Error", "Failed to delete employee.");
            }
        }
    } else {
        QMessageBox::warning(this, "No Employee Selected", "Please select an employee to delete.");
    }
}
void MainWindow::onUpdateButtonClicked()
{
    QModelIndexList selectedIndexes = ui->tableView_2->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Row Selected", "Please select a material to update.");
        return;
    }
    int row = selectedIndexes.first().row();
    QString etat = ui->tableView_2->model()->index(row, 1).data().toString();
    QString prix = ui->tableView_2->model()->index(row, 2).data().toString();
    QString id_emp = ui->tableView_2->model()->index(row, 3).data().toString();
    QString id_fourni = ui->tableView_2->model()->index(row, 4).data().toString();
    ui->ETAT->setText(etat);
    ui->PRIX->setText(prix);
    ui->IDEMP->setText(id_emp);
    ui->IDFOR->setText(id_fourni);
    navigateToPage(1);
}
void MainWindow::onMUpdateButtonClicked()
{
    QString etat = ui->ETAT->text();
    QString prix = ui->PRIX->text();
    QString id_emp = ui->IDEMP->text();
    QString id_fourni = ui->IDFOR->text();

    QModelIndexList selectedIndexes = ui->tableView_2->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Row Selected", "Please select a material to update.");
        return;
    }

    int row = selectedIndexes.first().row();
    int id_mat = ui->tableView_2->model()->index(row, 0).data().toInt();
 materiel Materiel;
    bool success =  Materiel.updateMaterial(id_mat, etat, prix.toInt(), id_emp.toInt(), id_fourni.toInt());
    if (success) {
        QMessageBox::information(this, "Update Successful", "Material information updated successfully.");
        navigateToPage(0);
        ui->tableView_2->setModel(Materiel.afficher_mat());
        ui->ETAT->clear();
        ui->PRIX->clear();
        ui->IDEMP->clear();
        ui->IDFOR->clear();
    } else {
        QMessageBox::warning(this, "Update Failed", "Failed to update material information.");
    }
}

void MainWindow::exportPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", "", "PDF files (.pdf)");
    if (!fileName.isEmpty())
    {
        exportToPdf(fileName, ui->tableView_2); // Utilisez votre QtableView_2 ici
    }
}

void MainWindow::exportToPdf(const QString &fileName, QTableView *tableView_2)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QPainter painter;
    painter.begin(&printer);

    double xscale = printer.pageRect().width() / double(tableView_2->width());
    double yscale = printer.pageRect().height() / double(tableView_2->height());
    double scale = qMin(xscale, yscale);

    painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                      printer.paperRect().y() + printer.pageRect().height() / 2);
    painter.scale(scale, scale);
    painter.translate(-tableView_2->width() / 2, -tableView_2->height() / 2);

    tableView_2->render(&painter);
    painter.end();
}







void MainWindow::on_goevent_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}
