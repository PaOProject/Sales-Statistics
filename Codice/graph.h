#ifndef GRAPH_H
#define GRAPH_H

#include "createtable.h"
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <algorithm>

QT_CHARTS_USE_NAMESPACE

class graph : public QWidget
{
public:
    virtual ~graph() =default;
    virtual void update(const QVector<createrecord*>&) =0;
};

#endif // GRAPH_H
