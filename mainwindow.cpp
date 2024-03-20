#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
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
#include <QtCharts>
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
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentPageIndex = 0;
    //side bar bouttons connection
    connect(ui->employe_1, &QPushButton::clicked, this, [this]() { On_Sidebar_Button_Clicked(1); });
    connect(ui->employe_2, &QPushButton::clicked, this, [this]() { On_Sidebar_Button_Clicked(1); });
    connect(ui->event_1, &QPushButton::clicked, this, [this]() { On_Sidebar_Button_Clicked(2); });
    connect(ui->event_2, &QPushButton::clicked, this, [this]() { On_Sidebar_Button_Clicked(2); });
    connect(ui->supplier_1, &QPushButton::clicked, this, [this]() { On_Sidebar_Button_Clicked(3); });
    connect(ui->supplier_2, &QPushButton::clicked, this, [this]() { On_Sidebar_Button_Clicked(3); });
    connect(ui->material_1, &QPushButton::clicked, this, [this]() { On_Sidebar_Button_Clicked(4); });
    connect(ui->material_2, &QPushButton::clicked, this, [this]() { On_Sidebar_Button_Clicked(4); });
    connect(ui->member_1, &QPushButton::clicked, this, [this]() { On_Sidebar_Button_Clicked(5); });
    connect(ui->member_2, &QPushButton::clicked, this, [this]() { On_Sidebar_Button_Clicked(5); });
    // top bar bouttons connection
    connect(ui->list, &QPushButton::clicked, this, [this]() { On_TopBar_Button_Clicked(1); });
    connect(ui->add, &QPushButton::clicked, this, [this]() { On_TopBar_Button_Clicked(2); });
    connect(ui->stat, &QPushButton::clicked, this, [this]() { On_TopBar_Button_Clicked(3); });
    // employe bouttons connection
    connect(ui->Cadd_Employe, &QPushButton::clicked, this, &MainWindow::Add_Employe);
    connect(ui->Cupdate_Employe, &QPushButton::clicked, this, &MainWindow::On_CUpdate_Employe_Button_Clicked_On_Form);
    connect(ui->Update_Emp, &QPushButton::clicked, this, &MainWindow::On_Update_Employe_Button_Clicked_On_Table);
    connect(ui->Delete_Emp, &QPushButton::clicked, this, &MainWindow::On_Delete_Employe_Button_clicked);
    connect(ui->TableView_Emp, &QTableView::activated, this, &MainWindow::On_Table_View_Employe_activated);
    //display only one sidebar
    ui->icon_name->show();
    ui->icon->hide();
    //connection with database
    Employee e;
    Connection c;
    if(c.createconnect())
    {
        ui->TableView_Emp->setModel(e.Afficher_Employe());
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
//end connection with databse
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Navigate_To_Page(int pageIndex)
{
    ui->stackedWidget->setCurrentIndex(pageIndex);
}
void MainWindow::On_Sidebar_Button_Clicked(int sidebarIndex)
{
    currentSidebarIndex = sidebarIndex;
    Navigate_To_Page(sidebarIndex);
}

void MainWindow::On_TopBar_Button_Clicked(int topBarIndex)
{
    int pageIndex = 0;
    switch (currentSidebarIndex) {
        case 1:
            if (topBarIndex == 1) pageIndex = 1;
            else if (topBarIndex == 2){
                pageIndex = 6;
                While_Going_To_Employe_Form();
            }
            else if (topBarIndex == 3) pageIndex = 11;
            break;
        case 2:
            if (topBarIndex == 1) pageIndex = 2;
            else if (topBarIndex == 2) pageIndex = 7;
            else if (topBarIndex == 3) pageIndex = 12;
            break;
        case 3:
            if (topBarIndex == 1) pageIndex = 3;
            else if (topBarIndex == 2) pageIndex = 8;
            else if (topBarIndex == 3) pageIndex = 13;
            break;
        case 4:
            if (topBarIndex == 1) pageIndex = 4;
            else if (topBarIndex == 2) pageIndex = 9;
            else if (topBarIndex == 3) pageIndex = 14;
            break;
        case 5:
            if (topBarIndex == 1) pageIndex = 5;
            else if (topBarIndex == 2) pageIndex = 10;
            else if (topBarIndex == 3) pageIndex = 15;
            break;
        default:
            break;
    }
    Navigate_To_Page(pageIndex);
}


//TACHE EMPLOYE
void MainWindow::Add_Employe()
{
    QString nom = ui->NOM->text();
    QString prenom = ui->PRENOM->text();
    QString email = ui->EMAIL->text();
    QString password = ui->PASSWORD->text();
    QString telephone = ui->TELEPHONE->text();
    QString adress = ui->ADRESSE->text();
    QString salaire = ui->SALAIRE->text();
    QString sexe = ui->SEXE->currentText();
    QString role = ui->ROLE->currentText();

    if (!Validate_Employe_Input(nom, prenom, email, password, telephone, adress, salaire)) {
        return;
    }
    Employee e(nom, prenom, email, password, telephone, salaire , adress , sexe , role);
    bool test = e.Ajouter_Employe();
    if (test)
    {
        ui->TableView_Emp->setModel(e.Afficher_Employe());
        QMessageBox::information(nullptr, QObject::tr("Employee Added"),
                                 QObject::tr("The employee has been added successfully."),
                                 QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::warning(nullptr, QObject::tr("Error"),
                             QObject::tr("Failed to add employee."),
                             QMessageBox::Cancel);
    }
    ui->NOM->clear();
    ui->PRENOM->clear();
    ui->EMAIL->clear();
    ui->PASSWORD->clear();
    ui->ADRESSE->clear();
    ui->SALAIRE->clear();
    ui->TELEPHONE->clear();
    ui->SEXE->setCurrentIndex(0);
    ui->ROLE->setCurrentIndex(0);
}


void MainWindow::On_Delete_Employe_Button_clicked()
{
    QModelIndexList selectedIndexes = ui->TableView_Emp->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        qDebug() << "Selected Index Row:" << row;
        int ID_EMP = ui->TableView_Emp->model()->data(ui->TableView_Emp->model()->index(row, 0)).toInt();
        qDebug() << "Selected Employee ID:" << ID_EMP;
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirm Deletion",
                                             "Are you sure you want to delete the employee with ID: " + QString::number(ID_EMP) + "?",
                                             QMessageBox::Yes|QMessageBox::No);

        if (confirmation == QMessageBox::Yes) {
            Employee employee;
            bool success = employee.Delete_Employe(ID_EMP);
            if(success) {
                ui->TableView_Emp->setModel(employee.Afficher_Employe());
                QMessageBox::information(this, "Employee Deleted", "The selected employee has been deleted.");
            } else {
                QMessageBox::warning(this, "Error", "Failed to delete employee.");
            }
        }
    } else {
        QMessageBox::warning(this, "No Employee Selected", "Please select an employee to delete.");
    }
}


