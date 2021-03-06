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
#include <QHash>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QTextStream>
#include <QList>
#include <QGuiApplication>
#include <QListView>
#include <QLabel>

#include "furniture.h"
#include "tool.h"

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

    QGraphicsPixmapItem* item;

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


    void on_save_clicked();

    void on_open_clicked();

    void on_extraction_clicked();

    void on_FurnitureList_itemDoubleClicked(QListWidgetItem *item);

    void on_newfile_clicked();

    void on_FurnitureList_itemSelectionChanged();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    struct roomInformation
    {
        int index;
        QString name;
        bool hasDoor = false;
    };

    bool startDrawing = false;
    int wallDrawing = 0;
    int wallx1, wally1, wallx2, wally2;
    int houseWidth, houseHeight;
    double imageScale;
    QMessageBox qmb;
    Ui::MainWindow *ui;
    tool toolBar;
    QHash<QString, Furniture> furniture;
    std::vector<roomInformation> roomList;
/*
    SchScene *scene;
*/
    QGraphicsScene *scene;
    std::vector<QGraphicsLineItem *> experiorWall;
    std::vector<QGraphicsLineItem *> interiorWall;
    std::vector<QGraphicsLineItem *> windowList;
    std::vector<QGraphicsLineItem *> doorList;
    void mousePressEvent(QMouseEvent *mouse);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void bfs();
    void loadFunction();
};

#endif // MAINWINDOW_H
