#ifndef CREATETABLE_H
#define CREATETABLE_H

#include "createrecord.h"
#include <QObject>
#include <QTableWidget>
#include "QVector"
#include <QSize>
#include <QHBoxLayout>
#include <QStringList>
#include <QDialog>
#include <QLabel>

class createtable : public QTableWidget
{
    Q_OBJECT
private:
    QVector<createrecord*> records;
public:
    createtable(QWidget* parent = 0);
    ~createtable();
    QVector<createrecord*> getRecords() const;
    void importedData(PiecesCollector*);
    void addRow();
    void deleteRow();
    void clearTable();

public slots:
    void updateTable();
};

#endif // CREATETABLE_H
