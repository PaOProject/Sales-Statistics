#include "createrecord.h"

createrecord::createrecord(QObject* parent):QObject(parent){
    name=new QLineEdit();
    name->setText("");
    brand=new QLineEdit();
    brand->setText("");
    price=new QDoubleSpinBox();
    price->setValue(0.0);
    price->setAccelerated(true);
    soldpieces=new QLineEdit();
    soldpieces->setText("");
    soldpieces->setReadOnly(true);
    profit=new QLineEdit();
    profit->setText("");
    profit->setReadOnly(true);
    jm= new QSpinBox();
    jm->setValue(0);
    jm->setAccelerated(true);
    aj= new QSpinBox();
    aj->setValue(0);
    aj->setAccelerated(true);
    js= new QSpinBox();
    js->setValue(0);
    js->setAccelerated(true);
    od= new QSpinBox();
    od->setValue(0);
    od->setAccelerated(true);
    check= new QCheckBox();
    check->setChecked(false);
}

QLineEdit* createrecord::getName() const{ return name; }
QLineEdit* createrecord::getBrand() const{ return brand; }
QLineEdit* createrecord::getSoldPieces() const{ return soldpieces; }
QDoubleSpinBox* createrecord::getPrice() const{ return price; }
QLineEdit* createrecord::getProfit() const{ return profit; }
QSpinBox* createrecord::getJm() const { return jm; }
QSpinBox* createrecord::getAj() const { return aj; }
QSpinBox* createrecord::getJs() const { return js; }
QSpinBox* createrecord::getOd() const { return od; }
QCheckBox* createrecord::getCh() const{ return check; }

void createrecord::setName(QString a){ name->setText(a); }
void createrecord::setBrand(QString b){ brand->setText(b); }
void createrecord::setPrice(double p){ price->setValue(p); }
void createrecord::setSoldPieces(int i){ QString val=QString::number(i); soldpieces->setText(val); }
void createrecord::setProfit(double pr){ QString val=QString::number(pr); profit->setText(val); }
void createrecord::setJm(int u){ jm->setValue(u); }
void createrecord::setAj(int y){ aj->setValue(y); }
void createrecord::setJs(int z){ js->setValue(z); }
void createrecord::setOd(int j){ od->setValue(j); }
void createrecord::setCh(bool b){ check->setChecked(b);}
