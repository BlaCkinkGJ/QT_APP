#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tool.h"
#include "sample.h"
#include "furniture.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->scene = new SchScene();
    ui->view->setScene(scene);
    scene->item = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_saveButton_clicked()
{
    sample sam(2);
   tool toolbar;
    toolbar.saveFile(sam);
    ui->currentValue->setText(QString::number(sam.getValue()));
}

void MainWindow::on_LoadButton_clicked()
{
    sample sam(2);
    tool toolbar;
    toolbar.openFile(sam);

    ui->currentValue->setText(QString::number(sam.getValue()));
}

void MainWindow::on_png_save_clicked()
{
    this->scene->clear();
    this->scene->addRect(0, 0, 100, 200, QPen(Qt::black), QBrush(Qt::green));
    //tool toolbar;
    //toolbar.imageExtraction(ui->view);
}

void MainWindow::on_getImage_clicked()
{
    this->scene->clear();
    Furniture refri("refri", "/home/kijunking/asd.png");
    QPixmap *map = refri.getImage();
    this->scene->item = new QGraphicsPixmapItem(*map);
    this->scene->item->setPos(0.0, 100.0);
    //qDebug() << map->rect().intersects(QRect(0, 0, 100, 100))<< endl; // how to properly use
    this->scene->addItem(this->scene->item);
}

void MainWindow::on_move_clicked()
{
    if(this->scene->item != nullptr){
        static quint64 value = 10;
        scene->item->setPos(0, value);
        value = (value + 10) % 100;
    }
}
