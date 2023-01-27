#ifndef POINTCHART_H
#define POINTCHART_H

#include "graph.h"
#include <QtCharts/QScatterSeries>

class pointchart : public graph
{
private:
    QScatterSeries* seriesScatter;
    QChart* chart;
    QChartView* pointChart;
public:
    pointchart();
    ~pointchart();
    graph* displayPointChart(QVector<createrecord*>,QHBoxLayout*);
    void update(const QVector<createrecord*>&) override;
};

#endif // POINTCHARTt_H