bool MainWindow::Validate_Employe_Input(const QString &nom, const QString &prenom, const QString &email,const QString &password,const QString &telephone, const QString &adress, const QString &salaire)
{
    if (nom.isEmpty() || prenom.isEmpty() || adress.isEmpty() || telephone.isEmpty() || salaire.isEmpty() || email.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Missing Information", "Please fill in all required fields.");
            return false;
        }
    QRegularExpression letterRegex("[a-zA-Z]");
    if (adress.length() - adress.count(QRegularExpression("\\d")) < 5 || !adress.contains(letterRegex)) {
        QMessageBox::warning(this, "Invalid Input", "Address must contain at least five letters.");
        return false;
    }
            QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
        if (!emailRegex.match(email).hasMatch()) {
            QMessageBox::warning(this, "Invalid Email", "Please enter a valid email address.");
            return false;
        }
            QRegularExpression passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
        if (!passwordRegex.match(password).hasMatch()) {
            QMessageBox::warning(this, "Invalid Password", "Password must contain at least one uppercase letter, one lowercase letter, one number, one special character, and be at least 8 characters long.");
            return false;
        }
    if (telephone.length() < 8) {
           QMessageBox::warning(this, "Invalid Input", "Telephone number must be at least 8 digits long.");
           return false;
       }
          if (salaire.length() < 4) {
           QMessageBox::warning(this, "Invalid Input", "Salaire must be at least 4 characters long.");
           return false;
       }
    if (nom.contains(QRegularExpression("\\d"))) {
        QMessageBox::warning(this, "Invalid Input", "Nom cannot contain numeric characters.");
        return false;
    }
    if (prenom.contains(QRegularExpression("\\d"))) {
        QMessageBox::warning(this, "Invalid Input", "Prenom cannot contain numeric characters.");
        return false;
    }
    QRegularExpression specialChars("[!@#$%^&*(),.?\":{}|<>]");
    if (nom.contains(specialChars)) {
        QMessageBox::warning(this, "Invalid Input", "Nom cannot contain special characters.");
        return false;
    }
    if (prenom.contains(specialChars)) {
        QMessageBox::warning(this, "Invalid Input", "Prenom cannot contain special characters.");
        return false;
    }
    if (adress.contains(specialChars)) {
        QMessageBox::warning(this, "Invalid Input", "Address cannot contain special characters.");
        return false;
    }
    bool ok;
    int tel = telephone.toInt(&ok);
    if (!ok || tel <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Telephone must be a positive numeric value.");
        return false;
    }
    int sal = salaire.toInt(&ok);
    if (!ok || sal <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Salaire must be a positive numeric value.");
        return false;
    }
    return true;
}
void MainWindow::While_Going_To_Employe_Form() {
        ui->Cupdate_Employe->setVisible(false);
        ui->Cadd_Employe->setVisible(true);
    }
