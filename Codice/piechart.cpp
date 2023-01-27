#include "piechart.h"

piechart::piechart():seriesPie(new QPieSeries()){
    pieChart=new QChartView();
    pieChart->setRenderHint(QPainter::Antialiasing);
    pieChart->chart()->addSeries(seriesPie);
    QFont graphTitle("Arial", 9, QFont::Bold);
    pieChart->chart()->setTitleFont(graphTitle);
    pieChart->chart()->setTitle("Earning for each brand");
    pieChart->chart()->setTheme(QChart::ChartThemeDark);
    pieChart->chart()->legend()->setAlignment(Qt::AlignRight);
    pieChart->chart()->legend()->setFont(QFont("Arial", 10));
    pieChart->setRenderHint(QPainter::Antialiasing);
    pieChart->chart()->setAnimationOptions(QChart::SeriesAnimations);
}

piechart::~piechart(){ pieChart->deleteLater(); }

graph* piechart::displayPieChart(QVector<createrecord *> v, QHBoxLayout *graphsSpaceArea){
    update(v);
    graphsSpaceArea->setContentsMargins(30, 20, 40, 60);
    graphsSpaceArea->addWidget(pieChart);
    return this;
}

void piechart::update(const QVector<createrecord*>& v){
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
    QPieSeries* pieUpdate = new QPieSeries();
    Brands=QVector<QString>(l.size());
    Brands=l;
    Sales=QVector<double>(l.size());

    int index=0;
    int maxind=0;
    for(QVector<QString>::const_iterator cit=Brands.begin();cit!=Brands.end();++cit){
        for(QVector<createrecord*>::const_iterator it=v.begin();it!=v.end();++it){
            if((*it)->getBrand()->text().toLower()==(*cit)){
                Sales[index] += (*it)->getPrice()->value()*(*it)->getSoldPieces()->text().toInt();
                bool verify=false;
                for(int i=0;i<Sales.size()&&!verify;++i){
                    if(Sales[i]>Sales[index]) verify=true;
                }
                if(!verify) maxind=index;
            }
        }
        pieUpdate->append((*cit),Sales[index]);
        index++;
    }
    if(!seriesPie->isEmpty()){
        pieChart->chart()->removeAllSeries();
    }
    seriesPie=pieUpdate;
    unsigned int seed=time(0);
    srand(seed);
    QList<QPieSlice*> ps= seriesPie->slices();
    ps[maxind]->setExploded();
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
    pieChart->chart()->addSeries(seriesPie);
}
