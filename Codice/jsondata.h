#ifndef JSONDATA_H
#define JSONDATA_H

#include "piecescollector.h"
#include <QJsonObject>
#include <QString>
#include <QJsonDocument>
#include <QIODevice>
#include <QFile>
#include <QJsonArray>
#include <iostream>
#include <QTextStream>
#include "QDebug"

using std::cout;
using std::string;

class jsondata
{

public:
    static PiecesCollector* readJ(const QString& path);
    static void writeJ(PiecesCollector*,const QString& path);
};

#endif // JSONDATA_H
