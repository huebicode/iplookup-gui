#include "widget.h"

#include <QApplication>
#include <QFile>

QString readTextFile(QString path){
    QFile file(path);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        return in.readAll();
    }
    return "";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString css = readTextFile(":/style.css");
    a.setStyleSheet(css);

    Widget w;
    w.show();
    return a.exec();
}
