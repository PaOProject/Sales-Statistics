#include "pointchart.h"

pointchart::pointchart(): seriesScatter(new QScatterSeries()), chart(new QChart()), pointChart(new QChartView(chart,this)){
    chart->legend()->hide();
    chart->addSeries(seriesScatter);
    QFont graphTitle("Times", 9, QFont::Bold);
    chart->setTitleFont(graphTitle);
    chart->setTitle("Sold pieces for each item");
    pointChart->setRenderHint(QPainter::Antialiasing);
    chart->setTheme(QChart::ChartThemeDark);
    pointChart->setFixedSize(QSize(800,800));
    chart->setAnimationOptions(QChart::NoAnimation);
}

pointchart::~pointchart(){ pointChart->deleteLater(); }

graph* pointchart::displayPointChart(QVector<createrecord*> v, QHBoxLayout* graphsSpaceArea){
    update(v);
    graphsSpaceArea->setContentsMargins(30, 20, 40, 60);
    graphsSpaceArea->addWidget(pointChart);
    return this;
}

void pointchart::update(const QVector<createrecord *> & v){
    int j=0;
    QVector<int> allSold;
    QScatterSeries* updatedseriesScatter = new QScatterSeries();
    for(QVector<createrecord*>::const_iterator cit=v.begin(); cit!=v.end();++cit){
        updatedseriesScatter->append(j,(*cit)->getSoldPieces()->text().toInt());
        allSold.push_back((*cit)->getSoldPieces()->text().toInt());
        j++;
    }

    delete seriesScatter;
    seriesScatter=updatedseriesScatter;
    chart->addSeries(seriesScatter);

    QValueAxis* axisX = new QValueAxis();
    axisX->setLabelFormat("%.0f");
    int maxx = *std::max_element(allSold.begin(),allSold.end());
    if(j>1){
        axisX->setRange(1,j);
        axisX->setTickCount(j);
    }
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0,maxx+10);
    chart->setAxisX(axisX);
    chart->axisX()->setTitleText("Item (table enumeration)");
    chart->axisY()->setTitleText("Sold pieces");
    pointChart->setChart(chart);
}
