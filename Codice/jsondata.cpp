#include "jsondata.h"

PiecesCollector* jsondata::readJ(const QString& path){
    PiecesCollector* tmp= new PiecesCollector();

    QFile file(path);
    if(file.open( QIODevice::ReadOnly|QIODevice::Text)){
       QByteArray bytes = file.readAll();
       file.close();

       QJsonParseError jsonError;
       QJsonDocument document = QJsonDocument::fromJson(bytes,&jsonError);

       if(document.isNull()) qDebug()<<"Document is void";
       else {
           QJsonObject root = document.object();

           QJsonArray array = root.value("Pieces Collector").toArray();

           if(!(array.isEmpty())) {
               for(int i=0; i<array.size(); ++i){
                QJsonObject subobj = array[i].toObject();
                piece* foo= new piece();
                string n = subobj["name"].toString().toStdString();
                QString nq = QString::fromStdString(n);
                string b = subobj["brand"].toString().toStdString();
                QString bq = QString::fromStdString(b);
                string ps = subobj["price"].toString().toStdString();
                QString psq = QString::fromStdString(ps);
                psq.replace(",",".");
                double p=psq.toDouble();
                int j = subobj["jm"].toInt();
                int a = subobj["aj"].toInt();
                int s = subobj["js"].toInt();
                int o = subobj["od"].toInt();
                foo->setBrand(bq);
                foo->setName(nq);
                foo->setPrice(p);
                foo->setQtaPeriod(0,j);
                foo->setQtaPeriod(1,a);
                foo->setQtaPeriod(2,s);
                foo->setQtaPeriod(3,o);
                foo->updateQtaTot();
                foo->updateProfit();
                tmp->Add(*foo);
               }
           }
           else {
               piece* blank = new piece();
               blank->setBrand("");
               blank->setName("");
               blank->setPrice(0);
               blank->setQtaPeriod(0,0);
               blank->setQtaPeriod(1,0);
               blank->setQtaPeriod(2,0);
               blank->setQtaPeriod(3,0);
               tmp->Add(*blank);
           }
           return tmp;
       }
    }
    return 0;
}

void jsondata::writeJ(PiecesCollector* p, const QString& path){
    QJsonObject root;
    QJsonArray PC;
    QFile file(path);
    if(!file.open(QFile::WriteOnly|QFile::Text)){}

    for(int l=0;l<p->Size();++l){
        piece* tmp=p->getPiece(l);
        QString na=tmp->getName();
        QString br=tmp->getBrand();
        double pr=tmp->getPrice();
        QString trans=QString::number(pr);
        trans.replace(",",".");
        int jm=tmp->getQtaPerPeriod(0);
        int aj=tmp->getQtaPerPeriod(1);
        int js=tmp->getQtaPerPeriod(2);
        int od=tmp->getQtaPerPeriod(3);
        QJsonObject element;
        element["name"]=na;
        element["brand"]=br;
        element["price"]=trans;
        element["jm"]=jm;
        element["aj"]=aj;
        element["js"]=js;
        element["od"]=od;
        PC.push_back(element);
    }
    root["Pieces Collector"] = PC;
    QByteArray ba = QJsonDocument(root).toJson();
    QFile fout(path);
    fout.open(QIODevice::WriteOnly);
    fout.write(ba);
    file.close();
}
