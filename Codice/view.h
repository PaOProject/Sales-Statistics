#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QVBoxLayout>
#include <QIcon>
#include <QInputDialog>
#include <QFileDialog>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "QTimer"

#include "createtable.h"
#include "linechart.h"
#include "piechart.h"
#include "donutchart.h"
#include "pointchart.h"
#include "barchart.h"

class controller;

class view : public QWidget {
    Q_OBJECT

private:
    controller* control;

    QMenuBar* menuBar;
    QMenu* file;
    QMenu* about;

    createtable* table;
    QPushButton* clearButton;
    QPushButton* addRowButton;
    QPushButton* deleteRowButton;
    QPushButton* updateButton;

    QHBoxLayout* graphsSpaceArea;

    QPushButton* showBarChart;
    QPushButton* showDonutChart;
    QPushButton* showPointChart;
    QPushButton* showLineChart;
    QPushButton* showPieChart;

    QString filePath;

    graph* checkGraph;
    graph* displayedGraph;

    void addMenus(QHBoxLayout* menuLayout);
    void addTableArea(QVBoxLayout* tableSpace);
    void addGraphsArea(QVBoxLayout* graphsSpace);

public:
    explicit view(QWidget* parent = nullptr);
    ~view();
    createtable* getTable() const;
    QHBoxLayout* getGraphsSpaceArea() const;
    void importedData(PiecesCollector*);
    QString getFilePath() const;
    void setController(controller*);
    PiecesCollector* extractData();
    void openFileDialog();
    void openSaveAsDialog();
    void setDisplayedGraph(graph*);
    void setCheckGraph(graph*);
    graph* getCheckGraph() const;
    graph* getDisplayedGraph() const;
    QVector<createrecord*> getTableRecords() const;
    void addTableRecord();
    void deleteTableRecords();
    void clear();
    bool recordCheck(QVector<createrecord*>,graph*) const;
    void showErrorMessage(const QString&) const;

public slots:
    void showSystemInformation() const;
};

#endif // VIEW_H
