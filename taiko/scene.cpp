#include "scene.h"
Scene::Scene()
{
    Map.songlist_init();
    QString line;
    QFile list(Map.path+"/taiko/files/song_list.txt");
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
            emit PlayLdong();
        }
        if(key->key()==Qt::Key_J){
            dong->play();
            eliminate(1);
            emit PlayRdong();
        }
        if(key->key()==Qt::Key_D){
            ka->play();
            eliminate(2);
            emit PlayLka();
        }
        if(key->key()==Qt::Key_K){
            ka->play();
            eliminate(2);
            emit PlayRka();
        }
        if(key->key()==Qt::Key_P){
            p++;
            if(p==1){
                track->pause();
                timer1->stop();
                timer2->stop();
                AniTimer1->stop();
                AniTimer3->stop();
                AniTimer4->stop();
                if(set30secMode==true)countdown->stop();
            }
            else if(p==2){
                track->play();
                timer1->start();
                timer2->start();
                AniTimer1->start();
                AniTimer3->start();
                AniTimer4->start();
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
    removeItem(arrow);
    delete d;
    delete picked_background_3;
    delete picked_background_r;
    delete picked_background_a;
    delete icon_30sec;
    delete icon_rand;
    delete icon_auto;
    delete arrow;
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

    RD = new QTimer(this);
    LD = new QTimer(this);
    RK = new QTimer(this);
    LK = new QTimer(this);
    rdp = new QGraphicsPixmapItem;ldp = new QGraphicsPixmapItem;
    rkp = new QGraphicsPixmapItem;lkp = new QGraphicsPixmapItem;
    QPixmap res;
    res.load(":/pics/pics/rd.png");
    rdp->setPixmap(res);rdp->setPos(147,123);
    res.load(":/pics/pics/ld.png");
    ldp->setPixmap(res);ldp->setPos(106,123);
    res.load(":/pics/pics/rk.png");
    rkp->setPixmap(res);rkp->setPos(147,124);
    res.load(":/pics/pics/lk.png");
    lkp->setPixmap(res);lkp->setPos(105,124);
    for(int i=0;i<4;i++){
        add[i]=false;
    }
    QObject::connect(this , SIGNAL(PlayRdong()) , this , SLOT(playRdong()));
    QObject::connect(this , SIGNAL(PlayLdong()) , this , SLOT(playLdong()));
    QObject::connect(this , SIGNAL(PlayRka()) , this , SLOT(playRka()));
    QObject::connect(this , SIGNAL(PlayLka()) , this , SLOT(playLka()));
    QObject::connect(RD , SIGNAL(timeout()) , this , SLOT(playRdong()));
    QObject::connect(LD , SIGNAL(timeout()) , this , SLOT(playLdong()));
    QObject::connect(RK , SIGNAL(timeout()) , this , SLOT(playRka()));
    QObject::connect(LK , SIGNAL(timeout()) , this , SLOT(playLka()));    

    AniTimer1 = new QTimer(this);
    QObject::connect(AniTimer1 , SIGNAL(timeout()) , this , SLOT(moveJudgement()));
    QObject::connect(AniTimer1 , SIGNAL(timeout()) , this , SLOT(FlySoul()));
    QObject::connect(AniTimer1 , SIGNAL(timeout()) , this , SLOT(MidSoul()));
    QObject::connect(AniTimer1 , SIGNAL(timeout()) , this , SLOT(WalkSoul()));

    QObject::connect(this , SIGNAL(Great()) , this , SLOT(GenGreat()));
    QObject::connect(this , SIGNAL(Good()) , this , SLOT(GenGood()));
    QObject::connect(this , SIGNAL(Miss()) , this , SLOT(GenMiss()));
    QObject::connect(this , SIGNAL(Combo()) , this , SLOT(ShowCombo()));
    QObject::connect(this , SIGNAL(Score()) , this , SLOT(ShowScore()));
    QObject::connect(this , SIGNAL(Jump()) , this , SLOT(donJump()));
    QObject::connect(this , SIGNAL(SoulF()) , this , SLOT(GenFlySoul()));
    QObject::connect(this , SIGNAL(SoulM()) , this , SLOT(GenMidSoul()));
    QObject::connect(this , SIGNAL(SoulW()) , this , SLOT(GenWalkSoul()));

    ex1.load(":/pics/pics/explosion_s4.png");
    AniTimer2 = new QTimer(this);
    QObject::connect(AniTimer2 , SIGNAL(timeout()) , this , SLOT(RemoveExplode()));
    QObject::connect(this , SIGNAL(Explode()) , this , SLOT(GenExplode()));

    AniTimer3 = new QTimer(this);
    QObject::connect(AniTimer3 , SIGNAL(timeout()) , this , SLOT(Jumper()));
    jumper = new QGraphicsPixmapItem;
    jumper->setPos(0,0);
    addItem(jumper);

    AniTimer4 = new QTimer(this);
    QObject::connect(AniTimer4 , SIGNAL(timeout()) , this , SLOT(Dance()));
    loadDancerPic();
    createDanceItem();

    great=0;good=0;miss=0;
    combo=0;maxcombo=0;soul=0,score=0;
    secLeft=30;jumpPicNum=1;
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
    for(int i=0;i<3;i++){
        jumpPic[i].load(":/pics/pics/playerchar_normal"+QString::number(i+1)+".png");
        jumpPic[i] = jumpPic[i].scaled(jumpPic[i].width()*1.48,jumpPic[i].height()*1.48);
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
    AniTimer4->stop();
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
    removeItem(jumper);
    delete jumper;
    foreach (QGraphicsPixmapItem *i, numbers) {
        removeItem(i);
    }
    numbers.clear();
    foreach (QGraphicsPixmapItem *i, scorenumbers) {
        removeItem(i);
    }
    scorenumbers.clear();
    foreach (QGraphicsPixmapItem *i, FSlist) {
        removeItem(i);
    }
    FSlist.clear();
    foreach (QGraphicsPixmapItem *i, WSlist) {
        removeItem(i);
    }
    WSlist.clear();
    foreach (QGraphicsPixmapItem *i, MSlist) {
        removeItem(i);
    }
    MSlist.clear();
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
    removeDanceItem();
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
    removeItem(rdp);removeItem(ldp);removeItem(rkp);removeItem(lkp);
    delete rdp;delete ldp;delete rkp;delete lkp;
    delete RD;delete LD;delete RK;delete LK;
    delete timer1;
    delete timer2;
    delete AniTimer1;
    delete AniTimer2;
    delete AniTimer3;
    delete AniTimer4;
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
        s=songs-1;
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
        emit SoulF();
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
        emit SoulM();
    }
    else if(x_pos<219){
        this->removeItem(list.back());
        list.pop_back();
        ++miss;
        ++missCombo;
        if(combo>maxcombo)maxcombo=combo;
        combo=0;
        emit Combo();
        emit Miss();
        emit SoulW();
    }

    //cout<<"size: "<<list.size()<<endl;
    //cout<<"pos_last2: "<<list.at(list.size()-2)->pos().x()<<endl;

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
            ++missCombo;
            if(combo>maxcombo)maxcombo=combo;
            combo=0;
            emit Combo();
            emit Miss();
            emit SoulW();
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
            if(i->symbol==1){
                dong->play();
                emit PlayRdong();
            }
            else {
                ka->play();
                emit PlayRka();
            }
            emit Great();
            emit Explode();
            emit Combo();
            emit Score();
            emit SoulF();
        }
    }

}
void Scene::stopWait(){
    timer->stop();
    delete timer;
    timer3->start(waitfor);
    timer2->start(msec);
    timer1->start(test);
    AniTimer1->start(50);
    AniTimer2->start(100);
    AniTimer3->start(60000/BPM/2+2);
    AniTimer4->start(msec-2);
    if(set30secMode==true)countdown->start(1000);
}
void Scene::startWave(){
    track->play();
    timer3->stop();
    delete timer3;
}
void Scene::playSeiseki(){
    screenMode=5;
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
void Scene::playRdong(){
    if(add[0]==true){
        RD->stop();
        removeItem(rdp);
        add[0]=false;
    }
    else{
        add[0]=true;
        addItem(rdp);
        RD->start(150);
    }
}
void Scene::playLdong(){
    if(add[1]==true){
        LD->stop();
        removeItem(ldp);
        add[1]=false;
    }
    else{
        add[1]=true;
        addItem(ldp);
        LD->start(150);
    }
}
void Scene::playRka(){
    if(add[2]==true){
        RK->stop();
        removeItem(rkp);
        add[2]=false;
    }
    else{
        add[2]=true;
        addItem(rkp);
        RK->start(150);
    }
}
void Scene::playLka(){
    if(add[3]==true){
        LK->stop();
        removeItem(lkp);
        add[3]=false;
    }
    else{
        add[3]=true;
        addItem(lkp);
        LK->start(150);
    }
}
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
void Scene::Jumper(){
    if(jumpPicNum==0){
        jumper->setPixmap(jumpPic[0]);
    }
    else {
        jumper->setPixmap(jumpPic[1]);
    }
    if(jumpPicNum==3)AniTimer3->start(60000/BPM/2+2);
    jumpPicNum==0?jumpPicNum=1:jumpPicNum=0;

}
void Scene::donJump(){
    jumper->setPixmap(jumpPic[2]);
    AniTimer3->start(60000/BPM+4);
    jumpPicNum=3;

}
void Scene::ShowCombo(){
    foreach (QGraphicsPixmapItem *i, numbers) {
        removeItem(i);
    }
    numbers.clear();
    if(combo<5)return;
    if(combo%10==0)emit Jump();
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
void Scene::FlySoul(){
    foreach (QGraphicsPixmapItem *i, FSlist) {
        i->setPos(i->pos().x()+22,i->pos().y());
            // Do boundary check
        if(i->pos().x()>720){
            this->removeItem(i);
            FSlist.pop_back();
        }
    }
}
void Scene::MidSoul(){
    foreach (QGraphicsPixmapItem *i, MSlist) {
        i->setPos(i->pos().x()+10,i->pos().y());
            // Do boundary check
        /*if(i->pos().x()>700){
            this->removeItem(i);
            WSlist.pop_back();
        }*/
    }
}
void Scene::WalkSoul(){
    foreach (QGraphicsPixmapItem *i, WSlist) {
        i->setPos(i->pos().x()+5,i->pos().y());
            // Do boundary check
        if(i->pos().x()>720){
            this->removeItem(i);
            WSlist.pop_back();
        }
    }
}
void Scene::GenFlySoul(){
    QGraphicsPixmapItem *j;
    j = new QGraphicsPixmapItem;
    QPixmap pic;
    pic.load(":/pics/pics/tamashi0.png");
    pic = pic.scaled(120,61,Qt::KeepAspectRatio);
    j->setPixmap(pic);
    j->setPos(182,20);
    this->addItem(j);
    FSlist.push_front(j);
}
void Scene::GenMidSoul(){
    QGraphicsPixmapItem *j;
    j = new QGraphicsPixmapItem;
    QPixmap pic;
    pic.load(":/pics/pics/tamashi1.png");
    pic = pic.scaled(75,61,Qt::KeepAspectRatio);
    j->setPixmap(pic);
    j->setPos(182,31);
    this->addItem(j);
    MSlist.push_front(j);
}
void Scene::GenWalkSoul(){
    QGraphicsPixmapItem *j;
    j = new QGraphicsPixmapItem;
    QPixmap pic;
    pic.load(":/pics/pics/tamashi2.png");
    pic = pic.scaled(100,61,Qt::KeepAspectRatio);
    j->setPixmap(pic);
    j->setPos(182,55);
    this->addItem(j);
    WSlist.push_front(j);
}
void Scene::loadDancerPic(){
    for(int i=0;i<16;i++){
        d1pa[i].load(":/dancer1/pics/1/dancer_a"+QString::number(i+1)+".png");
        d1pd[i].load(":/dancer1/pics/1/dancer_d"+QString::number(i+1)+".png");
        d1pn[i].load(":/dancer1/pics/1/dancer_n"+QString::number(i+1)+".png");
        d2pa[i].load(":/dancer2/pics/2/dancer_2a"+QString::number(i+1)+".png");
        d2pd[i].load(":/dancer2/pics/2/dancer_2d"+QString::number(i+1)+".png");
        d2pn[i].load(":/dancer2/pics/2/dancer_2n"+QString::number(i+1)+".png");
        d3pa[i].load(":/dancer3/pics/3/dancer_3a"+QString::number(i+1)+".png");
        d3pd[i].load(":/dancer3/pics/3/dancer_3d"+QString::number(i+1)+".png");
        d3pn[i].load(":/dancer3/pics/3/dancer_3n"+QString::number(i+1)+".png");
        d4pa[i].load(":/dancer4/pics/4/dancer_4a"+QString::number(i+1)+".png");
        d4pd[i].load(":/dancer4/pics/4/dancer_4d"+QString::number(i+1)+".png");
        d4pn[i].load(":/dancer4/pics/4/dancer_4n"+QString::number(i+1)+".png");
        d5pa[i].load(":/dancer5/pics/5/dancer_5a"+QString::number(i+1)+".png");
        d5pd[i].load(":/dancer5/pics/5/dancer_5d"+QString::number(i+1)+".png");
        d5pn[i].load(":/dancer5/pics/5/dancer_5n"+QString::number(i+1)+".png");
    }
}
void Scene::createDanceItem(){
    for(int i=0;i<6;i++){
        for(int j=0;j<3;j++){
            dancer_ctr[i][j]=0;
        }
    }
    toNum=0;
    danceNum=0;
    missCombo=0;
    rate=5;
    if(set30secMode==true)dscore=BPM*3;
    else dscore=BPM*9;
    d1 = new QGraphicsPixmapItem;
    d2 = new QGraphicsPixmapItem;
    d3 = new QGraphicsPixmapItem;
    d4 = new QGraphicsPixmapItem;
    d5 = new QGraphicsPixmapItem;
    //setpos add
    d1->setPos(300,180);
    addItem(d1);
    d2->setPos(380,180);
    addItem(d2);
    d3->setPos(220,180);
    addItem(d3);
    d4->setPos(460,180);
    addItem(d4);
    d5->setPos(140,180);
    addItem(d5);

}
void Scene::removeDanceItem(){
    this->removeItem(d1);
    this->removeItem(d2);
    this->removeItem(d3);
    this->removeItem(d4);
    this->removeItem(d5);
    delete d1,d2,d3,d4,d5;

}
void Scene::Dance(){
    //n
    if(danceNum>15)danceNum=0;
    if(dancer_ctr[1][0]==2)
        d1->setPixmap(d1pn[danceNum]);
    if(dancer_ctr[2][0]==2)
        d2->setPixmap(d2pn[danceNum]);
    if(dancer_ctr[3][0]==2)
        d3->setPixmap(d3pn[danceNum]);
    if(dancer_ctr[4][0]==2)
        d4->setPixmap(d4pn[danceNum]);
    if(dancer_ctr[5][0]==2)
        d5->setPixmap(d5pn[danceNum]);
    //move rest
    if(dancer_ctr[1][0]==1){
        d1->setPixmap(d1pa[++dancer_ctr[1][1]]);
        if(dancer_ctr[1][1]>14){
            dancer_ctr[1][0]=2;
        }
    }
    if(dancer_ctr[2][0]==1){
        d2->setPixmap(d2pa[++dancer_ctr[2][1]]);
        if(dancer_ctr[2][1]>14){
            dancer_ctr[2][0]=2;
        }
    }
    if(dancer_ctr[3][0]==1){
        d3->setPixmap(d3pa[++dancer_ctr[3][1]]);
        if(dancer_ctr[3][1]>14){
            dancer_ctr[3][0]=2;
        }
    }
    if(dancer_ctr[4][0]==1){
        d4->setPixmap(d4pa[++dancer_ctr[4][1]]);
        if(dancer_ctr[4][1]>14){
            dancer_ctr[4][0]=2;
        }
    }
    if(dancer_ctr[5][0]==1){
        d5->setPixmap(d5pa[++dancer_ctr[5][1]]);
        if(dancer_ctr[5][1]>14){
            dancer_ctr[5][0]=2;
        }
    }

    if(dancer_ctr[1][0]==3){
        d1->setPixmap(d1pd[++dancer_ctr[1][1]]);
        if(dancer_ctr[1][1]>14){
            dancer_ctr[1][0]=0;
        }
    }
    if(dancer_ctr[2][0]==3){
        d2->setPixmap(d2pd[++dancer_ctr[2][1]]);
        if(dancer_ctr[2][1]>14){
            dancer_ctr[2][0]=0;
        }
    }
    if(dancer_ctr[3][0]==3){
        d3->setPixmap(d3pd[++dancer_ctr[3][1]]);
        if(dancer_ctr[3][1]>14){
            dancer_ctr[3][0]=0;
        }
    }
    if(dancer_ctr[4][0]==3){
        d4->setPixmap(d4pd[++dancer_ctr[4][1]]);
        if(dancer_ctr[4][1]>14){
            dancer_ctr[4][0]=0;
        }
    }
    if(dancer_ctr[5][0]==3){
        d5->setPixmap(d5pd[++dancer_ctr[5][1]]);
        if(dancer_ctr[5][1]>14){
            dancer_ctr[5][0]=0;
        }
    }

    //a add
    if(score/dscore>1 && toNum<=5){
        dscore*=2;
        if(toNum==0){
            dancer_ctr[1][0]=1;
            d1->setPixmap(d1pa[0]);
            dancer_ctr[1][1]=0;
            ++toNum;
        }
        else if(toNum==1){
            dancer_ctr[2][0]=1;
            d2->setPixmap(d2pa[0]);
            dancer_ctr[2][1]=0;
            ++toNum;
        }
        else if(toNum==2){
            dancer_ctr[3][0]=1;
            d3->setPixmap(d3pa[0]);
            dancer_ctr[3][1]=0;
            ++toNum;
        }
        else if(toNum==3){
            dancer_ctr[4][0]=1;
            d4->setPixmap(d4pa[0]);
            dancer_ctr[4][1]=0;
            ++toNum;
        }
        else if(toNum==4){
            dancer_ctr[5][0]=1;
            d5->setPixmap(d5pa[0]);
            dancer_ctr[5][1]=0;
            ++toNum;
        }
        else if(toNum==5){

            ++toNum;
        }
    }
    //d add
    if(missCombo>rate && toNum>0){
        missCombo=0;
        rate+=5;
        //dscore/=2;
        if(toNum==6){

        }
        else if(toNum==5){
            dancer_ctr[5][0]=3;
            d5->setPixmap(d5pd[0]);
            dancer_ctr[5][1]=0;
            --toNum;
        }
        else if(toNum==4){
            dancer_ctr[4][0]=3;
            d4->setPixmap(d4pd[0]);
            dancer_ctr[4][1]=0;
            --toNum;
        }
        else if(toNum==3){
            dancer_ctr[3][0]=3;
            d3->setPixmap(d3pd[0]);
            dancer_ctr[3][1]=0;
            --toNum;
        }
        else if(toNum==2){
            dancer_ctr[2][0]=3;
            d2->setPixmap(d2pd[0]);
            dancer_ctr[2][1]=0;
            --toNum;
        }
        else if(toNum==1){
            dancer_ctr[1][0]=3;
            d1->setPixmap(d1pd[0]);
            dancer_ctr[1][1]=0;
            --toNum;
        }
    }

    danceNum++;
}
//debug
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    cout << "Now event x: " << event->scenePos().x()<< " event y: " << event->scenePos().y() << endl;
}
