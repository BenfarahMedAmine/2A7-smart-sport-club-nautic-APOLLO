#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool Validate_Employe_Input(const QString &nom, const QString &prenom, const QString &email,const QString &password,const QString &telephone, const QString &adress, const QString &salaire);
private:
    Ui::MainWindow *ui;
    int currentPageIndex;
    int currentSidebarIndex;
private slots:
     void Add_Employe();
     void On_Delete_Employe_Button_clicked();
     void On_Update_Employe_Button_Clicked_On_Table();
     void On_CUpdate_Employe_Button_Clicked_On_Form();
     void While_Going_To_Employe_Form();
     void On_Table_View_Employe_activated(const QModelIndex &index);



     void Navigate_To_Page(int pageIndex);
     void On_Sidebar_Button_Clicked(int sidebarIndex);
     void On_TopBar_Button_Clicked(int topBarIndex);

};
#endif // MAINWINDOW_H
