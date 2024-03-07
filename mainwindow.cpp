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


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher()); // Passez la connexion à la méthode afficher()

    connect(ui->pushButton_9,&QPushButton::clicked,this,&MainWindow::clicker_list);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&MainWindow::clicker_list1);
    connect(ui->pushButton_10,&QPushButton::clicked,this,&MainWindow::clicker_list1);
    connect(ui->pushButton_10,&QPushButton::clicked,this,&MainWindow::clicker_list1);
    connect(ui->pushButton_11,&QPushButton::clicked,this,&MainWindow::clicker_list3);
    //connect(ui->pushButton_delete,&QPushButton::clicked,this,&MainWindow::clicker_delete);
    connect(ui->pushButton_add,&QPushButton::clicked,this,&MainWindow::clicker_add);
    connect(ui->pushButton_modifier,&QPushButton::clicked,this,&MainWindow::clicker_update);
    connect(ui->pushButton_statistique,&QPushButton::clicked,this,&MainWindow::clicker_statistics);
    connect(ui->delete_2, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
    connect(ui->word, &QPushButton::clicked, this, [this]() {
            QString fileName = QFileDialog::getSaveFileName(this, "Save Word Document", QDir::currentPath(), "Word Files (*.docx)");
            if (!fileName.isEmpty()) {
                exportToWord(fileName);
            }
        });




    connect(ui->pushButton_refresh, &QPushButton::clicked, this, &MainWindow::refreshTable);
    connect(ui->lineEdit_search, &QLineEdit::textChanged, this, &MainWindow::searchEvent);
    connect(ui->pushButton_asc, &QPushButton::clicked, this, &MainWindow::sortAscending);
    connect(ui->pushButton_desc, &QPushButton::clicked, this, &MainWindow::sortDescending);
    connect(ui->exportPdfButton, &QPushButton::clicked, this, &MainWindow::exportPdf);



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
void MainWindow::on_deleteButton_clicked()
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

void MainWindow::exportPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", "", "PDF files (*.pdf)");
    if (!fileName.isEmpty())
    {
        exportToPdf(fileName, ui->tableView); // Utilisez votre QTableView ici
    }
}

void MainWindow::exportToPdf(const QString &fileName, QTableView *tableView)
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



void MainWindow::clicker_statistics()
{
    ui->stackedWidget->setCurrentIndex(1);


}

QList<int> evenement::getMontants() {
    QList<int> montants;
    QSqlQuery query;
    query.prepare("SELECT montant FROM evenements");
    if (query.exec()) {
        while (query.next()) {
            montants.append(query.value(0).toInt());
        }
    } else {
        qDebug() << "Erreur lors de la récupération des montants : " << query.lastError().text();
    }
    return montants;
}

void MainWindow::clicker_statistics1()
{
    // Récupérer les montants depuis la base de données
    evenement E;
    QList<int> montants = E.getMontants();

    // Créer le jeu de données pour le graphique
    QPieSeries *series = new QPieSeries();
    foreach (int montant, montants) {
        series->append(QString::number(montant), montant);
    }

    // Créer le graphique à secteurs
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques de montant");

    // Créer et afficher la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(400, 300); // Définir la taille de la vue du graphique

    // Afficher le graphique dans le widget de votre interface utilisateur
    ui->statisticsWidget->layout()->addWidget(chartView);
}
void MainWindow::exportToWord(const QString &fileName)
{
    QTextDocument doc;
    QAbstractItemModel * model = ui->tableView->model();
    int rows = model->rowCount();
    int cols = model->columnCount();
    QString tableData;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QModelIndex index = model->index(row, col);
            QString cellData = model->data(index).toString();
            tableData.append(cellData);
            if (col < cols - 1)
                tableData.append("\t");
            else
                tableData.append("\n");
        }
    }
    doc.setPlainText(tableData);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << doc.toPlainText();
        file.close();
    } else {
        qDebug() << "Error: Could not open file for writing";
    }
}



