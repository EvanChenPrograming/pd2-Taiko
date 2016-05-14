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
#include <QMediaPlayer>
#include <QTimer>
#include <QObject>
#include <QChar>
#include <QElapsedTimer>
#include "file_control.h"
#include "notes.h"


#include <QDebug>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
using namespace std;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


    void setbg_0();
    void setbg_1();
    void unsetbg_1();
    void setbg_2();
    void unsetbg_2();
    void setbg_3();
    void unsetbg_3();
    void setbg_4();
    void unsetbg_4();

    //picksong
    void showscene1();
    void scene1left();
    void scene1right();

    //setting
    void nowOn();
    void checked();

    //play
    void setMap();
    void startPlay();
    void eliminate(int);
    void playSeiseki();

public slots:
    void Generate();
    void Move();
    void Auto();
    void startWave();
    void stopWait();
    void endPlay();
    void secondsLeft();

    //animation
    /*void playRdong();
    void playLdong();
    void playRka();
    void playLka();
*/
    void GenGreat();
    void GenGood();
    void GenMiss();
    void moveJudgement();
    void ShowCombo();
    void GenExplode();
    void RemoveExplode();
    void ShowScore();
    void DanceAndJump();

signals:
    void Great();
    void Good();
    void Miss();
    void Explode();
    void Combo();
    void Score();




private:
    QString song;
    QSound *op, *dong, *ka;
    QGraphicsPixmapItem *a,*b,*c;
    int screenMode=0;//0=start 1=pick music 2=setting
                    //3=playing 4=after play

    //picksong
    int songs=0,s=1;
    QGraphicsSimpleTextItem *text0,*text1,*text2;
    QList<QString> title,subtitle;

    //setting
    QGraphicsPixmapItem *d,*st,*picked_background_r,*picked_background_3,*picked_background_a;
    QGraphicsPixmapItem *arrow,*icon_rand,*icon_30sec,*icon_auto;
    int now_on=0;
    int difficulty=1;//
    bool setRandom=false;
    bool setHidden=false;
    bool setAuto=false;
    bool set30secMode=false;

    //play
    QGraphicsPixmapItem *e,*randomTag,*countdownTag,*autoTag;
    file_control Map;
    QMediaPlayer *track;
    QList<QSound *> comTrack;
    int VOL=70,p=0;
    QTimer *timer,*timer1,*timer2,*timer3,*countdown;
    QElapsedTimer *Etimer;
    QList<notes *> list;
    //QList<QGraphicsPixmapItem *> numbers;
    QStringList songMap;
    int great=0,good=0,miss=0,score=0,combo=0,maxcombo=0;
    int soul=0;//48pass 63full
    int notesGen=0;
    int firstlayer=1,secondlayer=0;
    float BPM;
    int msec,test;
    int waitfor;
    int secLeft=30;

    //animation
    QTimer *soundTimer,*AniTimer1,*AniTimer2,*AniTimer3;
    QList<QGraphicsPixmapItem *> Judge;
    QList<QGraphicsPixmapItem *> expl;
    QPixmap ex1;
    QPixmap numberPic[10];
    QPixmap ctdnumberPic[10];
    QPixmap scorenumberPic[10];
    QList<QGraphicsPixmapItem *> numbers,ctdnumbers,scorenumbers;
    QPixmap dancePic[10];
    QList<QGraphicsPixmapItem *> dancers;

    //result
    QSound *seiseki,*fullcombo;
    bool passed=true;




};

#endif // SCENE_H
