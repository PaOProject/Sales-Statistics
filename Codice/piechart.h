#ifndef PIECHART_H
#define PIECHART_H

#include "graph.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

class piechart : public graph
{
private:
    QPieSeries* seriesPie;
    QChartView* pieChart;
    QVector<QString> Brands;
    QVector<double> Sales;
public:
    piechart();
    void update(const QVector<createrecord*>&) override;
    ~piechart();
    graph* displayPieChart(QVector<createrecord*> v, QHBoxLayout* graphsSpaceArea);
};

#endif // PIECHART_H
