#include "piece.h"

piece::~piece() { if(months) delete[] months; }

piece::piece(QString x, QString y, double p, int q, int r): name(x), brand(y), price(p), qtaTot(q), profit(r), months(new int[piece::size]){
    for(int i=0;i<size;++i) months[i]=0;
}

piece::piece(const piece& p): name(p.name), brand(p.brand), price(p.price), qtaTot(p.qtaTot), profit(p.profit), months(new int[piece::size]){
    for(int i=0;i<piece::size;i++) months[i]=p.months[i];
}

piece& piece::operator=(const piece& other){
    if(this!=&other){
        delete[] months;
        months = new int[piece::size];
        for(int i=0;i<size;i++) months[i]=other.months[i];
    }
    return *this;
}

bool piece::operator==(const piece& other)const {
    return name==other.name && brand==other.brand && price==other.price;
}

bool piece::operator!=(const piece& other)const {
    return !(name==other.name && brand==other.brand && price==other.price);
}

int piece::getQtaPerPeriod(int i) const{ return months[i]; }
QString piece::getName() const{ return name; }
QString piece::getBrand() const{ return brand; }
double piece::getPrice() const{ return price; }
int piece::getQtaTot() const{ return qtaTot; }
int piece::getProfit() const{ return profit; }

void piece::setName(QString a){ name=a; }
void piece::setBrand(QString b){ brand=b; }
void piece::setPrice(double c){ price=c;}
void piece::setQtaPeriod(int i,int newQta){ months[i]=newQta; }

void piece::updateQtaTot(){
    int sum =0;
    for(int i=0;i<size;++i) sum+=months[i];
    qtaTot=sum;
}

void piece::updateProfit(){
    profit=qtaTot*price;
}

const int piece::size=4;