void MainWindow::On_Update_Employe_Button_Clicked_On_Table()
{
    ui->Cadd_Employe->setVisible(false);
    ui->Cupdate_Employe->setVisible(true);
    QModelIndexList selectedIndexes = ui->TableView_Emp->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Row Selected", "Please select an employee to update.");
        return;
    }
    int row = selectedIndexes.first().row();
    QString id_emp = ui->TableView_Emp->model()->index(row, 0).data().toString();
    QString nom = ui->TableView_Emp->model()->index(row, 1).data().toString();
    QString prenom = ui->TableView_Emp->model()->index(row, 2).data().toString();
    QString email = ui->TableView_Emp->model()->index(row, 3).data().toString();
    QString password = ui->TableView_Emp->model()->index(row, 4).data().toString();
    QString telephone = ui->TableView_Emp->model()->index(row, 5).data().toString();
    QString salaire = ui->TableView_Emp->model()->index(row, 6).data().toString();
    QString adresse = ui->TableView_Emp->model()->index(row, 7).data().toString();
    QString sexe = ui->TableView_Emp->model()->index(row, 8).data().toString();
    QString role = ui->TableView_Emp->model()->index(row, 9).data().toString();

    ui->NOM->setText(nom);
    ui->PRENOM->setText(prenom);
    ui->EMAIL->setText(email);
    ui->PASSWORD->setText(password);
    ui->TELEPHONE->setText(telephone);
    ui->ADRESSE->setText(adresse);
    ui->SALAIRE->setText(salaire);
    ui->SEXE->setCurrentText(sexe);
    ui->ROLE->setCurrentText(role);

    Navigate_To_Page(6);
}

void MainWindow::On_CUpdate_Employe_Button_Clicked_On_Form()
{
    Employee e;
    QString nom = ui->NOM->text();
    QString prenom = ui->PRENOM->text();
    QString email = ui->EMAIL->text();
    QString password = ui->PASSWORD->text();
    QString telephone = ui->TELEPHONE->text();
    QString salaire = ui->SALAIRE->text();
    QString adress = ui->ADRESSE->text();
    QString sexe = ui->SEXE->currentText();
    QString role = ui->ROLE->currentText();
    if (!Validate_Employe_Input(nom, prenom, email, password, telephone, adress, salaire)) {
        return;
    }
    QModelIndexList selectedIndexes = ui->TableView_Emp->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Row Selected", "Please select an employee to update.");
        return;
    }
    int row = selectedIndexes.first().row();
    int id = ui->TableView_Emp->model()->index(row, 0).data().toInt();
    bool success = e.Update_Employe(id, nom, prenom, email, password, sexe, telephone, adress, salaire, role);
    if (success) {
        QMessageBox::information(this, "Update Successful", "Employee information updated successfully.");
        ui->TableView_Emp->setModel(e.Afficher_Employe());
    } else {
        QMessageBox::warning(this, "Update Failed", "Failed to update employee information.");
    }
    ui->NOM->clear();
    ui->PRENOM->clear();
    ui->EMAIL->clear();
    ui->PASSWORD->clear();
    ui->TELEPHONE->clear();
    ui->ADRESSE->clear();
    ui->SALAIRE->clear();
    ui->SEXE->setCurrentIndex(0);
    ui->ROLE->setCurrentIndex(0);
}

void MainWindow::On_Table_View_Employe_activated(const QModelIndex &index)
{
    QStackedWidget* stackedWidget = ui->stackedWidget;
    QWidget* page = stackedWidget->widget(3);
    QLineEdit* id = page->findChild<QLineEdit*>("id");

    if (!id) {
        qDebug() << "ID LineEdit not found on page";
        return;
    }

    QString value = ui->TableView_Emp->model()->data(ui->TableView_Emp->model()->index(index.row(), 0)).toString();
    id->setText(value);
    {
        QSqlQuery qry;
        qry.prepare("SELECT NOM, PRENOM, EMAIL, PASSWORD, SEXE, TELEPHONE, ADRESS, SALAIRE, ROLE FROM EMPLOYEE WHERE ID_EMP=:id");
        qry.bindValue(":id", value);

        if (qry.exec())
        {
            while (qry.next())
            {
                ui->NOM->setText(qry.value(0).toString());
                ui->PRENOM->setText(qry.value(1).toString());
                ui->EMAIL->setText(qry.value(2).toString());
                ui->PASSWORD->setText(qry.value(3).toString());
                ui->SEXE->setCurrentText(qry.value(4).toString());
                ui->TELEPHONE->setText(qry.value(5).toString());
                ui->ADRESSE->setText(qry.value(6).toString());
                ui->SALAIRE->setText(qry.value(7).toString());
                ui->ROLE->setCurrentText(qry.value(8).toString());
            }
        }
        else {
            qDebug() << "Query failed:" << qry.lastError().text();
        }
    }
}
//fin tache employe
