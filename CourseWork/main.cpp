#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QLibraryInfo>
#include <QSplashScreen>
#include <QTime>
#include <QPainter>

void LoadModules(QSplashScreen* psplash){
    QTime time;
    time.start();
    for(int i=0; i<100 ; ){
        if(time.elapsed() > 40){
            time.start();
            ++i;
        }
        psplash->showMessage("Loading modules: " + QString::number(i)+"%", Qt::AlignRight | Qt::AlignTop, Qt::green);
        qApp->processEvents();

    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QSplashScreen splash(QPixmap(":/images/load.jpg"));
    splash.show();
    LoadModules(&splash);
    splash.finish(&w);
    w.show();

    return a.exec();
}
