#ifndef SCENE_H
#define SCENE_H


#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QSound>
#include <QKeyEvent>
#include <QLabel>
#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsSimpleTextItem>
#include "file_control.h"

#include <QDebug>
#include <iostream>
using namespace std;

class Scene : public QGraphicsScene
{
public:
    Scene();
    void keyPressEvent(QKeyEvent *event);


    void setbg_0();
    void setbg_1();
    void unsetbg_1();
    void setbg_2();
    void unsetbg_2();
    void setbg_3();
    void unsetbg_3();

    //picksong
    void showscene1();
    void scene1left();
    void scene1right();

    //setting
    void nowOn();
    void checked();



private:
    QString song;
    QSound *op, *dong, *ka;
    QGraphicsPixmapItem *a,*b,*c;
    int SceneMode=0;//0=start 1=pick music 2=setting
                    //3=playing 4=after play

    //picksong
    int songs=0, picked=0,s=1;
    QGraphicsSimpleTextItem *text0,*text1,*text2;
    QList<QString> title,subtitle;

    //setting
    QGraphicsPixmapItem *d;
    int now_on=0;
    int difficulty=1;//
    bool setRandom=false;
    bool setHidden=false;
    bool setAuto=false;
    QString changeDong=":/sound/dong.wav";
    QString changeKa=":/sound/ka.wav";

    //play
    file_control *Map;
    QSound *track;




    int leftBound;
    int rightBound;

};

#endif // SCENE_H
