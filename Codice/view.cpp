#include "view.h"
#include "controller.h"

void view::addMenus(QHBoxLayout* menuLayout){
    menuBar->addMenu(file);
    menuBar->addMenu(about);

    // Menu "File"
    QAction* Open = new QAction("Open", file);
    Open->setIcon(QIcon(":/Immagini/openFile.png"));
    QAction* Save = new QAction("Save", file);
    Save->setIcon(QIcon(":/Immagini/saveFile.png"));
    QAction* SaveAs = new QAction("Save As", file);
    SaveAs->setIcon(QIcon(":/Immagini/newFile.png"));
    file->addAction(Open);
    file->addAction(Save);
    file->addAction(SaveAs);

    //Menu "About"
    QAction* SystemInfo = new QAction("System information", about);
    SystemInfo->setIcon(QIcon(":/Immagini/systemInformation.png"));
    about->addAction(SystemInfo);

    connect(SystemInfo,SIGNAL(triggered()),this,SLOT(showSystemInformation()));

    menuLayout->addWidget(menuBar);
}

void view::addTableArea(QVBoxLayout* tableSpace){
    QHBoxLayout* tableHeadingLayout = new QHBoxLayout;
    QHBoxLayout* tableLayout = new QHBoxLayout;
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    QLineEdit* tableHeading = new QLineEdit("         SHOP SALES");
    tableHeading->setReadOnly(true);
    tableHeading->setFrame(false);
    tableHeading->setStyleSheet("font: bold ;background:#00000000; font-size: 18px; height: 48px; width: 120px; border: 5px ;");
    const QSize QLINE_SIZE = QSize(200, 30);
    tableHeading->setFixedSize(QLINE_SIZE);

    table = new createtable();
    table->setSortingEnabled(true);

    clearButton->setStyleSheet("font: bold ;");
    addRowButton->setStyleSheet("font: bold ;");
    deleteRowButton->setStyleSheet("font: bold ;");
    updateButton->setStyleSheet("font: bold ;");

    const QSize BUTTON_SIZE = QSize(200, 30);
    clearButton->setFixedSize(BUTTON_SIZE);
    addRowButton->setFixedSize(BUTTON_SIZE);
    deleteRowButton->setFixedSize(BUTTON_SIZE);
    updateButton->setFixedSize(BUTTON_SIZE);

    tableHeadingLayout->addWidget(tableHeading);
    tableLayout->addWidget(table);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(addRowButton);
    buttonLayout->addWidget(deleteRowButton);
    buttonLayout->addWidget(updateButton);

    tableHeadingLayout->setContentsMargins(150, 10, 150, 10);
    buttonLayout->setSpacing(50);
    buttonLayout->setContentsMargins(80, 20, 80, 20);

    tableSpace->addLayout(tableHeadingLayout);
    tableSpace->addLayout(tableLayout);
    tableSpace->addLayout(buttonLayout);
}

void view::addGraphsArea(QVBoxLayout* graphsSpace){
    QHBoxLayout* graphsSpaceButton = new QHBoxLayout;
    QHBoxLayout* spaceButtonDescription = new QHBoxLayout;

    showBarChart->setIcon(QIcon(":/Immagini/barChart.png"));
    showDonutChart->setIcon(QIcon(":/Immagini/donutChart.png"));
    showPointChart->setIcon(QIcon(":/Immagini/pointChart.png"));
    showLineChart->setIcon(QIcon(":/Immagini/lineChart.png"));
    showPieChart->setIcon(QIcon(":/Immagini/pieChart.png"));

    showBarChart->setToolTip("Show Bar Chart");
    showDonutChart->setToolTip("Show Donut Chart");
    showPointChart->setToolTip("Show Point Chart");
    showLineChart->setToolTip("Show Line Chart");
    showPieChart->setToolTip("Show Pie Chart");

    const QSize BUTTON_SIZE = QSize(62, 60);
    showBarChart->setFixedSize(BUTTON_SIZE);
    showBarChart->setIconSize(BUTTON_SIZE);
    showDonutChart->setFixedSize(BUTTON_SIZE);
    showDonutChart->setIconSize(BUTTON_SIZE);
    showPointChart->setFixedSize(BUTTON_SIZE);
    showPointChart->setIconSize(BUTTON_SIZE);
    showLineChart->setFixedSize(BUTTON_SIZE);
    showLineChart->setIconSize(BUTTON_SIZE);
    showPieChart->setFixedSize(BUTTON_SIZE);
    showPieChart->setIconSize(BUTTON_SIZE);

    graphsSpaceButton->addWidget(showBarChart);
    graphsSpaceButton->addWidget(showDonutChart);
    graphsSpaceButton->addWidget(showPointChart);
    graphsSpaceButton->addWidget(showLineChart);
    graphsSpaceButton->addWidget(showPieChart);

    graphsSpaceButton->setSpacing(50);
    graphsSpaceButton->setAlignment(Qt::AlignCenter);
    graphsSpaceButton->setContentsMargins(50, 50, 50, 10);

    // inserimento grafico di default
    QVector<createrecord*> v;
    linechart* g = new linechart();
    displayedGraph = g->displayLineChart(v,graphsSpaceArea);
    checkGraph=g;
    graphsSpaceArea->setContentsMargins(30, 20, 40, 60);
    graphsSpaceArea->addWidget(g);

    graphsSpaceArea->setAlignment(Qt::AlignCenter);

    graphsSpace->addLayout(graphsSpaceButton);
    graphsSpace->addLayout(spaceButtonDescription);
    graphsSpace->addLayout(graphsSpaceArea);
}

