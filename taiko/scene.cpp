#include "scene.h"
Scene::Scene()
{
    Map.songlist_init();
    QString line;
    QFile list("/Users/Evan/Documents/fresh_2sem/pd2/gitHWs/pd2-Taiko/taiko/files/song_list.txt");
    if(!list.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",list.errorString());
    }
    QTextStream in(&list);
    while(!in.atEnd()){
        line=in.readLine();
        title.push_back(line);
        songs++;
        line=Map.getSubtitle(line);
        subtitle.push_back(line);
    }
    list.close();
   /* QList<QString>::iterator ti;
    int i=0;
    for(ti=title.begin();ti==title.end();ti++, i++){
        qDebug()<<title[i]<<" "<<subtitle[i];
    }*/
    //qDebug()<<QDir::currentPath();
}

void Scene::keyPressEvent(QKeyEvent *key){
    dong = new QSound(":/sound/sound/dong.wav");
    ka = new QSound(":/sound/sound/ka.wav");
    op = new QSound(":/sound/sound/opening.wav");

    if(screenMode==0){
        setbg_0();
        if(key->key()==Qt::Key_J || key->key()==Qt::Key_F){
            dong->play();
            op->play();
            screenMode = 1;
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
    else if(screenMode==1){
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
            screenMode=2;
            unsetbg_1();
            setbg_2();
        }
        if(key->key()==Qt::Key_Escape){
            screenMode=0;
            unsetbg_1();
            setbg_0();
        }
    }
    else if(screenMode==2){
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
            screenMode=1;
            setbg_1();
            showscene1();
        }
    }
    else if(screenMode==3){
        if(key->key()==Qt::Key_F){
            dong->play();
            eliminate(1);
        }
        if(key->key()==Qt::Key_J){
            dong->play();
            eliminate(1);
        }
        if(key->key()==Qt::Key_D){
            ka->play();
            eliminate(2);
        }
        if(key->key()==Qt::Key_K){
            ka->play();
            eliminate(2);
        }
        if(key->key()==Qt::Key_P){
            p++;
            if(p==1){
                track->pause();
                timer1->stop();
                timer2->stop();
                if(set30secMode==true)countdown->stop();
            }
            else if(p==2){
                track->play();
                timer1->start();
                timer2->start();
                if(set30secMode==true)countdown->start();
                p=0;
            }
        }
        if(key->key()==Qt::Key_Escape){
            track->stop();
            unsetbg_3();
            setbg_2();
            screenMode=2;
        }
        if(key->key()==Qt::Key_Equal && (VOL+5)<=100){
            VOL+=5;
            track->setVolume(VOL);
        }
        if(key->key()==Qt::Key_Minus && (VOL-5)>=0){
            VOL-=5;
            track->setVolume(VOL);
        }
        if(key->key()==Qt::Key_BracketRight){
            timer1->start(test+=1);
        }
        if(key->key()==Qt::Key_BracketLeft){
            timer1->start(test-=1);
        }
    }
    else if(screenMode==4){
        if(key->key()==Qt::Key_J || key->key()==Qt::Key_F){
            dong->play();
        }
        if(key->key()==Qt::Key_D || key->key()==Qt::Key_K){
            ka->play();
        }
        if(key->key()==Qt::Key_Escape){
            unsetbg_4();
            setbg_1();
            showscene1();
            screenMode=1;
        }
    }
}


