#include "barchart.h"
#include <QDebug>

barchart::barchart(){
    QStringList quarterly;
    quarterly << "January-March" << "April-June" <<"July-September" << "October-December";
    chart = new QChart();
    barSeries= new QBarSeries();
    chart->addSeries(barSeries);

    QFont graphTcitle("Times", 9, QFont::Bold);
    chart->setTitleFont(graphTcitle);
    chart->setTitle("Trimestral sold pieces for each brand");

    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(quarterly);
    axisX->setTitleText("Trimesters");
    chart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    barChart = new QChartView(chart);
    barChart->setRenderHint(QPainter::Antialiasing);
}

barchart::~barchart(){ barChart->deleteLater(); }

graph* barchart::displayBarChart(QVector<createrecord*> v, QHBoxLayout* graphsSpaceArea){
    update(v);
    graphsSpaceArea->setContentsMargins(30, 20, 40, 60);
    graphsSpaceArea->addWidget(barChart);
    return this;
}

void barchart::update(const QVector<createrecord*>& v){
    QString s;
    QVector<QString> l;
    for(QVector<createrecord*>::const_iterator cit=v.begin();cit!=v.end();++cit){
        bool found=false;
        s=(*cit)->getBrand()->text().toLower();
        for(auto it=l.begin();it!=l.end()&&!found;++it){
            if(*it == s) found = true;
        }
        if(!found) l.push_back(s);
    }

    str=l;

    BarSetAr=QVector<QBarSet*>();

    QBarSet* b;
    for(int i=0;i<str.size();++i){
        b = new QBarSet(str[i]);
        BarSetAr.push_back(b);
    }

    int siumJM[str.size()]={0};
    int siumJS[str.size()]={0};
    int siumAJ[str.size()]={0};
    int siumOD[str.size()]={0};

    for(QVector<createrecord*>::const_iterator cit=v.begin();cit!=v.end();++cit){
        bool exit=false;
        for(int l=0;l<str.size()&&!exit;++l){
            if((*cit)->getBrand()->text().toLower()==str[l]){
                siumJM[l]+=(*cit)->getJm()->text().toInt();
                siumAJ[l]+=(*cit)->getAj()->text().toInt();
                siumJS[l]+=(*cit)->getJs()->text().toInt();
                siumOD[l]+=(*cit)->getOd()->text().toInt();
                exit=true;
            }
        }
    }

    int k=0;
    for(QVector<QBarSet*>::iterator it=BarSetAr.begin();it!=BarSetAr.end();++it){
        (*it)->append(siumJM[k]);
        (*it)->append(siumAJ[k]);
        (*it)->append(siumJS[k]);
        (*it)->append(siumOD[k]);
        k++;
    }

    QBarSeries* updatedBarSeries = new QBarSeries();
    chart->removeSeries(barSeries);

    for(QVector<QBarSet*>::iterator it=BarSetAr.begin();it!=BarSetAr.end();++it) updatedBarSeries->append(*it);

    unsigned int seed=time(0);
    srand(seed);
    for(auto it = BarSetAr.begin();it!=BarSetAr.end();++it){
        bool out=false;
        while(!out){
            int color1=rand()%256;
            int color2=rand()%256;
            int color3=rand()%256;
            bool samecolor=false;
            for(auto cit = BarSetAr.begin();cit!=BarSetAr.end()&&!samecolor;++cit){
                if(QColor(color1,color2,color3,255)==(*cit)->color()){
                    samecolor=true;
                }
            }
            if(!samecolor){ (*it)->setColor(QColor(color1,color2,color3,255)); out=true; }
        }
    }


    barSeries=updatedBarSeries;
    chart->addSeries(barSeries);

    QValueAxis* axisYup = new QValueAxis();
    chart->removeAxis(axisY);
    axisY=axisYup;
    axisY->setLabelFormat("%.0f");
    axisY->setTitleText("Trimestral sold pieces");
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);
}
