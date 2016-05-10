#include "file_control.h"

file_control::file_control()
{

}
void file_control::setSongPlay(QString){
    QFile fin("../taiko/files/チルノのパーフェクトさんすう教室/チルノのパーフェクトさんすう教室.tja");
    if(!fin.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",fin.errorString());
    }

}