void Scene::setbg_0(){
    QImage bg;
    bg.load(":/pics/pics/open.jpg");
    bg = bg.scaled(770,400);
    this->setBackgroundBrush(bg);
}
void Scene::setbg_1(){
    QImage bg;
    bg.load(":/pics/pics/selecting_song.jpg");
    bg = bg.scaled(770,420);
    this->setBackgroundBrush(bg);

    int x=50,y=100;
    a = new QGraphicsPixmapItem;
    b = new QGraphicsPixmapItem;
    c = new QGraphicsPixmapItem;
    QPixmap song_bg,song_bg_select;
    song_bg.load(":/pics/pics/song_bg.png");
    song_bg = song_bg.scaled(700,50);
    song_bg_select.load(":/pics/pics/song_bg_select.png");
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
    delete a;
    delete b;
    delete c;
}
void Scene::setbg_2(){
    QImage bg;
    bg.load(":/pics/pics/song_picked.jpg");
    bg = bg.scaled(770,400);
    this->setBackgroundBrush(bg);
    Map.getStar(title[s]);
    d = new QGraphicsPixmapItem;
    //st = new QGraphicsPixmapItem;
    QPixmap diff,star,modePic_rand,modePic_30sec,picked_back,arrowPic,modePic_auto;
    diff.load(":/pics/pics/difficulty.png");
    diff = diff.scaled(900,400);
    d->setPixmap(diff);
    addItem(d);
    picked_back.load(":/pics/pics/mode_picked.png");
    picked_background_r = new QGraphicsPixmapItem;
    picked_background_r->setPixmap(picked_back);
    picked_background_r->setPos(189,75);
    if(setRandom==true)addItem(picked_background_r);
    picked_background_3 = new QGraphicsPixmapItem;
    picked_background_3->setPixmap(picked_back);
    picked_background_3->setPos(189,155);
    if(set30secMode==true)addItem(picked_background_3);
    picked_background_a = new QGraphicsPixmapItem;
    picked_background_a->setPixmap(picked_back);
    picked_background_a->setPos(189,235);
    if(setAuto==true)addItem(picked_background_a);
    modePic_rand.load(":/pics/pics/optionicon_random.png");
    icon_rand = new QGraphicsPixmapItem;
    icon_rand->setPixmap(modePic_rand);
    icon_rand->setPos(205,103);
    addItem(icon_rand);
    modePic_30sec.load(":/pics/pics/optionicon_demo.png");
    icon_30sec = new QGraphicsPixmapItem;
    icon_30sec->setPixmap(modePic_30sec);
    icon_30sec->setPos(205,173);
    addItem(icon_30sec);
    arrowPic.load(":/pics/pics/arrow.png");
    arrowPic = arrowPic.scaled(arrowPic.width()/3,arrowPic.height()/3);
    arrow = new QGraphicsPixmapItem;
    arrow->setPixmap(arrowPic);
    modePic_auto.load(":/pics/pics/optionicon_auto.png");
    icon_auto = new QGraphicsPixmapItem;
    icon_auto->setPixmap(modePic_auto);
    icon_auto->setPos(205,253);
    addItem(icon_auto);

    /*star.load(":/pics/pics/star.png");
    st->setPixmap(star);
    st->setPos(160,100);
    addItem(st);*/
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
    removeItem(picked_background_r);
    removeItem(icon_rand);
    removeItem(picked_background_3);
    removeItem(icon_30sec);
    removeItem(picked_background_a);
    removeItem(icon_auto);
    delete d;
    delete picked_background_3;
    delete picked_background_r;
    delete picked_background_a;
    delete icon_30sec;
    delete icon_rand;
    delete icon_auto;
    now_on=0;
}
void Scene::setbg_3(){
    QString load;
    if(difficulty==4)
        load=":/pics/pics/bg_oni.png";
    else if(difficulty==3)
        load=":/pics/pics/bg_hard.png";
    else if(difficulty==2)
        load=":/pics/pics/bg_normal.png";
    else
        load=":/pics/pics/bg_easy.png";
    QImage bg;
    bg.load(load);
    bg = bg.scaled(770,400);
    this->setBackgroundBrush(bg);
    text1->setText(title[s]);
    text1->setPos(488,9);
    addItem(text1);
    Map.setSongPlay(title[s]);
    track = new QMediaPlayer(this);
    track->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(Map.trackPath)));
    VOL=(Map.map["SONGVOL"]-Map.map["SEVOL"])>0?(Map.map["SONGVOL"]-Map.map["SEVOL"]+50):70;
    track->setVolume(VOL);
    BPM=Map.map["BPM"];
    Map.getMap(title[s],Map.star[difficulty-1]);
    Map.convert(setRandom);
    if(setRandom==true){
        QPixmap ran;
        ran.load(":/pics/pics/optionicon_random.png");
        randomTag = new QGraphicsPixmapItem;
        randomTag->setPos(199,83);
        randomTag->setPixmap(ran);
        addItem(randomTag);
    }
    if(setAuto==true){
        QPixmap au;
        au.load(":/pics/pics/optionicon_auto.png");
        autoTag = new QGraphicsPixmapItem;
        autoTag->setPos(394,72);
        autoTag->setPixmap(au);
        addItem(autoTag);
    }
    if(set30secMode==true){
        QPixmap ctd;
        ctd.load(":/pics/pics/optionicon_demo.png");
        countdownTag = new QGraphicsPixmapItem;
        countdownTag->setPos(294,72);
        countdownTag->setPixmap(ctd);
        addItem(countdownTag);
        countdown = new QTimer(this);
        QObject::connect(countdown , SIGNAL(timeout()) , this , SLOT(secondsLeft()));
    }
    songMap=Map.songMap;
    foreach (QString i, songMap) {
        qDebug()<<i<<endl;
    }
    AniTimer1 = new QTimer(this);
    QObject::connect(AniTimer1 , SIGNAL(timeout()) , this , SLOT(moveJudgement()));
    QObject::connect(this , SIGNAL(Great()) , this , SLOT(GenGreat()));
    QObject::connect(this , SIGNAL(Good()) , this , SLOT(GenGood()));
    QObject::connect(this , SIGNAL(Miss()) , this , SLOT(GenMiss()));
    QObject::connect(this , SIGNAL(Combo()) , this , SLOT(ShowCombo()));
    QObject::connect(this , SIGNAL(Score()) , this , SLOT(ShowScore()));

    ex1.load(":/pics/pics/explosion_s4.png");
    AniTimer2 = new QTimer(this);
    QObject::connect(AniTimer2 , SIGNAL(timeout()) , this , SLOT(RemoveExplode()));
    QObject::connect(this , SIGNAL(Explode()) , this , SLOT(GenExplode()));

    AniTimer3 = new QTimer(this);
    QObject::connect(AniTimer3 , SIGNAL(timeout()) , this , SLOT(DanceAndJump()));

    great=0;good=0;miss=0;notesGen=0;
    combo=0;maxcombo=0;soul=0,score=0;
    secLeft=30;
    msec=60000/BPM/4+2;
    test=60000/BPM/16;
    waitfor=109*test/2+Map.map["OFFSET"]*1000;
    for(int i=0;i<10;i++){
        numberPic[i].load(":/pics/pics/number_"+QString::number(i)+".png");
    }
    for(int i=0;i<10;i++){
        ctdnumberPic[i].load(":/pics/pics/number_"+QString::number(i)+".png");
    }
    for(int i=0;i<10;i++){
        scorenumberPic[i].load(":/pics/pics/scorenumber_"+QString::number(i)+".png");
    }
    for(int i=50;i<1000;i+=100){
        QSound *so;
        QString c;
        c=QString::number(i);
        so = new QSound(":/sound/sound/voice_"+c+"combo.wav");
        comTrack.push_back(so);
        if(i==50)i+=50;
    }
    //Etimer = new QElapsedTimer;
    //Etimer->start();

    timer = new QTimer(this);
    QObject::connect(timer , SIGNAL(timeout()) , this , SLOT(stopWait()));
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);
    cout<<"msec: "<<msec<<endl;
    cout<<"waitfor: "<<waitfor<<endl;
    QObject::connect(timer2 , SIGNAL(timeout()) , this , SLOT(Generate()));
    if(setAuto==false)
        QObject::connect(timer1 , SIGNAL(timeout()) , this , SLOT(Move()));
    else
        QObject::connect(timer1 , SIGNAL(timeout()) , this , SLOT(Auto()));

    QObject::connect(timer3 , SIGNAL(timeout()) , this , SLOT(startWave()));
    if(waitfor<0){
        track->play();
        timer->start(-waitfor);
        waitfor=0;
    }
    else
        timer->start(0);
}
void Scene::unsetbg_3(){
    track->stop();
    timer1->stop();
    timer2->stop();
    AniTimer1->stop();
    AniTimer2->stop();
    AniTimer3->stop();
    if(set30secMode==true){
        countdown->stop();
        delete countdown;
        removeItem(countdownTag);
        foreach (QGraphicsPixmapItem *i, ctdnumbers) {
            removeItem(i);
        }
        ctdnumbers.clear();
    }
    removeItem(text1);
    foreach (QGraphicsPixmapItem *i, numbers) {
        removeItem(i);
    }
    numbers.clear();
    foreach (QGraphicsPixmapItem *i, scorenumbers) {
        removeItem(i);
    }
    scorenumbers.clear();
    songMap.clear();
    Map.songMap.clear();
    foreach(QGraphicsPixmapItem *i , Judge){
        this->removeItem(i);
    }
    Judge.clear();
    foreach(QGraphicsPixmapItem *i , expl){
        this->removeItem(i);
    }
    expl.clear();
    firstlayer=1;
    secondlayer=0;
    msec=0;
    waitfor=0;
    foreach(notes *i , list){
        this->removeItem(i);
    }
    list.clear();
    if(setRandom==true){
        this->removeItem(randomTag);
        delete randomTag;
    }
    if(setAuto==true){
        this->removeItem(autoTag);
        delete autoTag;
    }
    delete timer1;
    delete timer2;
    delete AniTimer1;
    delete AniTimer2;
    delete AniTimer3;
}
void Scene::setbg_4(){
    if(combo>maxcombo)maxcombo=combo;
    if(score>=10000000)score=10000000;
    float rate;
    rate=(float)(great+good)/(float)(great+good+miss)*100;
    rate>=60?passed=true:passed=false;
    //soul>48?passed=true:passed=false;
    QImage bg;
    if(passed==true) bg.load(":/pics/pics/resultbg_clear.png");
    else bg.load(":/pics/pics/resultbg_failure.png");
    bg = bg.scaled(770,400);
    this->setBackgroundBrush(bg);
    QString ryou,katt,huka,tenn,saidaicon,sukoua,seikaiRate;
    ryou=QString::number(great);
    katt=QString::number(good);
    huka=QString::number(miss);
    saidaicon=QString::number(maxcombo);
    seikaiRate=QString::number((int)rate);
    sukoua=QString::number(score);
    int x=322;
    for(int i=ryou.size()-1;i>=0;i--){
        QGraphicsPixmapItem *N;
        N = new QGraphicsPixmapItem;
        int c=ryou.at(i).digitValue();
        N->setPixmap(numberPic[c]);
        N->setPos(x,105);
        x-=22;
        addItem(N);
        numbers.push_front(N);
    }
    x=457;
    for(int i=katt.size()-1;i>=0;i--){
        QGraphicsPixmapItem *N;
        N = new QGraphicsPixmapItem;
        int c=katt.at(i).digitValue();
        N->setPixmap(numberPic[c]);
        N->setPos(x,105);
        x-=22;
        addItem(N);
        numbers.push_front(N);
    }
    x=592;
    for(int i=huka.size()-1;i>=0;i--){
        QGraphicsPixmapItem *N;
        N = new QGraphicsPixmapItem;
        int c=huka.at(i).digitValue();
        N->setPixmap(numberPic[c]);
        N->setPos(x,105);
        x-=22;
        addItem(N);
        numbers.push_front(N);
    }
    x=460;
    for(int i=saidaicon.size()-1;i>=0;i--){
        QGraphicsPixmapItem *N;
        N = new QGraphicsPixmapItem;
        int c=saidaicon.at(i).digitValue();
        N->setPixmap(numberPic[c]);
        N->setPos(x,65);
        x-=22;
        addItem(N);
        numbers.push_front(N);
    }
    x=684;
    for(int i=seikaiRate.size()-1;i>=0;i--){
        QGraphicsPixmapItem *N;
        N = new QGraphicsPixmapItem;
        int c=seikaiRate.at(i).digitValue();
        N->setPixmap(numberPic[c]);
        N->setPos(x,65);
        x-=22;
        addItem(N);
        numbers.push_front(N);
    }
    x=386;
    for(int i=sukoua.size()-1;i>=0;i--){
        QGraphicsPixmapItem *N;
        N = new QGraphicsPixmapItem;
        int c=sukoua.at(i).digitValue();
        N->setPixmap(numberPic[c]);
        N->setPos(x,152);
        x-=22;
        addItem(N);
        numbers.push_front(N);
    }
}
void Scene::unsetbg_4(){
    foreach (QGraphicsPixmapItem *i, numbers) {
        removeItem(i);
    }
    numbers.clear();
    foreach (QGraphicsPixmapItem *i, ctdnumbers) {
        removeItem(i);
    }
    ctdnumbers.clear();
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
    removeItem(picked_background_r);
    removeItem(icon_rand);
    removeItem(picked_background_3);
    removeItem(icon_30sec);
    removeItem(picked_background_a);
    removeItem(icon_auto);
    removeItem(arrow);
    QString now,s,e,n,h,ex;
    s=":/pics/pics/difficulty.png";
    e=":/pics/pics/difficulty_easy.png";
    n=":/pics/pics/difficulty_normal.png";
    h=":/pics/pics/difficulty_hard.png";
    ex=":/pics/pics/difficulty_extrem.png";
    QPixmap diff,mode;
    if(now_on==-4){
        now_on=4;
        now=ex;
    }
    else if(now_on==-3){
        now=s;
    }
    else if(now_on==-2){
        now=s;
    }
    else if(now_on==-1){
        now=s;
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
        now_on=-3;
        now=s;
    }
    diff.load(now);
    diff = diff.scaled(900,400);
    d->setPixmap(diff);
    addItem(d);
    addItem(text1);
    if(setRandom==true)addItem(picked_background_r);
    addItem(icon_rand);
    if(set30secMode==true)addItem(picked_background_3);
    addItem(icon_30sec);
    if(setAuto==true)addItem(picked_background_a);
    addItem(icon_auto);
    if(now_on==-1){
        arrow->setPos(138,85);
        addItem(arrow);
    }
    else if(now_on==-2){
        arrow->setPos(138,165);
        addItem(arrow);
    }
    else if(now_on==-3){
        arrow->setPos(138,245);
        addItem(arrow);
    }
}
void Scene::checked(){
    if(now_on==-3){
        setAuto=!setAuto;
        if(setAuto==true){
            removeItem(icon_auto);
            addItem(picked_background_a);
            addItem(icon_auto);
        }
        else removeItem(picked_background_a);
    }
    else if (now_on==-2){
        set30secMode=!set30secMode;
        if(set30secMode==true){
            removeItem(icon_30sec);
            addItem(picked_background_3);
            addItem(icon_30sec);
        }
        else removeItem(picked_background_3);
    }
    else if (now_on==-1){
        setRandom=!setRandom;
        if(setRandom==true){
            removeItem(icon_rand);
            addItem(picked_background_r);
            addItem(icon_rand);
        }
        else removeItem(picked_background_r);
    }
    else if(now_on==0)return;
    else{
        difficulty=now_on;
        screenMode=3;
        unsetbg_2();
        setbg_3();
    }

}


