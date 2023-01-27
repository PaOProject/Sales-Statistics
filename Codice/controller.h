#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"
#include "view.h"
#include "jsondata.h"

class controller: public QObject
{
    Q_OBJECT
private:
    view* View;
    model* Model;
public:
    explicit controller(QObject* parent =nullptr);
    ~controller();

    void setModel(model*);
    void setView(view*);

public slots:
    void openFile();
    void saveFile();
    void saveAsFile();

    void addRecord();
    void deleteRecords();
    void clearAll();

    void showBarChart();
    void showDonutChart();
    void showPointChart();
    void showLineChart();
    void showPieChart();
    void updateGraph();

    void setModelCollector();
};

#endif // CONTROLLER_H
