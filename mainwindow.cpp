#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include "connection.h"
#include "evenement.h"
#include "materiel.h"
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
#include <QPieSeries>
#include <QImage>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentPageIndex = 0;
    Navigate_To_Page(0);
    //side bar bouttons connection
    connect(ui->employe_1, &QPushButton::clicked, this, [this]()
    {
        On_Sidebar_Button_Clicked(1);
    });
    connect(ui->employe_2, &QPushButton::clicked, this, [this]()
    {
        On_Sidebar_Button_Clicked(1);
    });
    connect(ui->event_1, &QPushButton::clicked, this, [this]()
    {
        On_Sidebar_Button_Clicked(2);
    });
    connect(ui->event_2, &QPushButton::clicked, this, [this]()
    {
        On_Sidebar_Button_Clicked(2);
    });
    connect(ui->supplier_1, &QPushButton::clicked, this, [this]()
    {
        On_Sidebar_Button_Clicked(3);
    });
    connect(ui->supplier_2, &QPushButton::clicked, this, [this]()
    {
        On_Sidebar_Button_Clicked(3);
    });
    connect(ui->material_1, &QPushButton::clicked, this, [this]()
    {
        On_Sidebar_Button_Clicked(4);
    });
    connect(ui->material_2, &QPushButton::clicked, this, [this]()
    {
        On_Sidebar_Button_Clicked(4);
    });
    connect(ui->member_1, &QPushButton::clicked, this, [this]()
    {
        On_Sidebar_Button_Clicked(5);
    });
    connect(ui->member_2, &QPushButton::clicked, this, [this]()
    {
        On_Sidebar_Button_Clicked(5);
    });


    // top bar bouttons connection
    connect(ui->list, &QPushButton::clicked, this, [this]()
    {
        On_TopBar_Button_Clicked(1);
    });
    connect(ui->add, &QPushButton::clicked, this, [this]()
    {
        On_TopBar_Button_Clicked(2);
    });
    connect(ui->stat, &QPushButton::clicked, this, [this]()
    {
        On_TopBar_Button_Clicked(3);
    });


    // employe bouttons connection
    connect(ui->Cadd_Employe, &QPushButton::clicked, this, &MainWindow::Add_Employe);
    connect(ui->Cupdate_Employe, &QPushButton::clicked, this, &MainWindow::On_CUpdate_Employe_Button_Clicked_On_Form);
    connect(ui->Update_Emp, &QPushButton::clicked, this, &MainWindow::On_Update_Employe_Button_Clicked_On_Table);
    connect(ui->Delete_Emp, &QPushButton::clicked, this, &MainWindow::On_Delete_Employe_Button_clicked);
    connect(ui->TableView_Emp, &QTableView::activated, this, &MainWindow::On_Table_View_Employe_activated);
    connect(ui->PDF_Emp, &QPushButton::clicked, this, &MainWindow::On_Export_Employe_Boutton_To_PDF_Clicked);
    connect(ui->Searchbar_Emp, &QLineEdit::textChanged, this, &MainWindow::Search_Employe);
    connect(ui->Text_Emp, &QPushButton::clicked, this, [this]()
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Text Document", QDir::currentPath(), "Text Files (*.txt)");
        if (!fileName.isEmpty())
        {
            Export_Employe_To_TEXT(fileName);
        }
    });
    connect(ui->Sort_Emp, &QPushButton::clicked, this, [this]()
    {
        QString filterOption = ui->ComboBox_Emp->currentText();
        Apply_Employe_Filter(filterOption);
    });


    //event button connection
    connect(ui->caddevent, &QPushButton::clicked, this, &MainWindow::On_Cadd_Event_Clicked);
    connect(ui->deleteEvent, &QPushButton::clicked, this, &MainWindow::On_Delete_Button_Event_Clicked);
    connect(ui->searchevent, &QLineEdit::textChanged, this, &MainWindow::Search_Event);
    connect(ui->exportPdfEvent, &QPushButton::clicked, this, &MainWindow::Export_PDF_Event);
    connect(ui->Cupdate_Event, &QPushButton::clicked, this, &MainWindow::On_CUpdate_Event_Button_Clicked_On_Form);
    connect(ui->Update_event, &QPushButton::clicked, this, &MainWindow::On_Update_Event_Button_Clicked_On_Table);
    connect(ui->Sort_Event, &QPushButton::clicked, this, [this]()
    {
        QString filterOption = ui->ComboBox_Event->currentText();
        Apply_event_Filter(filterOption);
    });

    // materiel boutton connection
    connect(ui->Delete_Mat, &QPushButton::clicked, this, &MainWindow::On_Delete_Button_Mat_Clicked);
    connect(ui->Update_Mat, &QPushButton::clicked, this, &MainWindow::On_Update_Button_Mat_Clicked);
    connect(ui->Cupdate_Mat, &QPushButton::clicked, this, &MainWindow::On_Mat_Update_Button_Clicked);
    connect(ui->Cadd_Mat, &QPushButton::clicked, this, &MainWindow::On_Cadd_Boutton_Mat_Clicked);
    connect(ui->PDF_Mat, &QPushButton::clicked, this, &MainWindow::Export_Mat_Pdf);
    connect(ui->Sort_Mat, &QPushButton::clicked, this, &MainWindow::On_Filter_Button_Mat_Clicked);
    connect(ui->SearchBar_Mat, &QLineEdit::textChanged, this, &MainWindow::Search_Mat);


    //display only one sidebar
    ui->icon_name->show();
    ui->icon->hide();


    //connection with database
    Connection c;
   // declaration of work
    Employee e;
    evenement e1;
    materiel m;
    //begin connection with database and show tables
    if(c.createconnect())
    {
        ui->TableView_Emp->setModel(e.Afficher_Employe());
        ui->table_event->setModel(e1.afficherevenement());
        ui->TableView_Mat->setModel(m.afficher_mat());



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
    switch (currentSidebarIndex)
    {
    case 1:
        if (topBarIndex == 1) pageIndex = 1;
        else if (topBarIndex == 2)
        {
            pageIndex = 6;
            While_Going_To_Employe_Form();
        }
        else if (topBarIndex == 3)
        {
            pageIndex = 11;
            Go_And_Refresh_Employe_Statistics();
        }
        break;
    case 2:
        if (topBarIndex == 1) pageIndex = 2;

        else if (topBarIndex == 2)
        {
            pageIndex = 7;
            While_Going_To_Event_Form();
        }
        else if (topBarIndex == 3)
        {

            pageIndex = 12;
            On_Event_Stat_Clicked();
        }

        break;
    case 3:
        if (topBarIndex == 1) pageIndex = 3;
        else if (topBarIndex == 2) pageIndex = 8;
        else if (topBarIndex == 3) pageIndex = 13;
        break;
    case 4:
        if (topBarIndex == 1) pageIndex = 4;
        else if (topBarIndex == 2) {
            pageIndex = 9;
            While_Going_To_Mat_Form();
        }
        else if (topBarIndex == 3) {
            pageIndex = 14;
            On_Stat_Mat_Clicked();
        }
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
//beginning of employee crud
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

    if (!Validate_Employe_Input_Add(nom, prenom, email, password, telephone, adress, salaire))
    {
        return;
    }
    Employee e(nom, prenom, email, password, telephone, salaire, adress, sexe, role);
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
    if (!selectedIndexes.isEmpty())
    {
        int row = selectedIndexes.first().row();
        int ID_EMP = ui->TableView_Emp->model()->data(ui->TableView_Emp->model()->index(row, 0)).toInt();
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirm Deletion",
                                             "Are you sure you want to delete the employee with ID: " + QString::number(ID_EMP) + "?",
                                             QMessageBox::Yes|QMessageBox::No);

        if (confirmation == QMessageBox::Yes)
        {
            Employee employee;
            bool success = employee.Delete_Employe(ID_EMP);
            if(success)
            {
                ui->TableView_Emp->setModel(employee.Afficher_Employe());
                QMessageBox::information(this, "Employee Deleted", "The selected employee has been deleted.");
            }
            else
            {
                QMessageBox::warning(this, "Error", "Failed to delete employee.");
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "No Employee Selected", "Please select an employee to delete.");
    }
}


bool MainWindow::Validate_Employe_Input_Add(const QString &nom, const QString &prenom, const QString &email, const QString &password, const QString &telephone, const QString &adress, const QString &salaire) {
    QSqlQuery emailQuery;
    emailQuery.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE EMAIL = ?");
    emailQuery.addBindValue(email);
    if (!emailQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Error occurred while checking email existence.");
        return false;
    }
    emailQuery.next();
    int emailCount = emailQuery.value(0).toInt();
    if (emailCount > 0) {
        QMessageBox::warning(this, "Invalid Input", "An employee with this email already exists.");
        return false;
    }

    QSqlQuery phoneQuery;
    phoneQuery.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE TELEPHONE = ?");
    phoneQuery.addBindValue(telephone);
    if (!phoneQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Error occurred while checking phone number existence.");
        return false;
    }
    phoneQuery.next();
    int phoneCount = phoneQuery.value(0).toInt();
    if (phoneCount > 0) {
        QMessageBox::warning(this, "Invalid Input", "An employee with this phone number already exists.");
        return false;
    }

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

    if (nom.contains(QRegularExpression("\\d")) || prenom.contains(QRegularExpression("\\d")) || adress.contains(QRegularExpression("[!@#$%^&*(),.?\":{}|<>]"))) {
        QMessageBox::warning(this, "Invalid Input", "Nom, Prenom, and Address cannot contain numeric characters or special characters.");
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
bool MainWindow::Validate_Employe_Input_Update(const QString &nom, const QString &prenom, const QString &email, const QString &password, const QString &telephone, const QString &adress, const QString &salaire) {
    QSqlQuery emailQuery;
    emailQuery.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE EMAIL = ?");
    emailQuery.addBindValue(email);
    if (!emailQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Error occurred while checking email existence.");
        return false;
    }
    emailQuery.next();
    int emailCount = emailQuery.value(0).toInt();
    if (emailCount > 1) {
        QMessageBox::warning(this, "Invalid Input", "An employee with this email already exists.");
        return false;
    }

    QSqlQuery phoneQuery;
    phoneQuery.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE TELEPHONE = ?");
    phoneQuery.addBindValue(telephone);
    if (!phoneQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Error occurred while checking phone number existence.");
        return false;
    }
    phoneQuery.next();
    int phoneCount = phoneQuery.value(0).toInt();
    if (phoneCount > 1) {
        QMessageBox::warning(this, "Invalid Input", "An employee with this phone number already exists.");
        return false;
    }

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

    if (nom.contains(QRegularExpression("\\d")) || prenom.contains(QRegularExpression("\\d")) || adress.contains(QRegularExpression("[!@#$%^&*(),.?\":{}|<>]"))) {
        QMessageBox::warning(this, "Invalid Input", "Nom, Prenom, and Address cannot contain numeric characters or special characters.");
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




void MainWindow::While_Going_To_Employe_Form()
{
    ui->NOM->clear();
    ui->PRENOM->clear();
    ui->EMAIL->clear();
    ui->PASSWORD->clear();
    ui->TELEPHONE->clear();
    ui->ADRESSE->clear();
    ui->SALAIRE->clear();
    ui->SEXE->setCurrentIndex(0);
    ui->ROLE->setCurrentIndex(0);
    ui->Cupdate_Employe->setVisible(false);
    ui->Cadd_Employe->setVisible(true);
}
void MainWindow::On_Update_Employe_Button_Clicked_On_Table()
{
    ui->Cadd_Employe->setVisible(false);
    ui->Cupdate_Employe->setVisible(true);
    QModelIndexList selectedIndexes = ui->TableView_Emp->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty())
    {
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
    if (!Validate_Employe_Input_Update(nom, prenom, email, password, telephone, adress, salaire))
    {
        return;
    }
    QModelIndexList selectedIndexes = ui->TableView_Emp->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "No Row Selected", "Please select an employee to update.");
        return;
    }
    int row = selectedIndexes.first().row();
    int id = ui->TableView_Emp->model()->index(row, 0).data().toInt();
    bool success = e.Update_Employe(id, nom, prenom, email, password, sexe, telephone, adress, salaire, role);
    if (success)
    {
        QMessageBox::information(this, "Update Successful", "Employee information updated successfully.");
        ui->TableView_Emp->setModel(e.Afficher_Employe());
    }
    else
    {
        QMessageBox::warning(this, "Update Failed", "Failed to update employee information.");
    }
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::On_Table_View_Employe_activated(const QModelIndex &index)
{
    QStackedWidget* stackedWidget = ui->stackedWidget;
    QWidget* page = stackedWidget->widget(3);
    QLineEdit* id = page->findChild<QLineEdit*>("id");

    if (!id)
    {
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
        else
        {
            qDebug() << "Query failed:" << qry.lastError().text();
        }
    }
}
//end of employe crud


//beginning of metier employe
void MainWindow::On_Export_Employe_Boutton_To_PDF_Clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", "", "PDF files (.pdf)");
    if (!fileName.isEmpty())
    {
        Export_Employe_To_PDF(fileName, ui->TableView_Emp);
    }
}
void MainWindow::Export_Employe_To_PDF(const QString &fileName, QTableView *tableView)
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
void MainWindow::Search_Employe(const QString &text)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (text.isEmpty())
    {
        query.prepare("SELECT ID_EMP, NOM, PRENOM, EMAIL, PASSWORD, TELEPHONE, SALAIRE, ADRESS, SEXE, ROLE FROM EMPLOYEE");
    }
    else
    {
        query.prepare("SELECT ID_EMP, NOM, PRENOM, EMAIL, PASSWORD, TELEPHONE, SALAIRE, ADRESS, SEXE, ROLE FROM EMPLOYEE WHERE ID_EMP LIKE :search OR NOM LIKE :search OR PRENOM LIKE :search OR EMAIL LIKE :search OR SEXE LIKE :search OR TELEPHONE LIKE :search OR ROLE LIKE :search OR ADRESS LIKE :search OR SALAIRE LIKE :search");
        query.bindValue(":search", "%" + text + "%");
    }

    if (query.exec())
    {
        model->setQuery(query);
        ui->TableView_Emp->setModel(model);
    }
    else
    {
        qDebug() << "Erreur lors de la recherche : " << query.lastError().text();
    }
}
void MainWindow::Export_Employe_To_TEXT(const QString &fileName)
{
    QAbstractItemModel *model = ui->TableView_Emp->model();
    int rows = model->rowCount();
    int cols = model->columnCount();
    QString tableData;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            QModelIndex index = model->index(row, col);
            QString cellData = model->data(index).toString();
            tableData.append(cellData);

            if (col < cols - 1)
                tableData.append("\t");
            else
                tableData.append("\n");
        }
    }
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << tableData;
        file.close();
    }
    else
    {
        qDebug() << "Error: Could not open file for writing";
    }
}
void MainWindow::On_Filter_Employe_Button_clicked()
{
    QString filterOption = ui->ComboBox_Emp->currentText();
    Apply_Employe_Filter(filterOption);
}
void MainWindow::Apply_Employe_Filter(const QString &filterOption)
{
    QString query;
    if (filterOption == "None")
    {
        query = "SELECT ID_EMP, NOM, PRENOM, EMAIL, PASSWORD, TELEPHONE, SALAIRE, ADRESS, SEXE, ROLE FROM EMPLOYEE";
    }
    else if (filterOption == "ID_EMP ASC")
    {
        query = "SELECT ID_EMP, NOM, PRENOM, EMAIL, PASSWORD, TELEPHONE, SALAIRE, ADRESS, SEXE, ROLE FROM EMPLOYEE ORDER BY ID_EMP ASC";
    }
    else if (filterOption == "ID_EMP DESC")
    {
        query = "SELECT ID_EMP, NOM, PRENOM, EMAIL, PASSWORD, TELEPHONE, SALAIRE, ADRESS, SEXE, ROLE FROM EMPLOYEE ORDER BY ID_EMP DESC";
    }
    else if (filterOption == "SALAIRE ASC")
    {
        query = "SELECT ID_EMP, NOM, PRENOM, EMAIL, PASSWORD, TELEPHONE, SALAIRE, ADRESS, SEXE, ROLE FROM EMPLOYEE ORDER BY CAST(SALAIRE AS NUMBER) ASC";
    }
    else if (filterOption == "SALAIRE DESC")
    {
        query = "SELECT ID_EMP, NOM, PRENOM, EMAIL, PASSWORD, TELEPHONE, SALAIRE, ADRESS, SEXE, ROLE FROM EMPLOYEE ORDER BY CAST(SALAIRE AS NUMBER) DESC";
    }
    else if (filterOption == "NOM and PRENOM ASC")
    {
        query = "SELECT ID_EMP, NOM, PRENOM, EMAIL, PASSWORD, TELEPHONE, SALAIRE, ADRESS, SEXE, ROLE FROM EMPLOYEE ORDER BY NOM ASC, PRENOM ASC";
    }
    else if (filterOption == "NOM and PRENOM DESC")
    {
        query = "SELECT ID_EMP, NOM, PRENOM, EMAIL, PASSWORD, TELEPHONE, SALAIRE, ADRESS, SEXE, ROLE FROM EMPLOYEE ORDER BY NOM DESC, PRENOM DESC";
    }
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    ui->TableView_Emp->setModel(model);
}


