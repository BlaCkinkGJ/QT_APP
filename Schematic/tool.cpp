#include "tool.h"

int tool::newFile(){
    // clear viewport and then set current class
}


int tool::saveFile(sample& sch){
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Schematic"), "",
                                                    tr("Schematic(*.sch);;All Files (*)"));
    if(fileName.isEmpty())
        return -1; // invalid state
    else {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return -1;
        }
        QDataStream out(&file);
        out << QString::number(sch.getValue()); // you have to make operator overloading
    }
    return 0; // success
}

int tool::openFile(sample& sch){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Schematic"), "",
                                                    tr("Schematic(*.sch);;All Files (*)"));
    if(fileName.isEmpty())
        return -1;
    else {
        QFile file(fileName);

        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return -1;
        }
        QDataStream in(&file);
        //sch.clear();
        sch.setValue(in);
    }
    return 0;
}
