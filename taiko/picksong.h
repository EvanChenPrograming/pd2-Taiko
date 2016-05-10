#ifndef PICKSONG_H
#define PICKSONG_H

#include <QList>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>

class PickSong
{
public:
    PickSong();

    void show();

    void left();
    void right();
    QString pick();

private:
    QGraphicsScene scene;
    int songs=0, picked=0;
    QGraphicsSimpleTextItem *text0,*text1,*text2;
    QList<QString> title,subtitle,diff;

};

#endif // PICKSONG_H
