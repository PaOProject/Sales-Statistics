#include "view.h"
#include "model.h"
#include "controller.h"

#include <QApplication>
#include <QIcon>
#include <QDesktopWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Immagini/graphIcon(png).png"));
    a.setApplicationName("Sales & Statistics");
    view w;
    controller c;
    model m;
    c.setModel(&m);
    c.setView(&w);
    w.setController(&c);
#ifdef _WIN32
    w.setWindowState(Qt::WindowMaximized);
    w.setFixedSize(qApp->primaryScreen()->availableSize());
    w.show();
#elif __linux__
    w.showMaximized();
    w.adjustSize();
    w.setFixedSize(w.width(),w.height());
#endif
    return a.exec();
}