//play
void Scene::eliminate(int key){
    if(list.isEmpty())return;
    //cout<<"pos_last1: "<<list.back()->pos().x()<<endl;
    int x_pos=list.back()->pos().x();
    if(x_pos<=241 && x_pos>=225 &&list.back()->symbol==key){
        ++great;
        ++combo;
        score+=370+80*combo/10;
        removeItem(list.back());
        list.pop_back();
        emit Great();
        emit Explode();
        emit Combo();
        emit Score();
    }
    else if(x_pos<=269 && x_pos>=219 &&list.back()->symbol==key){
        ++good;
        ++combo;
        score+=300+70*combo/10;
        removeItem(list.back());
        list.pop_back();
        emit Good();
        emit Explode();
        emit Combo();
        emit Score();
    }
    else if(x_pos<219){
        this->removeItem(list.back());
        list.pop_back();
        ++miss;
        if(combo>maxcombo)maxcombo=combo;
        combo=0;
        emit Combo();
        emit Miss();
    }

    //cout<<"size: "<<list.size()<<endl;
    //cout<<"pos_last2: "<<list.at(list.size()-2)->pos().x()<<endl;

}
void Scene::stopWait(){
    timer->stop();
    delete timer;
    timer3->start(waitfor);
    timer2->start(msec);
    timer1->start(test);
    AniTimer1->start(50);
    AniTimer2->start(100);
    AniTimer3->start(60000/BPM);
    if(set30secMode==true)countdown->start(1000);
}
void Scene::Generate(){
    QChar c=songMap.at(firstlayer).at(secondlayer);
    //qDebug()<<"fir:"<<firstlayer<<" sec:"<<secondlayer<<" c:"<<c<<endl;
    if(c=='#'){
        secondlayer++;
        c=songMap.at(firstlayer).at(secondlayer);
        if(c=='E'){
            playSeiseki();
        }
        else{
            firstlayer++;
            c=songMap.at(firstlayer).at(secondlayer);
            if(c=='#'){
                secondlayer=0;
                firstlayer++;
                c=songMap.at(firstlayer).at(secondlayer);
            }

        }

    }
    secondlayer++;
    if(secondlayer>15){
        secondlayer=0;
        firstlayer++;
    }
    if (c=='0')return;
    else if(c=='1'){
        notes *dk;
        dk = new notes(1);
        QPixmap pic;
        pic.load(":/pics/pics/ldong.png");
        dk->setPixmap(pic);
        dk->setPos(763,146);
        this->addItem(dk);
        list.push_front(dk);
        notesGen++;
    }
    else if(c=='2'){
        notes *dk;
        dk = new notes(2);
        QPixmap pic;
        pic.load(":/pics/pics/lka.png");
        dk->setPixmap(pic);
        dk->setPos(763,146);
        this->addItem(dk);
        list.push_front(dk);
        notesGen++;
    }
    else if(c=='3'){
        notes *dk;
        dk = new notes(1);
        QPixmap pic;
        pic.load(":/pics/pics/bdong.png");
        dk->setPixmap(pic);
        dk->setPos(763,136);
        this->addItem(dk);
        list.push_front(dk);
        notesGen++;
    }
    else if(c=='4'){
        notes *dk;
        dk = new notes(2);
        QPixmap pic;
        pic.load(":/pics/pics/bka.png");
        dk->setPixmap(pic);
        dk->setPos(763,136);
        this->addItem(dk);
        list.push_front(dk);
        notesGen++;
    }
    else return;
}
void Scene::Move(){
    foreach(notes *i , list){
        i->setPos(i->pos().x()-10,i->pos().y());
            // Do boundary check
        if(i->pos().x()<200){
            this->removeItem(i);
            list.pop_back();
            ++miss;
            if(combo>maxcombo)maxcombo=combo;
            combo=0;
            emit Combo();
            emit Miss();
        }
    }
}
void Scene::Auto(){
    foreach(notes *i , list){
        i->setPos(i->pos().x()-10,i->pos().y());
            // Do boundary check
        if(i->pos().x()<=235 && i->pos().x()>=225){
            ++great;
            ++combo;
            score+=370+80*combo/10;
            removeItem(i);
            list.pop_back();
            i->symbol==1?dong->play():ka->play();
            emit Great();
            emit Explode();
            emit Combo();
            emit Score();
        }
    }

}
void Scene::startWave(){
    track->play();
    timer3->stop();
    delete timer3;
}
void Scene::playSeiseki(){
    unsetbg_3();
    QImage bg;
    bg.load(":/pics/pics/maku.png");
    bg = bg.scaled(770,400);
    this->setBackgroundBrush(bg);
    seiseki = new QSound(":/sound/sound/seiseki.wav");
    seiseki->play();
    soundTimer = new QTimer(this);
    QObject::connect(soundTimer , SIGNAL(timeout()) , this , SLOT(endPlay()));
    soundTimer->start(3000);
}
void Scene::endPlay(){
    soundTimer->stop();
    delete soundTimer;
    if(miss==0){
        fullcombo = new QSound(":/sound/sound/voice_fullcombo.wav");
        fullcombo->play();
    }
    setbg_4();
    screenMode=4;
}