void MainWindow::Generate_Employee_Statistics()
{
    QString roleQuery = "SELECT ROLE, COUNT(*) FROM EMPLOYEE GROUP BY ROLE";
    QSqlQuery roleCountQuery(roleQuery);
    QMap<QString, int> roleCounts;
    int totalEmployees = 0;
    while (roleCountQuery.next())
    {
        QString role = roleCountQuery.value(0).toString();
        int count = roleCountQuery.value(1).toInt();
        roleCounts.insert(role, count);
        totalEmployees += count;
    }
    QString sexeQuery = "SELECT SEXE, COUNT(*) FROM EMPLOYEE GROUP BY SEXE";
    QSqlQuery sexeCountQuery(sexeQuery);
    QMap<QString, int> sexeCounts;
    int totalSexes = 0;
    while (sexeCountQuery.next())
    {
        QString sexe = sexeCountQuery.value(0).toString();
        int count = sexeCountQuery.value(1).toInt();
        sexeCounts.insert(sexe, count);
        totalSexes += count;
    }
    QPieSeries *roleSeries = new QPieSeries();
    for (auto it = roleCounts.begin(); it != roleCounts.end(); ++it)
    {
        QString role = it.key();
        int count = it.value();
        double percentage = (count * 100.0) / totalEmployees;
        roleSeries->append(role + " (" + QString::number(count) + ", " + QString::number(percentage, 'f', 2) + "%)", percentage);
    }
    QChart *roleChart = new QChart();
    roleChart->addSeries(roleSeries);
    roleChart->setTitle("Employee Role Distribution");
    roleChart->setAnimationOptions(QChart::SeriesAnimations);
    QBarSet *sexeSet = new QBarSet("Sexe Distribution");
    QStringList categories;
    for (auto it = sexeCounts.begin(); it != sexeCounts.end(); ++it)
    {
        QString sexe = it.key();
        int count = it.value();
        double percentage = (count * 100.0) / totalSexes;
        *sexeSet << percentage;
        categories << sexe + " (" + QString::number(count) + ", " + QString::number(percentage, 'f', 2) + "%)";
    }
    QBarSeries *sexeSeries = new QBarSeries();
    sexeSeries->append(sexeSet);
    QChart *sexeChart = new QChart();
    sexeChart->addSeries(sexeSeries);
    sexeChart->setTitle("Employee Sexe Distribution");
    sexeChart->setAnimationOptions(QChart::SeriesAnimations);
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    sexeChart->createDefaultAxes();
    sexeChart->setAxisX(axis, sexeSeries);
    sexeChart->legend()->setVisible(false);
    QChartView *roleChartView = new QChartView(roleChart);
    roleChartView->setRenderHint(QPainter::Antialiasing);
    QChartView *sexeChartView = new QChartView(sexeChart);
    sexeChartView->setRenderHint(QPainter::Antialiasing);
    QWidget *chartsWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(roleChartView);
    layout->addWidget(sexeChartView);
    chartsWidget->setLayout(layout);
    int pageIndex = 11;
    QWidget *pageWidget = ui->stackedWidget->widget(pageIndex);
    QVBoxLayout *pageLayout = new QVBoxLayout();
    pageLayout->addWidget(chartsWidget);
    pageWidget->setLayout(pageLayout);
}


