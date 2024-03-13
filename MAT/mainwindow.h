#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QStackedWidget>
#include <QMap>
#include <QFile>
#include <QString>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "materiel.h"
#include <QFileDialog>
#include <QTableView>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
private:
   Ui::MainWindow *ui;

private slots:
    void on_cadd_clicked();
    void navigateToPage(int pageIndex);
    void on_tableView_activated(const QModelIndex &index);
    void on_deleteButton_clicked();
    void onUpdateButtonClicked();
    void onMUpdateButtonClicked();
    void exportPdf();
    void exportToPdf(const QString &fileName, QTableView*tableView);
    void on_filterButton_clicked();
    void applyFilter(const QString &filterOption);
    void searchMat(const QString &text);
};
#endif // MAINWINDOW_H
