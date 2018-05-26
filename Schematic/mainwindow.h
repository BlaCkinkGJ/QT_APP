#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QGraphicsScene>
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
#include <Queue>

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
    void MainWindow::bfs();
};

#endif // MAINWINDOW_H
