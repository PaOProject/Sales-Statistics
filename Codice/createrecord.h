#ifndef CREATERECORD_H
#define CREATERECORD_H

#include <QObject>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include "piecescollector.h"
#include <QCheckBox>

class createrecord : public QObject
{
    Q_OBJECT
private:
    QLineEdit* name;
    QLineEdit* brand;
    QDoubleSpinBox* price;
    QLineEdit* soldpieces;
    QLineEdit* profit;
    QSpinBox* jm; //january-march
    QSpinBox* aj; //april-june
    QSpinBox* js; //july-september
    QSpinBox* od; //october-december
    QCheckBox* check;
public:
    createrecord(QObject* =0);

    QLineEdit* getName() const;
    QLineEdit* getBrand() const;
    QLineEdit* getSoldPieces() const;
    QDoubleSpinBox* getPrice() const;
    QLineEdit* getProfit() const;
    QSpinBox* getJm() const;
    QSpinBox* getAj() const;
    QSpinBox* getJs() const;
    QSpinBox* getOd() const;
    QCheckBox* getCh() const;

    void setName(QString);
    void setBrand(QString);
    void setPrice(double);
    void setSoldPieces(int);
    void setProfit(double);
    void setJm(int);
    void setAj(int);
    void setJs(int);
    void setOd(int);
    void setCh(bool);
};

#endif // CREATERECORD_H