void MainWindow::Go_And_Refresh_Employe_Statistics()
{
    QLayout *existingLayout = ui->Employe_Stat->layout();
    if (existingLayout)
    {
        delete existingLayout;
    }
    Generate_Employee_Statistics();
}

//fin tache employe


//tache event
void MainWindow::On_Delete_Button_Event_Clicked()
{
    QModelIndexList selectedIndexes = ui->table_event->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty())
    {
        int row = selectedIndexes.first().row();
        qDebug() << "Selected Index Row:" << row;
        int eventID = ui->table_event->model()->data(ui->table_event->model()->index(row, 0)).toInt();
        qDebug() << "Selected Event ID:" << eventID;
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirm Deletion",
                                             "Are you sure you want to delete the event with ID: " + QString::number(eventID) + "?",
                                             QMessageBox::Yes|QMessageBox::No);

        if (confirmation == QMessageBox::Yes)
        {
            evenement E;
            bool success = E.deleteEvent(eventID);
            if(success)
            {
                ui->table_event->setModel(E.afficherevenement());
                QMessageBox::information(this, "Event Deleted", "The selected event has been deleted.");
            }
            else
            {
                QMessageBox::warning(this, "Error", "Failed to delete event.");
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "No Event Selected", "Please select an event to delete.");
    }
}
void MainWindow::On_Cadd_Event_Clicked()
{
    QString type_event = ui->type_event->text();
    QString duree = ui->duree->text();
    QString sponsor = ui->sponsor->text();
    QString montant_str = ui->montant->text();
    if (type_event.isEmpty() || duree.isEmpty() || sponsor.isEmpty() || montant_str.isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }
    bool montant_ok;
    int montant = montant_str.toInt(&montant_ok);
    if (!montant_ok)
    {
        QMessageBox::critical(this, "Erreur", "Montant invalide. Veuillez entrer un nombre entier.");
        return;
    }
    QRegularExpression regex("^[a-zA-Z0-9_]*$");
    if (!regex.match(type_event).hasMatch() || !regex.match(duree).hasMatch() || !regex.match(sponsor).hasMatch())
    {
        QMessageBox::critical(this, "Erreur", "Les champs ne doivent pas contenir de caractères spéciaux.");
        return;
    }
    evenement E(type_event, duree, sponsor, montant);
    bool test = E.ajouterevenement();
    if (test)
    {
        ui->table_event->setModel(E.afficherevenement());
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
    ui->type_event->clear();
    ui->duree->clear();
    ui->montant->clear();
    ui->sponsor->clear();
}
void MainWindow::Search_Event(const QString &text)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM evenements WHERE id_event LIKE :search OR type_event LIKE :search OR duree LIKE :search OR sponsor LIKE :search");
    query.bindValue(":search", "%" + text + "%");

    if (query.exec())
    {
        model->setQuery(query);
        ui->table_event->setModel(model);
    }
    else
    {
        qDebug() << "Erreur lors de la recherche : " << query.lastError().text();
    }
}
void MainWindow::Export_PDF_Event()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", "", "PDF files (*.pdf)");
    if (!fileName.isEmpty())
    {
        Export_To_Pdf_Event(fileName, ui->table_event);
    }
}

