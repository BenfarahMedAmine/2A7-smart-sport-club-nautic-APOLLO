#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseurs.h"

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Déclaration des prototypes des fonctions



private slots:
    void on_pushButton_clicked();
    void on_deleteButton_clicked();
    void on_tableView_activated(const QModelIndex &index);
    void onUpdateButtonClicked();
    void onmiseajourButtonClicked();
    void navigateToPage(int pageIndex);



private:
    Ui::MainWindow *ui;
    fournisseurs fourni;


};
#endif // MAINWINDOW_H