view::view(QWidget* parent) : QWidget(parent), menuBar(new QMenuBar(this)), file(new QMenu("File", menuBar)), about(new QMenu("About", menuBar)), clearButton(new QPushButton ("Clear")), addRowButton(new QPushButton("Add Row")), deleteRowButton(new QPushButton("Delete Row")), updateButton(new QPushButton("Update Graph")), graphsSpaceArea(new QHBoxLayout), showBarChart(new QPushButton()), showDonutChart(new QPushButton()), showPointChart(new QPushButton()), showLineChart(new QPushButton()), showPieChart(new QPushButton()), filePath(""), checkGraph(nullptr), displayedGraph(nullptr){
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* menuLayout = new QHBoxLayout;
    QHBoxLayout* mainScreen = new QHBoxLayout;
    QVBoxLayout* tableSpace = new QVBoxLayout;
    QVBoxLayout* graphsSpace = new QVBoxLayout;

    addMenus(menuLayout);
    addTableArea(tableSpace);
    addGraphsArea(graphsSpace);

    mainScreen->addLayout(tableSpace);
    mainScreen->addLayout(graphsSpace);
    mainLayout->addLayout(menuLayout);
    mainLayout->addLayout(mainScreen);

    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),table,SLOT(updateTable()));
    timer->start(3000);
}

view::~view(){ delete displayedGraph; }

createtable* view::getTable() const{
    return table;
}

QHBoxLayout* view::getGraphsSpaceArea() const{
    return graphsSpaceArea;
}

void view::importedData(PiecesCollector* p){
    table->importedData(p);
}

QString view::getFilePath() const{ return filePath; }

void view::setController(controller* c) {
    control = c;

    connect(file->actions()[0], SIGNAL(triggered()), control, SLOT(openFile()));
    connect(file->actions()[1], SIGNAL(triggered()), control, SLOT(saveFile()));
    connect(file->actions()[2], SIGNAL(triggered()), control, SLOT(saveAsFile()));

    connect(addRowButton,SIGNAL(clicked()),control,SLOT(addRecord()));
    connect(deleteRowButton,SIGNAL(clicked()),control,SLOT(deleteRecords()));
    connect(clearButton,SIGNAL(clicked()),control,SLOT(clearAll()));
    connect(updateButton,SIGNAL(clicked()),control,SLOT(updateGraph()));

    connect(showBarChart,SIGNAL(clicked()),control,SLOT(showBarChart()));
    connect(showDonutChart,SIGNAL(clicked()),control,SLOT(showDonutChart()));
    connect(showPointChart,SIGNAL(clicked()),control,SLOT(showPointChart()));
    connect(showLineChart,SIGNAL(clicked()),control,SLOT(showLineChart()));
    connect(showPieChart,SIGNAL(clicked()),control,SLOT(showPieChart()));
}

