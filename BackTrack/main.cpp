#include "backtrack.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BackTrack w;
    w.show();

    return a.exec();
}
