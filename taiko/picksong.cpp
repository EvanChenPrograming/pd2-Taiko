#include "picksong.h"
#include <QDebug>
#include <iostream>
using namespace std;
PickSong::PickSong()
{
    scene = new QGraphicsScene;


    QString line;
    QFile list(":/files/files/song_list.txt");
    if(!list.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",list.errorString());
    }
    QTextStream in(&list);
    while(!in.atEnd()){
        line=in.readLine();
        title.push_back(line);
        line=in.readLine();
        subtitle.push_back(line);
        line=in.readLine();
        diff.push_back(line);
        songs++;
    }
    QList<QString>::iterator ti;
    int i=0;
    for(ti=title.begin();ti<title.end()-1;ti++, i++){
        qDebug()<<title[i]<<" "<<subtitle[i]<<" "<<diff[i];
    }

}


void PickSong::show(){



}

void PickSong::left(){


}

void PickSong::right(){


}

QString PickSong::pick(){


}
