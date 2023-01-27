#ifndef PIECESCOLLECTOR_H
#define PIECESCOLLECTOR_H

#include <QVector>
#include "piece.h"

class PiecesCollector
{
private:
    QVector<piece*> collector;
public:
    PiecesCollector();
    void Delete(int);
    void Add(const piece&);
    void ClearAll();
    void Replace(int,const piece&);
    bool IsEmpty() const;
    int Size() const;
    piece* operator[](int) const;
    piece* getPiece(int) const;
    QVector<piece*> getCollector() const;
    PiecesCollector& operator=(const PiecesCollector&);
};

#endif // PIECESCOLLECTOR_H




