#include "scene.h"
Scene::Scene()
{
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
        songs++;
    }
   /* QList<QString>::iterator ti;
    int i=0;
    for(ti=title.begin();ti==title.end();ti++, i++){
        qDebug()<<title[i]<<" "<<subtitle[i];
    }*/


}

void Scene::keyPressEvent(QKeyEvent *key){
    dong = new QSound(":/sound/dong.wav");
    ka = new QSound(":/sound/ka.wav");
    op = new QSound(":/sound/opening.wav");

    track = new QSound("../taiko/voice_50combo.wav");

    int out=0;

    if(SceneMode==0){
        setbg_0();
        if(key->key()==Qt::Key_J || key->key()==Qt::Key_F){
            dong->play();
            op->play();
            SceneMode = 1;
            setbg_1();
            showscene1();
        }
        if(key->key()==Qt::Key_D || key->key()==Qt::Key_K){
            ka->play();
        }
        if(key->key()==Qt::Key_Escape){
            exit(1);
        }
    }
    else if(SceneMode==1){
        if(key->key()==Qt::Key_D){
            ka->play();
            scene1left();
        }
        if(key->key()==Qt::Key_K){
            ka->play();
            scene1right();
        }
        if(key->key()==Qt::Key_J || key->key()==Qt::Key_F){
            dong->play();
            SceneMode=2;
            unsetbg_1();
            setbg_2();
        }
        if(key->key()==Qt::Key_Escape){
            SceneMode=0;
            unsetbg_1();
            setbg_0();
        }
    }
    else if(SceneMode==2){
        if(key->key()==Qt::Key_D){
            ka->play();
            now_on-=1;
            nowOn();

        }
        if(key->key()==Qt::Key_K){
            ka->play();
            now_on+=1;
            nowOn();
        }
        if(key->key()==Qt::Key_J || key->key()==Qt::Key_F){
            dong->play();
            checked();
        }

        if(key->key()==Qt::Key_Escape){
            unsetbg_2();
            SceneMode=1;
            setbg_1();
            showscene1();
        }
    }
    else if(SceneMode==3){
        if(key->key()==Qt::Key_J || key->key()==Qt::Key_F){
            dong->play();
            track->play();
        }
        if(key->key()==Qt::Key_D || key->key()==Qt::Key_K){
            ka->play();
        }
        if(key->key()==Qt::Key_Escape){
            out++;
            if(out==1){

            }
            else if(out==2){

            }
        }
    }
}


void Scene::setbg_0(){
    QImage bg;
    bg.load(":/pics/open.jpg");
    bg = bg.scaled(770,400);
    this->setBackgroundBrush(bg);
}
void Scene::setbg_1(){
    QImage bg;
    bg.load(":/pics/selecting_song.jpg");
    bg = bg.scaled(770,420);
    this->setBackgroundBrush(bg);

    int x=50,y=100;
    a = new QGraphicsPixmapItem;
    b = new QGraphicsPixmapItem;
    c = new QGraphicsPixmapItem;
    QPixmap song_bg,song_bg_select;
    song_bg.load(":/pics/song_bg.png");
    song_bg = song_bg.scaled(700,50);
    song_bg_select.load(":/pics/song_bg_select.png");
    song_bg_select = song_bg_select.scaled(700,100);
    a->setPixmap(song_bg);
    a->setPos(x,y);
    b->setPixmap(song_bg_select);
    b->setPos(x,y+50);
    c->setPixmap(song_bg);
    c->setPos(x,y+150);
    addItem(a);
    addItem(b);
    addItem(c);
}
void Scene::unsetbg_1(){
    removeItem(text0);
    removeItem(text1);
    removeItem(text2);
    removeItem(a);
    removeItem(b);
    removeItem(c);
}
void Scene::setbg_2(){
    QImage bg;
    bg.load(":/pics/song_picked.jpg");
    bg = bg.scaled(770,400);
    this->setBackgroundBrush(bg);
    d = new QGraphicsPixmapItem;
    QPixmap diff;
    diff.load(":/pics/difficulty.png");
    diff = diff.scaled(900,400);
    d->setPixmap(diff);
    addItem(d);
    if (s==-1){
        s=songs-1;
    }
    else if(s==-2){
        s=songs-3;
    }
    else if(s==songs){
        s=0;
    }
    else if(s==songs+1){
        s=1;
    }
    text1->setText(" "+title[s]+"  "+subtitle[s]);
    text1->setPos(170,25);
    addItem(text1);
}
void Scene::unsetbg_2(){
    removeItem(text1);
    removeItem(d);
}
void Scene::setbg_3(){

    //Map = new file_control;
    //Map->setSongPlay();

}
void Scene::unsetbg_3(){

}

void Scene::showscene1(){
    int x=50,y=100,i,j,k;
    if(s==0){
        i=songs-1;
        j=0;k=1;
    }
    else if (s==-1){
        i=songs-2;
        j=songs-1;
        k=0;
    }
    else if(s==-2){
        s=songs-3;
        i=s-1;j=s;k=s+1;
    }
    else if(s==songs-1){
        i=s-1;j=s;k=0;
    }
    else if(s==songs){
        i=s-1;j=0;k=1;
    }
    else if(s==songs+1){
        s=1;
        i=s-1;j=s;k=s+1;
    }
    else {
        i=s-1;j=s;k=s+1;
    }

    QFont unselect("Courier", 24),select("Courier", 24);

    text0 = new QGraphicsSimpleTextItem;
    text1 = new QGraphicsSimpleTextItem;
    text2 = new QGraphicsSimpleTextItem;

    text0->setText(" "+title[i]+"  "+subtitle[i]);
    text0->setFont(unselect);
    text0->setPos(x,y+5);
    addItem(text0);

    text1->setText(" "+title[j]+"\n"+subtitle[j]);
    text1->setFont(select);
    text1->setPos(x,y+55);
    addItem(text1);

    text2->setText(" "+title[k]+"  "+subtitle[k]);
    text2->setFont(unselect);
    text2->setPos(x,y+155);
    addItem(text2);
}

void Scene::scene1left(){
    removeItem(text0);
    removeItem(text1);
    removeItem(text2);
    s-=1;
    showscene1();
}

void Scene::scene1right(){
    removeItem(text0);
    removeItem(text1);
    removeItem(text2);
    s+=1;
    showscene1();
}


void Scene::nowOn(){
    removeItem(d);
    removeItem(text1);
    QString now,s,e,n,h,ex;
    s=":/pics/difficulty.png";
    e=":/pics/difficulty_easy.png";
    n=":/pics/difficulty_normal.png";
    h=":/pics/difficulty_hard.png";
    ex=":/pics/difficulty_extrem.png";
    QPixmap diff;
    if(now_on==-1){
        now_on=4;
        now=ex;
    }
    else if(now_on==0){
        now=s;
    }
    else if(now_on==1){
        now=e;
    }
    else if(now_on==2){
        now=n;
    }
    else if(now_on==3){
        now=h;
    }
    else if(now_on==4){
        now=ex;
    }
    else {
        now_on=0;
        now=s;
    }
    diff.load(now);
    diff = diff.scaled(900,400);
    d->setPixmap(diff);
    addItem(d);
    addItem(text1);

}

void Scene::checked(){
    if(now_on==0)return;
    else{
        difficulty=now_on;
        SceneMode=3;
        unsetbg_2();
        setbg_3();
    }

}