void MainWindow::Export_To_Pdf_Event(const QString &fileName, QTableView *tableView)
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
void MainWindow::On_Update_Event_Button_Clicked_On_Table()
{
    ui->caddevent->setVisible(false);
    ui->Cupdate_Event->setVisible(true);
    QModelIndexList selectedIndexes = ui->table_event->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "No Row Selected", "Please select an event to update.");
        return;
    }
    int row = selectedIndexes.first().row();
    QString id_event = ui->table_event->model()->index(row, 0).data().toString();
    QString  type_event= ui->table_event->model()->index(row, 1).data().toString();
    QString duree = ui->table_event->model()->index(row, 2).data().toString();
    QString montant = ui->table_event->model()->index(row, 3).data().toString();
    QString sponsor = ui->table_event->model()->index(row, 4).data().toString();

    ui->type_event->setText(type_event);
    ui->duree->setText(duree);
    ui->montant->setText(montant);
    ui->sponsor->setText(sponsor);


    Navigate_To_Page(7);
}

void MainWindow::On_CUpdate_Event_Button_Clicked_On_Form()
{
    evenement ev;
    QString type_event = ui->type_event->text();
    QString duree = ui->duree->text();
    QString montant = ui->montant->text();
    QString sponsor = ui->sponsor->text();


    QModelIndexList selectedIndexes = ui->table_event->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "No Row Selected", "Please select an event to update.");
        return;
    }
    int row = selectedIndexes.first().row();
    int id = ui->table_event->model()->index(row, 0).data().toInt();
    bool success = ev.modifierevenement(id,type_event,duree,montant.toInt(),sponsor );
    if (success)
    {
        QMessageBox::information(this, "Update Successful", "Event information updated successfully.");
        ui->table_event->setModel(ev.afficherevenement());
    }
    else
    {
        QMessageBox::warning(this, "Update Failed", "Failed to update event information.");
    }
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::While_Going_To_Event_Form()
{
    ui->type_event->clear();
    ui->duree->clear();
    ui->montant->clear();
    ui->sponsor->clear();
    ui->caddevent->setVisible(true);
    ui->Cupdate_Event->setVisible(false);

}
void MainWindow::On_Event_Stat_Clicked()
{
    QSqlQuery dataQuery;
    dataQuery.prepare("SELECT type_event, SUM(montant) AS total_amount FROM evenements GROUP BY type_event");
    dataQuery.exec();
    QBarSeries *barSeries = new QBarSeries();
    QChart *barChart = new QChart();
    barChart->setTitle("Répartition des événements par montant");
    QPieSeries *pieSeries = new QPieSeries();
    QChart *pieChart = new QChart();
    pieChart->setTitle("Répartition des événements par montant");
    int totalAmountBar = 0;
    int totalAmountPie = 0;
    QStringList pieColors = {"#FF5733", "#33FF57", "#3357FF", "#FFFF33", "#FF33FF", "#33FFFF", "#999999", "#FF9933", "#33FF99", "#9933FF"};
    while (dataQuery.next())
    {
        QString eventType = dataQuery.value("type_event").toString();
        int totalAmount = dataQuery.value("total_amount").toInt();
        QBarSet *barSet = new QBarSet(eventType);
        *barSet << totalAmount;
        barSeries->append(barSet);
        QPieSlice *slice = pieSeries->append(eventType, totalAmount);
        slice->setLabel(QString("%1\n%2% (%3)").arg(eventType).arg(((double)totalAmount / totalAmountPie) * 100, 0, 'f', 1).arg(totalAmount));
        slice->setColor(QColor(pieColors[pieSeries->slices().size() % pieColors.size()]));
        totalAmountBar += totalAmount;
        totalAmountPie += totalAmount;
    }
    barChart->addSeries(barSeries);
    pieChart->addSeries(pieSeries);
    barChart->setAxisX(new QBarCategoryAxis(), barSeries);
    barChart->setAxisY(new QValueAxis(), barSeries);
    barChart->setAnimationOptions(QChart::AllAnimations);
    pieChart->setAnimationOptions(QChart::AllAnimations);
    QChartView *barChartView = new QChartView(barChart);
    barChartView->setRenderHint(QPainter::Antialiasing);
    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(barChartView);
    layout->addWidget(pieChartView);
    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    ui->stackedWidget->insertWidget(12, widget);
}
void MainWindow::On_Filter_Event_Button_Clicked()
{
    QString filterOption = ui->ComboBox_Event->currentText();
    Apply_event_Filter(filterOption);
}
void MainWindow::Apply_event_Filter(const QString &filterOption)
{
    QString query;
    if (filterOption == "None")
    {
        query = "SELECT ID_EVENT, TYPE_EVENT, DUREE, MONTANT, SPONSOR FROM EVENEMENTS";
    }
    else if (filterOption == "ID_EVENT ASC")
    {
        query = "SELECT ID_EVENT, TYPE_EVENT, DUREE, MONTANT, SPONSOR FROM EVENEMENTS ORDER BY ID_EVENT ASC";
    }
    else if (filterOption == "ID_EVENT DESC")
    {
        query = "SELECT ID_EVENT, TYPE_EVENT, DUREE, MONTANT, SPONSOR FROM EVENEMENTS ORDER BY ID_EVENT DESC";
    }
    else if (filterOption == "MONTANT ASC")
    {
        query = "SELECT ID_EVENT, TYPE_EVENT, DUREE, MONTANT, SPONSOR FROM EVENEMENTS ORDER BY MONTANT ASC";
    }
    else if (filterOption == "MONTANT DESC")
    {
        query = "SELECT ID_EVENT, TYPE_EVENT, DUREE, MONTANT, SPONSOR FROM EVENEMENTS ORDER BY MONTANT DESC";
    }
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    ui->table_event->setModel(model);
}
//fin tache event


