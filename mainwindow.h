#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "evenement.h"
#include <vector>
#include <QMainWindow>
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

void clicker_statistics1();
void exportToWord(const QString &fileName);

public slots:
    void refreshTable();


private slots:
    //boutons
    void clicker_list();
    void clicker_list1();
    void clicker_list2();
    void clicker_list3();
    void exportPdf();


    void clicker_delete();
    void clicker_add();
    void clicker_update();
    void clicker_statistics();

    //
    void on_pushButton_ajouter_clicked();

   // void on_pushButton_supprimer_clicked();
   void on_deleteButton_clicked();

    void on_pushButton_update_clicked();
  void searchEvent(const QString &text);
   //TRI
void sortAscending();
void sortDescending();
  //
private:
void exportToPdf(const QString &fileName, QTableView *tableView);
private:
    Ui::MainWindow *ui;
    evenement Etmp ;
};
#endif // MAINWINDOW_H
