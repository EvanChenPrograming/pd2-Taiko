#include "file_control.h"

file_control::file_control()
{
}

void file_control::songlist_init(){
    QStringList songlist;
    dir.setPath("/Users/Evan/Documents/fresh_2sem/pd2/gitHWs/pd2-Taiko/taiko/songs");
    dir.setSorting(QDir::Name);
    //dir.setFilter(QDir::NoDotAndDotDot);
    songlist = dir.entryList();
    /*for(int i=0;i<songlist.size();++i){
        cout<<songlist.at(i).toUtf8().constData()<<endl;
    }
    cout<<"fuck "<<songlist.size()<<endl;
*/
    QFile ofile("/Users/Evan/Documents/fresh_2sem/pd2/gitHWs/pd2-Taiko/taiko/files/song_list.txt");
    if(!ofile.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0,"error",ofile.errorString());
    }
    QTextStream out(&ofile);
    for(int i=0;i<songlist.size();++i){
        if(songlist.at(i)=="." || songlist.at(i)=="..")
            continue;
        out<<songlist.at(i)<<endl;
    }
    //ofile.close();
}

QString file_control::getSubtitle(QString Title){
    path="/Users/Evan/Documents/fresh_2sem/pd2/gitHWs/pd2-Taiko/";
    QString pathNom = QDir::toNativeSeparators(path+"taiko/songs/"+Title.toUtf8()+"/"+Title.toUtf8()+".tja");
    QFile fin(pathNom);
    if(!fin.open(QIODevice::ReadOnly)) {
        cerr<<Title.toStdString()<<" not open"<<endl;
        QMessageBox::information(0,"error",fin.errorString());
    }
    QString line;
    QString c;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //cout<<"in"<<endl;
    QTextStream in(&fin);
    while(!in.atEnd()){
        c=in.read(1);
        if(c =="#")break;
        if(c == "S"){
            c=in.read(1);
            if(c=="U"){
                c=in.read(7);
                line= codec->toUnicode(in.readLine().toStdString().c_str());
                break;
            }
        }
        else
            continue;
    }
    fin.close();
    return line;
}

void file_control::getStar(QString SongName){
    QFile fin(path+"taiko/songs/"+SongName.toUtf8()+"/"+SongName.toUtf8()+".tja");
    if(!fin.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",fin.errorString());
    }
    QString line,ti;
    QString c;
    QTextStream in(&fin);
    while(!in.atEnd()){
        c=in.read(1);
        if (c=="C"){
            ti.push_back(c);
            c=in.read(5);
            ti.push_back(c);
            c=in.read(1);
            line=in.readLine();
            in.read(6);
            if(line=="Oni"||line=="oni"||line=="3"){
                star[3]=in.readLine().toInt();
            }
            else if(line=="hard"||line=="Hard"||line=="2"){
                star[2]=in.readLine().toInt();
            }
            else if(line=="normal"||line=="Normal"||line=="1"){
                star[1]=in.readLine().toInt();
            }
            else if(line=="easy"||line=="Easy"||line=="0"){
                star[0]=in.readLine().toInt();
            }
            else
                continue;
        }
        else line=in.readLine();
    }
    fin.close();
    cout<<"3: "<<star[3]<<"\n2: "<<star[2]<<"\n1: "<<star[1]<<"\n0: "<<star[0]<<endl;
}

void file_control::setSongPlay(QString SongName){
    //qDebug()<<QDir::currentPath()<<endl;
    QFile fin(path+"taiko/songs/"+SongName.toUtf8()+"/"+SongName.toUtf8()+".tja");
    if(!fin.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",fin.errorString());
    }
    QString line,ti;
    QString c;
    QTextStream in(&fin);
    while(!in.atEnd()){
        c=in.read(1);
        if (c=="#"){
            break;
        }
        if(c=="\n" || c=="\r"){
            continue;
        }
        if(c==":"){
            line=in.readLine();
            //qDebug()<<ti<<" : "<<line<<endl;
            if(ti=="TITLE")
                TITLE=line;
            else if(ti=="SUBTITLE")
                SUBTITLE=line;
            else if(ti=="WAVE")
                WAVE=line;
            else
                map[ti]=line.toFloat();
            ti="";line="";
        }
        else{
            ti.push_back(c);
        }
    }
    fin.close();
    trackPath = path+"taiko/songs/"+SongName.toUtf8()+"/"+WAVE.toUtf8();
}

void file_control::getMap(QString SongName,int Level){
    QFile fin(path+"taiko/songs/"+SongName.toUtf8()+"/"+SongName.toUtf8()+".tja");
    if(!fin.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",fin.errorString());
    }
    QString line,ti;
    QString c;
    QTextStream in(&fin);
    while(!in.atEnd()){
        c=in.read(1);
        if(c=="L"){
            ti.push_back(c);
            c=in.read(1);
            if(c=="E"){
                ti.push_back(in.read(4));
                if(in.readLine().toInt()==Level){
                    while(!in.atEnd()){
                        c=in.read(1);
                        if(c=="#"){
                            songMap.push_back(c);
                            c=in.readLine();
                            songMap.replace(0,songMap.at(0)+c);
                            while(!in.atEnd()){
                                c=in.readLine();
                                if(c=="")continue;
                                else if(c=="#END"){
                                    songMap.push_back(c);
                                    fin.close();
                                    return;
                                }
                                else
                                    songMap.push_back(c);
                            }
                        }
                    }
                }
            }
        }
    }
}


void file_control::convert(bool setRandom){
    if(setRandom==true){
        srand(time(NULL));
        for(int i=0;i<songMap.size();i++){
            for(int j=0;j<songMap.at(i).size();j++){
                if(songMap.at(i).at(j).digitValue()<=4 && songMap.at(i).at(j).digitValue()>=1){
                    QString c=QString::number(rand()%4+1);
                    songMap[i].replace(j,1,c);
                }
            }
        }
    }
    for(int i=0;i<songMap.size();i++){
        if(songMap.at(i).size()==1){
            songMap[i].insert(0,"0000000000000000");
        }
        else if(songMap.at(i).size()==2){
            songMap[i].insert(1,"000000000000000");
        }
        else if(songMap.at(i).size()==3){
            for(int j=1;j<10;j+=8){
                songMap[i].insert(j,"0000000");
            }
        }
        else if(songMap.at(i).size()==5){
            for(int j=1;j<14;j+=4){
                songMap[i].insert(j,"000");
            }
        }
        else if(songMap.at(i).size()==9){
            for(int j=1;j<16;j+=2){
                songMap[i].insert(j,"0");
            }
        }

        //debug
        for(int j=0;j<16;j++){
            if(songMap.at(i).size()<16)
                songMap[i].push_back("0");
        }
    }
}
