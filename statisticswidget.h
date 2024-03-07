#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

class StatisticsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    ~StatisticsWidget(); // Ajout du destructeur

    void setChartData();

private:
    QChartView *chartView;
    QPieSeries *series; // Déclaration de la série en tant que membre de classe pour pouvoir la libérer dans le destructeur
};

#endif // STATISTICSWIDGET_H
