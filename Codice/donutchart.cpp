#include "donutchart.h"

donutchart::donutchart(): donutSeries(new QPieSeries()){
    donutSeries->setHoleSize(0.25);
    donutChart = new QChartView();
    donutChart->setRenderHint(QPainter::Antialiasing);
    donutChart->chart()->setTitle("Sold pieces per brand");
    donutChart->chart()->addSeries(donutSeries);
    donutChart->chart()->legend()->setAlignment(Qt::AlignRight);
    donutChart->chart()->setTheme(QChart::ChartThemeDark);
    donutChart->chart()->legend()->setFont(QFont("Arial", 10));
    donutChart->chart()->setAnimationOptions(QChart::SeriesAnimations);
}

donutchart::~donutchart(){ donutChart->deleteLater(); }

graph* donutchart::displayDonutChart(QVector<createrecord*> v, QHBoxLayout* graphsSpaceArea){
    update(v);
    graphsSpaceArea->setContentsMargins(30, 20, 40, 60);
    graphsSpaceArea->addWidget(donutChart);
    return this;
}

void donutchart::update(const QVector<createrecord*>& v){
    QString s;
    QVector<QString> l;
    for(QVector<createrecord*>::const_iterator cit=v.begin();cit!=v.end();++cit){
        bool found = false;
        s=(*cit)->getBrand()->text().toLower();
        for(auto it=l.begin();it!=l.end()&&!found;++it){
            if(*it == s) found = true;
        }
        if(!found) l.push_back(s);
    }
    QPieSeries* donutUpdate = new QPieSeries();
    brands=QVector<QString>(l.size());
    brands=l;
    soldpieces=QVector<int>(l.size());

    int index=0;
    for(QVector<QString>::const_iterator cit=brands.begin();cit!=brands.end();++cit){
        for(QVector<createrecord*>::const_iterator it=v.begin();it!=v.end();++it){
            if((*it)->getBrand()->text().toLower()==(*cit)){
                soldpieces[index] += (*it)->getSoldPieces()->text().toInt();
            }
        }
        donutUpdate->append((*cit),soldpieces[index]);
        index++;
    }
    donutUpdate->setHoleSize(0.25);
    if(!donutSeries->isEmpty()){
        donutChart->chart()->removeAllSeries();
    }
    donutSeries=donutUpdate;
    unsigned int seed=time(0);
    srand(seed);
    QList<QPieSlice*> ps= donutSeries->slices();
    for(auto it = ps.begin();it!=ps.end();++it){
        bool out=false;
        while(!out){
            int color1=rand()%256;
            int color2=rand()%256;
            int color3=rand()%256;
            bool samecolor=false;
            for(auto cit = ps.begin();cit!=ps.end()&&!samecolor;++cit){
                if(QColor(color1,color2,color3,255)==(*cit)->color()){
                    samecolor=true;
                }
            }
            if(!samecolor){ (*it)->setBrush(QColor(color1,color2,color3,255)); out=true; }
        }
    }
    donutChart->chart()->addSeries(donutSeries);
}
