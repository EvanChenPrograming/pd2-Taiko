#ifndef FILE_CONTROL_H
#define FILE_CONTROL_H


#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMap>
#include <QDir>
#include <QStringList>
#include <QTextCodec>
#include <ctime>
#include <cstdlib>


#include <QDebug>
#include <iostream>
using namespace std;

class file_control
{
public:
    file_control();
    void songlist_init();
    void setSongPlay(QString);
    void getStar(QString);
    void getMap(QString,int);
    QString getSubtitle(QString);

    void convert(bool);

    QDir dir;
    //QString path="/";
    QString path="/Users/Evan/Documents/fresh_2sem/pd2/gitHWs/pd2-Taiko/";
    QMap<QString,float> map;
    QStringList songMap;
    QString TITLE,SUBTITLE,WAVE,trackPath;
    int star[4];  //0=easy 1=normal 2=hard 3=oni
    /*int BPM,OFFSET,SONGVOL,SEVOL,DEMOSTART;
    int COURSE,LEVEL,BALLOON,SCOREINIT,SCOREDIFF;*/

};

#endif // FILE_CONTROL_H
