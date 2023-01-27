#ifndef MODEL_H
#define MODEL_H

#include "piecescollector.h"

class model
{
private:
    PiecesCollector* collector;
public:
    model();
    ~model();

    QVector<piece*> getPiecesCollector() const;

    PiecesCollector* getModelCollector() const;

    void setCollector(PiecesCollector*);
};

#endif // MODEL_H
