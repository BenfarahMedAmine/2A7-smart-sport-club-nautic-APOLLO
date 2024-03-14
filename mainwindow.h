#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "evenement.h"
#include "materiel.h"
#include <vector>
#include <QMainWindow>
#include <QTableView>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QSqlQuery>
#include <QVBoxLayout>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




public slots:
    void refreshTable();


private slots:
    //boutons
    void clicker_list();
    void clicker_list1();
    void clicker_list2();
    void clicker_list3();
    void exportPdfEvent();

    void clicker_delete();
    void clicker_add();
    void clicker_update();
    void clicker_statistics();

    void on_statisticsButton_clicked();

    //
    void on_pushButton_ajouter_clicked();

   // void on_pushButton_supprimer_clicked();
   void on_deleteButtonEvent_clicked();

    void on_pushButton_update_clicked();
  void searchEvent(const QString &text);
   void exportCsv();
   //TRI
void sortAscending();
void sortDescending();
  //
void on_pushButton_statistique_2_clicked();

void on_pushButton_4_clicked();

//tache materiel

void on_cadd_clicked();
void navigateToPage(int pageIndex);
void on_tableView_activated(const QModelIndex &index);
void on_deleteButton_clicked();
void onUpdateButtonClicked();
void onMUpdateButtonClicked();
void exportPdf();



void on_goevent_clicked();

private:
void exportToPdfEvent(const QString &fileName, QTableView *tableView);
void exportToPdf(const QString &fileName, QTableView *tableView_2);

private:
    Ui::MainWindow *ui;
    evenement Etmp ;
    QtCharts::QChartView *chartView;
    QtCharts::QPieSeries *series;

};
#endif // MAINWINDOW_H
