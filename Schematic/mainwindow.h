#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include "schscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_saveButton_clicked();

    void on_LoadButton_clicked();

    void on_png_save_clicked();

private slots:
    void on_getImage_clicked();

    void on_move_clicked();

private:
    Ui::MainWindow *ui;
    SchScene *scene;
};

#endif // MAINWINDOW_H
