#ifndef TOOL_H
#define TOOL_H

#include <QMainWindow>
#include <QString>
#include <QGraphicsView>
#include <QFileDialog>
#include <QMessageBox>

#include "sample.h"

class tool : public QMainWindow
{
public:

private:

public:
    int newFile(); // like fork
    int saveFile(sample& sch);
    int openFile(sample& sch);
    int imageExtraction(QGraphicsView* view);


};

#endif // TOOL_H
