#include "linechart.h"
#include "view.h"

linechart::linechart(): seriesLine(new QLineSeries()), chart(new QChart()), lineChart(new QChartView(chart,this)){
    chart->legend()->hide();
    chart->addSeries(seriesLine);
    chart->createDefaultAxes();
    QFont graphTitle("Times", 9, QFont::Bold);
    chart->setTitleFont(graphTitle);
    chart->setTitle("Earning for each item");
    lineChart->setRenderHint(QPainter::Antialiasing);
    chart->setTheme(QChart::ChartThemeDark);
    chart->axisX()->setTitleText("Item (table enumeration)");
    chart->axisY()->setTitleText("Profit");
    lineChart->setFixedSize(QSize(800,800));
    chart->setAnimationOptions(QChart::NoAnimation);
}

linechart::~linechart(){ lineChart->deleteLater(); }

graph* linechart::displayLineChart(QVector<createrecord*> v, QHBoxLayout* graphsSpaceArea){
    update(v);
    graphsSpaceArea->setContentsMargins(30, 20, 40, 60);
    graphsSpaceArea->addWidget(lineChart);
    return this;
}

void linechart::update(const QVector<createrecord*>& v){
    int j=0;
    QVector<double> allEarnings;
    QLineSeries* updatedLineSeries = new QLineSeries();
    for(QVector<createrecord*>::const_iterator cit=v.begin(); cit!=v.end();++cit){
        double s=(*cit)->getSoldPieces()->text().toDouble();
        double n=(*cit)->getPrice()->value();
        updatedLineSeries->append(j,s*n);
        allEarnings.push_back((*cit)->getSoldPieces()->text().toDouble()*(*cit)->getPrice()->value());
        j++;
    }
    delete seriesLine;
    seriesLine=updatedLineSeries;
    chart->addSeries(seriesLine);
    QValueAxis* axisX = new QValueAxis();
    axisX->setLabelFormat("%.0f");
    QValueAxis* axisY = new QValueAxis();
    if(j>1){
        double maxx = *std::max_element(allEarnings.begin(),allEarnings.end());
        double minx = *std::min_element(allEarnings.begin(),allEarnings.end());
        axisX->setRange(1,j);
        axisX->setMin(1);
        axisX->setMax(j);
        axisX->setTickCount(j);
        if(minx==maxx){
            axisY->setRange(0,100);
            axisY->setMin(0);
            axisY->setMax(100);
        } else {
            axisY->setRange(minx,maxx);
            axisY->setMin(minx);
            axisY->setMax(maxx);
        }
    } else {
        axisX->setRange(1,5);
        axisX->setMin(1);
        axisX->setMax(5);
        axisX->setTickCount(5);
        axisY->setRange(0,100);
        axisY->setMin(0);
        axisY->setMax(100);
    }
    chart->setAxisX(axisX);
    chart->setAxisY(axisY);
    chart->axisX()->setTitleText("Item (table enumeration)");
    chart->axisY()->setTitleText("Profit");
    lineChart->setChart(chart);
}
