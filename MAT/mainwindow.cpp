#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materiel.h"
#include "connection.h"
#include <QDebug>
#include <QStackedWidget>
#include <QMap>
#include <QFile>
#include <QString>
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QRegularExpression>
#include<QSqlQueryModel>
#include <QTableView>
#include <QStandardItemModel>
#include <QTextDocument>
#include <QTextStream>
#include <QAbstractItemModel>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->tableView, &QTableView::activated, this, &MainWindow::on_tableView_activated);
  connect(ui->delete_2, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
  connect(ui->update, &QPushButton::clicked, this, &MainWindow::onUpdateButtonClicked);
  connect(ui->cupdate, &QPushButton::clicked, this, &MainWindow::onMUpdateButtonClicked);
  connect(ui->cadd, &QPushButton::clicked, this, [this]() { navigateToPage(0); });
  connect(ui->cupdate, &QPushButton::clicked, this, [this]() { navigateToPage(0); });
  connect(ui->ListMat, &QPushButton::clicked, this, [this]() { navigateToPage(0); });
  connect(ui->AddMat, &QPushButton::clicked, this, [this]() { navigateToPage(1); });
  connect(ui->Stat, &QPushButton::clicked, this, [this]() { navigateToPage(2); });
  connect(ui->pdf, &QPushButton::clicked, this, &MainWindow::exportPdf);
  connect(ui->sort, &QPushButton::clicked, this, &MainWindow::on_filterButton_clicked);
  connect(ui->searchbar, &QLineEdit::textChanged, this, &MainWindow::searchMat);

  ui->tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed);
  QStackedWidget* stackedWidget = ui->stackedWidget;
  QWidget* page = stackedWidget->widget(0);
  QTableView* tableView = page->findChild<QTableView*>("tableView");
  materiel m;
  Connection c;
  if(c.createconnect())
  {
      tableView->setModel(m.afficher_mat());
      QMessageBox::information(nullptr, QObject::tr("database is open"),
                               QObject::tr("connection successful.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
  }
  else
  {
      QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                            QObject::tr("connection failed.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
  }

}


MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::navigateToPage(int pageIndex)
{
    ui->stackedWidget->setCurrentIndex(pageIndex);
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QStackedWidget* stackedWidget = ui->stackedWidget;
    QWidget* page = stackedWidget->widget(0);
    QLineEdit* id = page->findChild<QLineEdit*>("id");

    if (!id) {
        qDebug() << "ID LineEdit not found on page";
        return;
    }

    QString value = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
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
            numbercoloumn=ui->tableView->model()->columnCount();
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
    ui->tableView->setModel(Materiel.afficher_mat());
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
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        qDebug() << "Selected Index Row:" << row;
        int id_mat = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();
        qDebug() << "Selected Employee ID:" << id_mat;
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirm Deletion",
                                             "Are you sure you want to delete the employee with ID: " + QString::number(id_mat) + "?",
                                             QMessageBox::Yes|QMessageBox::No);

        if (confirmation == QMessageBox::Yes) {
           materiel Materiel;
           bool success = Materiel.delete_mat(id_mat);
            if(success) {
                ui->tableView->setModel(Materiel.afficher_mat());
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
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Row Selected", "Please select a material to update.");
        return;
    }
    int row = selectedIndexes.first().row();
    QString etat = ui->tableView->model()->index(row, 1).data().toString();
    QString prix = ui->tableView->model()->index(row, 2).data().toString();
    QString id_emp = ui->tableView->model()->index(row, 3).data().toString();
    QString id_fourni = ui->tableView->model()->index(row, 4).data().toString();
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

    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Row Selected", "Please select a material to update.");
        return;
    }

    int row = selectedIndexes.first().row();
    int id_mat = ui->tableView->model()->index(row, 0).data().toInt();
 materiel Materiel;
    bool success =  Materiel.updateMaterial(id_mat, etat, prix.toInt(), id_emp.toInt(), id_fourni.toInt());
    if (success) {
        QMessageBox::information(this, "Update Successful", "Material information updated successfully.");
        navigateToPage(0);
        ui->tableView->setModel(Materiel.afficher_mat());
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
        exportToPdf(fileName, ui->tableView); // Utilisez votre QTableView ici
    }
}

void MainWindow::exportToPdf(const QString &fileName, QTableView*tableView)
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



void MainWindow::on_filterButton_clicked()
{
    QString filterOption = ui->comboBox_2->currentText();
    applyFilter(filterOption);
}

void MainWindow::applyFilter(const QString &filterOption)
{
    QString query;

    if (filterOption == "None") {
        query = "SELECT ID_MAT, ETAT, PRIX, ID_EMP, ID_FOURNI FROM MATERIEL";
    } else if (filterOption == "ID_MAT ASC") {
        query = "SELECT ID_MAT, ETAT, PRIX, ID_EMP, ID_FOURNI FROM MATERIEL ORDER BY ID_MAT ASC";
    } else if (filterOption == "ID_MAT DESC") {
        query = "SELECT ID_MAT, ETAT, PRIX, ID_EMP, ID_FOURNI FROM MATERIEL ORDER BY ID_MAT DESC";
    } else if (filterOption == "ETAT ASC") {
        query = "SELECT ID_MAT, ETAT, PRIX, ID_EMP, ID_FOURNI FROM MATERIEL ORDER BY ETAT ASC";
    } else if (filterOption == "ETAT DESC") {
        query = "SELECT ID_MAT, ETAT, PRIX, ID_EMP, ID_FOURNI FROM MATERIEL ORDER BY ETAT DESC";
    } else {
        // Handle other filter options or provide a default query
        // Example: query = "SELECT * FROM MATERIEL";
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->update();
}


void MainWindow::searchMat(const QString &text)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM MATERIEL WHERE ID_MAT LIKE :search OR ETAT LIKE :search OR PRIX LIKE :search OR ID_EMP LIKE :search OR ID_FOURNI LIKE :search ");
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
