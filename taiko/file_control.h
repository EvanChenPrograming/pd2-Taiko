#ifndef FILE_CONTROL_H
#define FILE_CONTROL_H


#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMap>

class file_control
{
public:
    file_control();
    void songlist_init();
    void setSongPlay(QString);

    QMap<QString,int> map;
    QString TITLE,SUBTITLE,WAVE;
    /*int BPM,OFFSET,SONGVOL,SEVOL,DEMOSTART;
    int COURSE,LEVEL,BALLOON,SCOREINIT,SCOREDIFF;*/

};

#endif // FILE_CONTROL_H
