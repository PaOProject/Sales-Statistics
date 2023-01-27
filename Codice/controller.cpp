#include "controller.h"

controller::controller(QObject* parent): QObject(parent) { QTimer* timer2 = new QTimer(this); connect(timer2,SIGNAL(timeout()),this,SLOT(setModelCollector())); timer2->start(2000);}

controller::~controller(){}

void controller::setModel(model* m){
    Model=m;
}

void controller::setView(view* v){
    View=v;
}

void controller::openFile(){
    View->openFileDialog();
    PiecesCollector* p = jsondata::readJ(View->getFilePath());
    if(p){
        Model->setCollector(p);
        View->importedData(Model->getModelCollector());
    }
}

void controller::saveFile(){
    if(!(View->getFilePath().isEmpty())){
        jsondata::writeJ(Model->getModelCollector(),View->getFilePath());
    }
}

void controller::saveAsFile(){
    View->openSaveAsDialog();
    jsondata::writeJ(Model->getModelCollector(),View->getFilePath());
}

void controller::addRecord(){
    View->addTableRecord();
}

void controller::deleteRecords(){
    View->deleteTableRecords();
}

void controller::clearAll(){
    View->clear();
}

void controller::showBarChart(){
    barchart* b = new barchart();
    if(View->getCheckGraph() && dynamic_cast<barchart*>(View->getCheckGraph())) { delete b; }
    else if(View->recordCheck(View->getTableRecords(),b)){
        View->setDisplayedGraph(b->displayBarChart(View->getTableRecords(),View->getGraphsSpaceArea()));
        View->setCheckGraph(b);
    }
    else if(!(View->recordCheck(View->getTableRecords(),b))){
        View->setCheckGraph(nullptr);
        delete b;
        View->showErrorMessage("To show the bar chart you need at least one valid brand, price and trimestral sold pieces for each record");
    }
}

void controller::showDonutChart(){
    donutchart* d = new donutchart();
    if(View->getCheckGraph() && dynamic_cast<donutchart*>(View->getCheckGraph())) { delete d; }
    else if(View->recordCheck(View->getTableRecords(),d)){
        View->setDisplayedGraph(d->displayDonutChart(View->getTableRecords(),View->getGraphsSpaceArea()));
        View->setCheckGraph(d);
    }
    else if(!(View->recordCheck(View->getTableRecords(),d))){
        View->setCheckGraph(nullptr);
        delete d;
        View->showErrorMessage("To show the donut chart you need at least one record and one valid brand for each record");
    }
}

void controller::showPointChart(){
    pointchart* s = new pointchart();
    if(View->getCheckGraph() && dynamic_cast<pointchart*>(View->getCheckGraph())) { delete s; }
    else if(View->recordCheck(View->getTableRecords(),s)){
        View->setDisplayedGraph(s->displayPointChart(View->getTableRecords(),View->getGraphsSpaceArea()));
        View->setCheckGraph(s);
    }
    else if(!(View->recordCheck(View->getTableRecords(),s))){
        View->setCheckGraph(nullptr);
        delete s;
        View->showErrorMessage("To show the point chart you need at least 2 table records");
    }
}

void controller::showLineChart(){
    linechart* l = new linechart();
    if(View->getCheckGraph() && dynamic_cast<linechart*>(View->getCheckGraph())) { delete l; }
    else if(View->recordCheck(View->getTableRecords(),l)){
        View->setDisplayedGraph(l->displayLineChart(View->getTableRecords(),View->getGraphsSpaceArea()));
        View->setCheckGraph(l);
    }
    else if(!(View->recordCheck(View->getTableRecords(),l))){
        View->setCheckGraph(nullptr);
        delete l;
        View->showErrorMessage("To show the line chart you need at least 2 table records");
    }
}

void controller::showPieChart(){
    piechart* p = new piechart();
    if(View->getCheckGraph() && dynamic_cast<piechart*>(View->getCheckGraph())) { delete p; }
    else if(View->recordCheck(View->getTableRecords(),p)){
        View->setDisplayedGraph(p->displayPieChart(View->getTableRecords(),View->getGraphsSpaceArea()));
        View->setCheckGraph(p);
    }
    else if(!(View->recordCheck(View->getTableRecords(),p))){
        View->setCheckGraph(nullptr);
        delete p;
        View->showErrorMessage("To show the pie chart you need at least one record and one valid brand for each record");
    }
}

void controller::updateGraph(){
    graph* g = const_cast<graph*>(View->getDisplayedGraph());
    if(View->recordCheck(View->getTableRecords(),g)) g->update(View->getTableRecords());
    else {
        if(dynamic_cast<barchart*>(g)){
            View->showErrorMessage("To update the bar chart you need at least one valid brand, price and trimestral sold pieces for each record");
        }
        else if(dynamic_cast<donutchart*>(g)){
            View->showErrorMessage("To update the donut chart you need at least one record and one valid brand for each record");
        }
        else if(dynamic_cast<pointchart*>(g)){
            View->showErrorMessage("To update the point chart you need at least 2 table records");
        }
        else if(dynamic_cast<linechart*>(g)){
            View->showErrorMessage("To update the line chart you need at least 2 table records");
        }
        else{
            View->showErrorMessage("To update the pie chart you need at least one record and one valid brand for each record");
        }
    }
}

void controller::setModelCollector(){
    Model->setCollector(View->extractData());
}
