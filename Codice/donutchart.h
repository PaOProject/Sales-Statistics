#ifndef DONUTCHART_H
#define DONUTCHART_H

#include "graph.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

class donutchart : public graph
{
private:
    QPieSeries* donutSeries;
    QVector<QString> brands;
    QVector<int> soldpieces;
    QChartView* donutChart;
public:
    donutchart();
    ~donutchart();
    void update(const QVector<createrecord*>&) override;
    graph* displayDonutChart(QVector<createrecord*> v, QHBoxLayout*);
};

#endif // DONUTCHART_H