//begin of tache materiel
void MainWindow::On_Cadd_Boutton_Mat_Clicked()
{
    QString etat = ui->ETAT_Mat->text();
    QString prix = ui->PRIX_Mat->text();
    QString id_emp = ui->IDEMP_Mat->text();
    QString id_fourni = ui->IDFOR_Mat->text();
    materiel Materiel(etat, prix.toFloat(), id_emp.toInt(), id_fourni.toInt());

    bool test = Materiel.ajouter_mat();
    ui->TableView_Mat->setModel(Materiel.afficher_mat());
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

void MainWindow::On_Delete_Button_Mat_Clicked()
{
    QModelIndexList selectedIndexes = ui->TableView_Mat->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        qDebug() << "Selected Index Row:" << row;
        int id_mat = ui->TableView_Mat->model()->data(ui->TableView_Mat->model()->index(row, 0)).toInt();
        qDebug() << "Selected materiel ID:" << id_mat;
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirm Deletion",
                                             "Are you sure you want to delete the Materiel with ID: " + QString::number(id_mat) + "?",
                                             QMessageBox::Yes|QMessageBox::No);

        if (confirmation == QMessageBox::Yes) {
           materiel Materiel;
           bool success = Materiel.delete_mat(id_mat);
            if(success) {
                ui->TableView_Mat->setModel(Materiel.afficher_mat());
                QMessageBox::information(this, "Employee Deleted", "The selected Materiel has been deleted.");
            } else {
                QMessageBox::warning(this, "Error", "Failed to delete Materiel.");
            }
        }
    } else {
        QMessageBox::warning(this, "No Materiel Selected", "Please select an Materiel to delete.");
    }
}
void MainWindow::On_Update_Button_Mat_Clicked()
{
    ui->Cadd_Mat->setVisible(false);
    ui->Cupdate_Mat->setVisible(true);
    QModelIndexList selectedIndexes = ui->TableView_Mat->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Row Selected", "Please select a material to update.");
        return;
    }
    int row = selectedIndexes.first().row();
    QString etat = ui->TableView_Mat->model()->index(row, 1).data().toString();
    QString prix = ui->TableView_Mat->model()->index(row, 2).data().toString();
    QString id_emp = ui->TableView_Mat->model()->index(row, 3).data().toString();
    QString id_fourni = ui->TableView_Mat->model()->index(row, 4).data().toString();
    ui->ETAT_Mat->setText(etat);
    ui->PRIX_Mat->setText(prix);
    ui->IDEMP_Mat->setText(id_emp);
    ui->IDFOR_Mat->setText(id_fourni);
    Navigate_To_Page(9);
}
void MainWindow::On_Mat_Update_Button_Clicked()
{
    QString etat = ui->ETAT_Mat->text();
    QString prix = ui->PRIX_Mat->text();
    QString id_emp = ui->IDEMP_Mat->text();
    QString id_fourni = ui->IDFOR_Mat->text();

    QModelIndexList selectedIndexes = ui->TableView_Mat->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Row Selected", "Please select a material to update.");
        return;
    }

    int row = selectedIndexes.first().row();
    int id_mat = ui->TableView_Mat->model()->index(row, 0).data().toInt();
 materiel Materiel;
    bool success =  Materiel.updateMaterial(id_mat, etat, prix.toInt(), id_emp.toInt(), id_fourni.toInt());
    if (success) {
        QMessageBox::information(this, "Update Successful", "Material information updated successfully.");
        ui->TableView_Mat->setModel(Materiel.afficher_mat());
        Navigate_To_Page(4);
        ui->ETAT_Mat->clear();
        ui->PRIX_Mat->clear();
        ui->IDEMP_Mat->clear();
        ui->IDFOR_Mat->clear();
    } else {
        QMessageBox::warning(this, "Update Failed", "Failed to update material information.");
    }
}
void MainWindow::On_Table_View_Mat_Activated(const QModelIndex &index)
{
    QStackedWidget* stackedWidget = ui->stackedWidget;
    QWidget* page = stackedWidget->widget(0);
    QLineEdit* id = page->findChild<QLineEdit*>("id");

    if (!id) {
        qDebug() << "ID LineEdit not found on page";
        return;
    }

    QString value = ui->TableView_Mat->model()->data(ui->TableView_Mat->model()->index(index.row(), 0)).toString();
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
            ui->ETAT_Mat->setText(qry.value(0).toString());
            ui->PRIX_Mat->setText(qry.value(1).toString());
            ui->IDEMP_Mat->setText(qry.value(3).toString());
            ui->IDFOR_Mat->setText(qry.value(4).toString());
            int numbercoloumn;
            numbercoloumn=ui->TableView_Mat->model()->columnCount();
            qDebug()<<numbercoloumn;
        }
    }
    else {
        qDebug() << "Query failed:" << qry.lastError().text();
    }
}
  //materiel metiers