//animation
void Scene::GenGreat(){
    QGraphicsPixmapItem *j;
    j = new QGraphicsPixmapItem;
    QPixmap pic;
    pic.load(":/pics/pics/judgement_great.png");
    pic = pic.scaled(pic.width()*5/4,pic.height()*5/4);
    j->setPixmap(pic);
    j->setPos(235,130);
    this->addItem(j);
    Judge.push_front(j);
}
void Scene::GenGood(){
    QGraphicsPixmapItem *j;
    j = new QGraphicsPixmapItem;
    QPixmap pic;
    pic.load(":/pics/pics/judgement_good.png");
    pic = pic.scaled(pic.width()*5/4,pic.height()*5/4);
    j->setPixmap(pic);
    j->setPos(235,130);
    this->addItem(j);
    Judge.push_front(j);
}
void Scene::GenMiss(){
    QGraphicsPixmapItem *j;
    j = new QGraphicsPixmapItem;
    QPixmap pic;
    pic.load(":/pics/pics/judgement_miss.png");
    pic = pic.scaled(pic.width()*5/4,pic.height()*5/4);
    j->setPixmap(pic);
    j->setPos(225,130);
    this->addItem(j);
    Judge.push_front(j);
}
void Scene::moveJudgement(){
    foreach(QGraphicsPixmapItem *i , Judge){
        i->setPos(i->pos().x(),i->pos().y()-2);
            // Do boundary check
        if(i->pos().y()<105){
            this->removeItem(i);
            Judge.pop_back();
        }
    }
}
void Scene::GenExplode(){
    QGraphicsPixmapItem *ex;
    ex = new QGraphicsPixmapItem;
    ex->setPixmap(ex1);
    ex->setPos(195,110);
    this->addItem(ex);
    expl.push_front(ex);
}
void Scene::secondsLeft(){
    int x=384;
    if(secLeft<=0){
        countdown->stop();
        playSeiseki();
        return;
    }
    QString t;
    t=QString::number(secLeft);
    foreach (QGraphicsPixmapItem *i, ctdnumbers) {
        removeItem(i);
    }
    ctdnumbers.clear();
    for(int i=t.size()-1;i>=0;i--){
        QGraphicsPixmapItem *N;
        N = new QGraphicsPixmapItem;
        int c=t.at(i).digitValue();
        N->setPixmap(ctdnumberPic[c]);
        N->setPos(x,23);
        x-=22;
        addItem(N);
        ctdnumbers.push_front(N);
    }
    secLeft--;
}
void Scene::DanceAndJump(){

}
void Scene::ShowCombo(){
    foreach (QGraphicsPixmapItem *i, numbers) {
        removeItem(i);
    }
    numbers.clear();
    if(combo<5)return;
    if(combo==50)comTrack[0]->play();
    else if(combo==100)comTrack[1]->play();
    else if(combo%100==0&&combo<901)comTrack[combo/100-1]->play();
    QString com;
    int x=146;
    if(combo<10)x=136;
    if(combo>99)x=154;
    com=QString::number(combo);
    for(int i=com.size()-1;i>=0;i--){
        QGraphicsPixmapItem *N;
        N = new QGraphicsPixmapItem;
        int c=com.at(i).digitValue();
        N->setPixmap(numberPic[c]);
        N->setPos(x,138);
        x-=22;
        addItem(N);
        numbers.push_front(N);
    }

}
void Scene::RemoveExplode(){
    foreach (QGraphicsPixmapItem *i, expl) {
        this->removeItem(i);
        expl.pop_back();
    }
}
void Scene::ShowScore(){
    if(score>=10000000)return;
    foreach (QGraphicsPixmapItem *i, scorenumbers) {
        removeItem(i);
    }
    scorenumbers.clear();
    int x=87;
    QString com;
    com=QString::number(score);
    for(int i=com.size()-1;i>=0;i--){
        QGraphicsPixmapItem *N;
        N = new QGraphicsPixmapItem;
        int c=com.at(i).digitValue();
        N->setPixmap(scorenumberPic[c]);
        N->setPos(x,121);
        x-=13;
        addItem(N);
        scorenumbers.push_front(N);
    }
}

//debug
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    cout << "Now event x: " << event->scenePos().x()<< " event y: " << event->scenePos().y() << endl;
}
