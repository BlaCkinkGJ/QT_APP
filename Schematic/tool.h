#ifndef TOOL_H
#define TOOL_H

#include <QMainWindow>
#include <QString>
#include <QGraphicsView>
#include <QFileDialog>
#include <QMessageBox>

#include "buffer.h"

class tool : public QMainWindow
{
public:
    int newFile(); // like fork
    int saveFile(buffer& sch);
    int openFile(buffer& sch);
    int imageExtraction(QGraphicsView* view);


};

#endif // TOOL_H
