#include "createtable.h"

createtable::createtable(QWidget *parent): QTableWidget(parent){
    setColumnCount(10);
    QStringList texts;
    texts<<"Name"<<"Brand"<<"Price"<<"Sold pieces"<<"Tot Profit"<<"January-March"<<"April-June"<<"July-September"<<"October-December"<<"Selected";
    setHorizontalHeaderLabels(texts);
    setColumnWidth(0,200);
    resizeColumnToContents(5);
    resizeColumnToContents(7);
    resizeColumnToContents(8);
    setRowCount(1);
    createrecord* elem = new createrecord();
    records.push_back(elem);
    setCellWidget(0,0,elem->getName());
    setCellWidget(0,1,elem->getBrand());
    setCellWidget(0,2,elem->getPrice());
    setCellWidget(0,3,elem->getSoldPieces());
    setCellWidget(0,4,elem->getProfit());
    setCellWidget(0,5,elem->getJm());
    setCellWidget(0,6,elem->getAj());
    setCellWidget(0,7,elem->getJs());
    setCellWidget(0,8,elem->getOd());
    QWidget* checkBoxWidget= new QWidget();
    QHBoxLayout* layoutCheckBox=new QHBoxLayout(checkBoxWidget);
    layoutCheckBox->addWidget(elem->getCh());
    layoutCheckBox->setAlignment(Qt::AlignCenter);
    layoutCheckBox->setContentsMargins(0,0,0,0);
    setCellWidget(0,9,checkBoxWidget);
}


createtable::~createtable(){}

QVector<createrecord*> createtable::getRecords() const{
    return records;
}

void createtable::addRow() {
    setRowCount(rowCount()+1);
    createrecord* elem = new createrecord();
    records.push_back(elem);
    setCellWidget(rowCount()-1,0,elem->getName());
    setCellWidget(rowCount()-1,1,elem->getBrand());
    setCellWidget(rowCount()-1,2,elem->getPrice());
    setCellWidget(rowCount()-1,3,elem->getSoldPieces());
    setCellWidget(rowCount()-1,4,elem->getProfit());
    setCellWidget(rowCount()-1,5,elem->getJm());
    setCellWidget(rowCount()-1,6,elem->getAj());
    setCellWidget(rowCount()-1,7,elem->getJs());
    setCellWidget(rowCount()-1,8,elem->getOd());
    QWidget* checkBoxWidget = new QWidget();
    QHBoxLayout* layoutCheckBox = new QHBoxLayout(checkBoxWidget);
    layoutCheckBox->addWidget(elem->getCh());
    layoutCheckBox->setAlignment(Qt::AlignCenter);
    layoutCheckBox->setContentsMargins(0,0,0,0);
    setCellWidget(rowCount()-1,9,checkBoxWidget);
}

void createtable::deleteRow() {
    int count=0;
    QVector<int> deletedRecord;
    for(QVector<createrecord*>::const_iterator cit=records.begin();cit!=records.end();++cit){
        if(!((*cit)->getCh()->checkState())) count +=1;
    }
    if(count==records.size()) {
        QDialog* dialog = new QDialog();
        dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
        dialog->setFixedSize(QSize(420,150));

        dialog->setLayout(new QVBoxLayout);
        QString s1="Before deleting a row, you have\n", s2="   to select one from the table";
        dialog->layout()->addWidget(new QLabel(s1+s2,dialog));
        dialog->layout()->setAlignment(Qt::AlignCenter);
        QFont text("Times", 9, QFont::Cursive);
        dialog->setFont(text);

        dialog->move(x() + 750, y() + 350);
        dialog->show();
    }else {
        int n=0;
        for(QVector<createrecord*>::iterator it=records.begin();it!=records.end();++it){
            if((*it)->getCh()->checkState()){
                records.erase(it);
                removeRow(n);
                --it;
                n--;
            }
            n++;
        }
    }
}

void createtable::clearTable(){
    records.clear();
    setRowCount(1);
    createrecord* elem = new createrecord();
    records.push_back(elem);
    setCellWidget(0,0,elem->getName());
    setCellWidget(0,1,elem->getBrand());
    setCellWidget(0,2,elem->getPrice());
    setCellWidget(0,3,elem->getSoldPieces());
    setCellWidget(0,4,elem->getProfit());
    setCellWidget(0,5,elem->getJm());
    setCellWidget(0,6,elem->getAj());
    setCellWidget(0,7,elem->getJs());
    setCellWidget(0,8,elem->getOd());
    QWidget* checkBoxWidget= new QWidget();
    QHBoxLayout* layoutCheckBox=new QHBoxLayout(checkBoxWidget);
    layoutCheckBox->addWidget(elem->getCh());
    layoutCheckBox->setAlignment(Qt::AlignCenter);
    layoutCheckBox->setContentsMargins(0,0,0,0);
    setCellWidget(0,9,checkBoxWidget);
}

void createtable::updateTable(){
    for(QVector<createrecord*>::iterator it=records.begin();it!=records.end();++it){
        (*it)->setName(QString::fromStdString((*it)->getName()->text().toStdString()));
        (*it)->setBrand(QString::fromStdString((*it)->getBrand()->text().toStdString()));
        (*it)->setPrice((*it)->getPrice()->value());
        (*it)->setJm((*it)->getJm()->value());
        (*it)->setAj((*it)->getAj()->value());
        (*it)->setJs((*it)->getJs()->value());
        (*it)->setOd((*it)->getOd()->value());
        (*it)->setSoldPieces((*it)->getOd()->value()+(*it)->getJs()->value()+(*it)->getAj()->value()+(*it)->getJm()->value());
        (*it)->setProfit((*it)->getSoldPieces()->text().toInt()*(*it)->getPrice()->value());
    }
}

void createtable::importedData(PiecesCollector*p){
    setRowCount(p->Size());
    records.clear();
    for(int i=0;i<p->Size();++i){
        createrecord* elem=new createrecord();
        elem->setName(p->getPiece(i)->getName());
        elem->setBrand(p->getPiece(i)->getBrand());
        elem->setPrice(p->getPiece(i)->getPrice());
        elem->setSoldPieces(p->getPiece(i)->getQtaTot());
        elem->setProfit(p->getPiece(i)->getProfit());
        elem->setJm(p->getPiece(i)->getQtaPerPeriod(0));
        elem->setAj(p->getPiece(i)->getQtaPerPeriod(1));
        elem->setJs(p->getPiece(i)->getQtaPerPeriod(2));
        elem->setOd(p->getPiece(i)->getQtaPerPeriod(3));
        records.push_back(elem);
        setCellWidget(i,0,elem->getName());
        setCellWidget(i,1,elem->getBrand());
        setCellWidget(i,2,elem->getPrice());
        setCellWidget(i,3,elem->getSoldPieces());
        setCellWidget(i,4,elem->getProfit());
        setCellWidget(i,5,elem->getJm());
        setCellWidget(i,6,elem->getAj());
        setCellWidget(i,7,elem->getJs());
        setCellWidget(i,8,elem->getOd());
        QWidget* checkBoxWidget= new QWidget();
        QHBoxLayout* layoutCheckBox=new QHBoxLayout(checkBoxWidget);
        layoutCheckBox->addWidget(elem->getCh());
        layoutCheckBox->setAlignment(Qt::AlignCenter);
        layoutCheckBox->setContentsMargins(0,0,0,0);
        setCellWidget(i,9,checkBoxWidget);
    }
}
