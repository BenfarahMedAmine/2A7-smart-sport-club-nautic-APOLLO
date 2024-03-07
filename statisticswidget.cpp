#include "statisticswidget.h"
#include <QVBoxLayout>

StatisticsWidget::StatisticsWidget(QWidget *parent) : QWidget(parent), chartView(nullptr), series(nullptr)
{
    // Création du graphique et du widget de vue du graphique
    QChart *chart = new QChart();
    chartView = new QChartView(chart);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    setLayout(layout);
}

StatisticsWidget::~StatisticsWidget()
{
    // Libération de la mémoire allouée pour la série
    delete series;
}

void StatisticsWidget::setChartData()
{
    // Création d'une série de données pour le graphique
    series = new QPieSeries();

    // Connexion à la base de données
    QSqlDatabase db = QSqlDatabase::database();

    // Exécution de la requête pour récupérer les montants
    QSqlQuery query(db);
    query.prepare("SELECT montant FROM evenements");
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return;
    }

    // Création d'un QMap pour stocker les montants et leur fréquence
    QMap<int, int> montantFrequency;

    // Calcul de la fréquence des montants
    while (query.next()) {
        int montant = query.value(0).toInt(); // La colonne 0 contient les montants
        montantFrequency[montant]++;
    }

    // Ajout des données au graphique
    for (auto it = montantFrequency.constBegin(); it != montantFrequency.constEnd(); ++it) {
        series->append(QString::number(it.key()), it.value());
    }

    // Création du graphique à secteurs
    QChart *chart = chartView->chart();
    chart->removeAllSeries(); // Nettoyer le graphique avant d'ajouter de nouvelles données
    chart->addSeries(series);
    chart->setTitle("Statistiques des montants des événements");

    chartView->setRenderHint(QPainter::Antialiasing);
}
