#ifndef PIECE_H
#define PIECE_H

#include <QString>

class piece
{
private:
    QString name;
    QString brand;
    double price;
    int qtaTot;
    int profit;
    int* months; // vettore di dimensione statica=4, dove ogni cella indica le quantità vendute nel rispettivo trimestre
    static const int size;

public:
    piece(QString = "",QString = "",double = 0.0,int = 0,int = 0);
    piece(const piece&);
    ~piece();
    piece& operator=(const piece&);
    bool operator==(const piece&) const;
    bool operator!=(const piece&) const;


    QString getName() const;
    QString getBrand() const;
    double getPrice() const;
    int getQtaTot() const;
    int getProfit() const;
    int getQtaPerPeriod(int) const;

    void setName(QString);
    void setBrand(QString);
    void setPrice(double);
    void setQtaPeriod(int,int);

    void updateQtaTot();
    void updateProfit();


};


#endif // PIECE_H
