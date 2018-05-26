#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QGraphicsScene>
/*
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include "schscene.h"
*/
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QCursor>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QPointF>
#include <QLine>
#include <QLineF>
#include <QKeyEvent>
#include <QRgb>
#include <QImage>
#include <QWidget>
#include <queue>
#include <cmath>

#define INF 987654321
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

/*
public slots:
    void on_saveButton_clicked();

    void on_LoadButton_clicked();

    void on_png_save_clicked();

private slots:
    void on_getImage_clicked();

    void on_move_clicked();
*/
private slots:
    void on_EnterButton_clicked();
    void on_ResetButton_clicked();


private:
    bool startDrawing = false;
    int wallDrawing = 0;
    int wallx1, wally1, wallx2, wally2;
    int houseWidth, houseHeight;
    QMessageBox qmb;
    Ui::MainWindow *ui;
/*
    SchScene *scene;
*/

    QGraphicsScene *scene;
    std::vector<QGraphicsLineItem *> experiorWall;
    std::vector<QGraphicsLineItem *> interiorWall;
    std::vector<QGraphicsLineItem *> windowList;
    std::vector<QGraphicsRectItem *> doorList;
    std::vector<std::vector<QGraphicsLineItem *> > room;
    void mousePressEvent(QMouseEvent *mouse);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void bfs();
};

#endif // MAINWINDOW_H
