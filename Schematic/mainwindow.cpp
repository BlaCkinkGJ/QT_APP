#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tool.h"
#include "sample.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    QGraphicsScene *scene = new QGraphicsScene();
    ui->view->setScene(scene);
    scene->addRect(0, 0, 100, 200, QPen(Qt::black), QBrush(Qt::green));

    tool toolbar;
    toolbar.imageExtraction(ui->view);
}
