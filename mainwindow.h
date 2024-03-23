#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employee.h"
#include "evenement.h"
#include "materiel.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //employe part
    void Apply_Employe_Filter(const QString &filterOption);
    bool Validate_Employe_Input_Add(const QString &nom, const QString &prenom, const QString &email, const QString &password, const QString &telephone, const QString &adress, const QString &salaire);
    bool Validate_Employe_Input_Update(const QString &nom, const QString &prenom, const QString &email, const QString &password, const QString &telephone, const QString &adress, const QString &salaire);
    void Apply_event_Filter(const QString &filterOption);
private:
    Ui::MainWindow *ui;
    //for side bar
    int currentPageIndex;
    int currentSidebarIndex;
    QWidget *chartPage;
    //metier employee pdf et text
    void Export_Employe_To_PDF(const QString &fileName, QTableView *tableView);
    void Export_Employe_To_TEXT(const QString &fileName);

    //tache evenements
    void Export_To_Pdf_Event(const QString &fileName, QTableView *tableView);




private slots:
    //side bar work
    void Navigate_To_Page(int pageIndex);
    void On_Sidebar_Button_Clicked(int sidebarIndex);
    void On_TopBar_Button_Clicked(int topBarIndex);

    //crud employee
    void Add_Employe();
    void On_Delete_Employe_Button_clicked();
    void On_Update_Employe_Button_Clicked_On_Table();
    void On_CUpdate_Employe_Button_Clicked_On_Form();
    void While_Going_To_Employe_Form();
    void On_Table_View_Employe_activated(const QModelIndex &index);

    //metier employee
    void Search_Employe(const QString &text);
    void On_Filter_Employe_Button_clicked();
    void On_Export_Employe_Boutton_To_PDF_Clicked();
    void Generate_Employee_Statistics();
    void Go_And_Refresh_Employe_Statistics();

    //crud event
    void On_Delete_Button_Event_Clicked();
    void On_Cadd_Event_Clicked();
    void On_CUpdate_Event_Button_Clicked_On_Form();
    void On_Update_Event_Button_Clicked_On_Table();
    void While_Going_To_Event_Form();


    //metier event
    void Search_Event(const QString &text);
    void Export_PDF_Event();
    void On_Event_Stat_Clicked() ;
    void On_Filter_Event_Button_Clicked();


    //materiel Crud
    void On_Cadd_Boutton_Mat_Clicked();
    void On_Table_View_Mat_Activated(const QModelIndex &index);
    void On_Delete_Button_Mat_Clicked();
    void On_Update_Button_Mat_Clicked();
    void On_Mat_Update_Button_Clicked();
    void While_Going_To_Mat_Form();
    //materiel metier
    void Export_Mat_Pdf();
    void Export_Mat_To_Pdf(const QString &fileName, QTableView*tableView);
    void On_Filter_Button_Mat_Clicked();
    void Apply_Mat_Filter(const QString &filterOption);
    void Search_Mat(const QString &text);
    void On_Stat_Mat_Clicked();
    void visualize_Mat_Statistics();

};
#endif // MAINWINDOW_H
