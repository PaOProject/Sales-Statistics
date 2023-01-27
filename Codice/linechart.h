#ifndef LINECHART_H
#define LINECHART_H

#include "graph.h"
#include <QtCharts/QLineSeries>

class linechart : public graph
{
private:
    QLineSeries* seriesLine;
    QChart* chart;
    QChartView* lineChart;
public:
    linechart();
    ~linechart();
    graph* displayLineChart(QVector<createrecord*>,QHBoxLayout*);
    void update(const QVector<createrecord*>&) override;
};

#endif // LINECHART_H
