#include "piecescollector.h"

PiecesCollector::PiecesCollector(): collector(){}

bool PiecesCollector::IsEmpty()const{
    return collector.size()==0;
}

int PiecesCollector::Size() const{
    return collector.size();
}

void PiecesCollector::Add(const piece& other){
    piece* p=const_cast<piece*>(&other);
    collector.push_back(p);
}

void PiecesCollector::Delete(int i){
    QVector<piece*>::iterator it=collector.begin()+i;
    collector.erase(it);
    //if(*it) delete *it;
}

void PiecesCollector::ClearAll(){
    collector.clear();
}

piece* PiecesCollector::operator[](int i) const{
    QVector<piece*>::const_iterator it=collector.begin()+i;
    return *it;
}

piece* PiecesCollector::getPiece(int i) const{
    return collector[i];
}

QVector<piece *> PiecesCollector::getCollector() const{
    return collector;
}

void PiecesCollector::Replace(int i, const piece& other){
    piece* p=const_cast<piece*>(&other);
    delete collector[i];
    collector[i]=p;
}

PiecesCollector& PiecesCollector::operator=(const PiecesCollector& p){
    if(this!=&p){
        for(auto it=collector.begin();it!=collector.end();++it) delete *it;
        for(int i=0;i<p.Size();++i) collector[i]=p.collector[i];
    }
    return *this;
}

