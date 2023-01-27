#include "model.h"

model::~model(){ delete collector; }

model::model(): collector(new PiecesCollector){}

QVector<piece *> model::getPiecesCollector() const{
    return collector->getCollector();
}

PiecesCollector* model::getModelCollector() const{ return collector; }

void model::setCollector(PiecesCollector* p){ collector=p; }