void view::showSystemInformation() const{
    QString generalInfo = "Software Version: 1.0 ";
    QString developersInfo = "  Developed by M&M";
    QDialog* dialog = new QDialog();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    dialog->setFixedSize(QSize(200,200));

    dialog->setLayout(new QVBoxLayout);
    dialog->layout()->addWidget(new QLabel(generalInfo,dialog));
    dialog->layout()->addWidget(new QLabel(developersInfo,dialog));
    dialog->layout()->setAlignment(Qt::AlignCenter);

    dialog->move(x() + 850, y() + 400);
    dialog->show();
}

void view::openFileDialog() {
    QString filter = " JSON file (*.json)";
    QString filePathTMP;
    filePathTMP = QFileDialog::getOpenFileName(this, tr("Open a file"), QDir::homePath(), filter);

    if(filePathTMP == "") qDebug()<<"No file selected";
    else filePath=filePathTMP;

    QFile file(filePathTMP);

    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","file not open");
    }

    file.close();
}

void view::openSaveAsDialog(){
    QString filter = " JSON file (*.json)";
    QString filePathTMP = filePath;
    filePath = QFileDialog::getSaveFileName(this, tr("Save As"), QDir::currentPath(), filter);

    if(filePath == ""){
        QMessageBox::warning(this,"Warning","file not selected");
        filePath=filePathTMP;
    }
    QFile file(filePath);
    file.close();
}

void view::setDisplayedGraph(graph* g){
    delete displayedGraph;
    displayedGraph = g;
}

void view::setCheckGraph(graph* g){
    checkGraph = g;
}

graph* view::getCheckGraph() const{
    return checkGraph;
}

graph* view::getDisplayedGraph() const{
    return displayedGraph;
}

QVector<createrecord*> view::getTableRecords() const{
    return table->getRecords();
}

void view::addTableRecord(){
    table->addRow();
}

void view::deleteTableRecords(){
    table->deleteRow();
}

void view::clear(){
    table->clearTable();
}

bool view::recordCheck(QVector<createrecord*> v, graph* g) const{
    int i=0;
    bool lineChartCheck = true, barChartCheck = true, donutChartCheck=true, pieChartCheck=true, pointChartCheck=true;
    for(QVector<createrecord*>::const_iterator cit=v.begin();cit!=v.end();++cit){
        if((*cit)->getBrand()->text()=="") { donutChartCheck=false; barChartCheck=false; }
        if((*cit)->getPrice()->value()==0.0) barChartCheck=false;
        if((*cit)->getSoldPieces()->text().toInt()==0) barChartCheck=false;
        i++;
    }
    pieChartCheck=donutChartCheck;
    if(i<2) lineChartCheck=false;
    if(i<1) donutChartCheck=false;
    pointChartCheck=lineChartCheck;
    if(dynamic_cast<barchart*>(g)) return barChartCheck;
    else if(dynamic_cast<donutchart*>(g)) return donutChartCheck;
    else if(dynamic_cast<pointchart*>(g)) return pointChartCheck;
    else if(dynamic_cast<linechart*>(g)) return lineChartCheck;
    else return pieChartCheck;
}

void view::showErrorMessage(const QString& errorMessage) const{
    QMessageBox::warning(const_cast<view*>(this),"Warning",errorMessage);
}

PiecesCollector* view::extractData() {
    QVector<createrecord*> tmp = table->getRecords();
    PiecesCollector* tmpar = new PiecesCollector();
    piece* tmpiece = new piece();
    for(int i=0;i<table->getRecords().size();++i){
        string n=tmp[i]->getName()->text().toStdString();
        QString nn = QString::fromStdString(n);
        tmpiece->setName(nn);
        string b=tmp[i]->getBrand()->text().toStdString();
        QString nb = QString::fromStdString(b);
        tmpiece->setBrand(nb);
        double pr=tmp[i]->getPrice()->value();
        tmpiece->setPrice(pr);
        int jm=tmp[i]->getJm()->text().toInt();
        tmpiece->setQtaPeriod(0,jm);
        int aj=tmp[i]->getAj()->text().toInt();
        tmpiece->setQtaPeriod(1,aj);
        int js=tmp[i]->getJs()->text().toInt();
        tmpiece->setQtaPeriod(2,js);
        int od=tmp[i]->getOd()->text().toInt();
        tmpiece->setQtaPeriod(3,od);
        tmpiece->updateQtaTot();
        tmpiece->updateProfit();
        tmpar->Add(*(new piece(*tmpiece)));
    }
    delete tmpiece;
    return tmpar;
}
