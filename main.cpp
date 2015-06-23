
#include <QtGui>
#include <stdio.h>
#include <QtDebug>
#include <QObject>

#include "BitEdit.h"
#include "FloatingHexEdit.h"
#include "BitCalculator.h"



int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    BitCalculator window;

    window.setWindowFlags(window.windowFlags()|Qt::WindowStaysOnTopHint);
//    window.hide();

    return app.exec();
}