void MainWindow::Export_Mat_Pdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", "", "PDF files (.pdf)");
    if (!fileName.isEmpty())
    {
        Export_Mat_To_Pdf(fileName, ui->TableView_Mat); // Utilisez votre QTableView ici
    }
}

void MainWindow::Export_Mat_To_Pdf(const QString &fileName, QTableView*tableView)
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

void MainWindow::On_Filter_Button_Mat_Clicked()
{
    QString filterOption = ui->ComboBox_Mat->currentText();
    Apply_Mat_Filter(filterOption);
}

void MainWindow::Apply_Mat_Filter(const QString &filterOption)
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
    }
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    ui->TableView_Mat->setModel(model);
    ui->TableView_Mat->update();
}


void MainWindow::Search_Mat(const QString &text)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM MATERIEL WHERE ID_MAT LIKE :search OR ETAT LIKE :search OR PRIX LIKE :search OR ID_EMP LIKE :search OR ID_FOURNI LIKE :search ");
    query.bindValue(":search", "%" + text + "%");

    if (query.exec())
    {
        model->setQuery(query);
        ui->TableView_Mat->setModel(model);
    }
    else
    {
        qDebug() << "Erreur lors de la recherche : " << query.lastError().text();
    }
}
void MainWindow::While_Going_To_Mat_Form()
{
    ui->ETAT_Mat->clear();
    ui->PRIX_Mat->clear();
    ui->IDEMP_Mat->clear();
    ui->IDFOR_Mat->clear();
    ui->Cadd_Mat->setVisible(true);
    ui->Cupdate_Mat->setVisible(false);

}

void MainWindow::On_Stat_Mat_Clicked()
{
    visualize_Mat_Statistics();
}

void MainWindow::visualize_Mat_Statistics()
{
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Materiel Statistics by etat");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QSqlQuery query("SELECT ETAT, COUNT(*) FROM MATERIEL GROUP BY ETAT");
    while (query.next()) {
        QString state = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(state, count);
    }
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget *chartPage = ui->stackedWidget->widget(14);
    if (!chartPage->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(chartPage);
        layout->addWidget(chartView);
    } else {
        QLayout *existingLayout = chartPage->layout();
        QLayoutItem *child;
        while ((child = existingLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        existingLayout->addWidget(chartView);
    }
    chart->setAnimationOptions(QtCharts::QChart::AllAnimations);
}


//fin tache materiel
