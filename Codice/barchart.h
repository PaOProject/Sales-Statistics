#ifndef BARCHART_H
#define BARCHART_H

#include "graph.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVectorIterator>

class barchart : public graph
{
private:
    QBarSeries* barSeries;
    QVector<QString> str;
    QVector<QBarSet*> BarSetAr;
    QValueAxis* axisY;
    QChart* chart;
    QChartView* barChart;
public:
    barchart();
    ~barchart();
    graph* displayBarChart(QVector<createrecord*>, QHBoxLayout*);
    void update(const QVector<createrecord*>&) override;
};


#endif // BARCHART_H
