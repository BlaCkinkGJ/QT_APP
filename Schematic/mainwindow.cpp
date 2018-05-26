#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "furniture.h"

bool dir; // Not useful
int roomColor[2000][2000]; // ----- > to make a 800 x 600
int state = 0;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0, 0, 1000, 1000);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(!startDrawing) return;

    if(event->key() == Qt::Key_1)
    {
        if(wallDrawing == 1)
        {
            wallDrawing = 0;
            return;
        }
        wallDrawing = 1;
    }
    else if (event->key() == Qt::Key_2)
    {
        if(wallDrawing == 3)
        {
            wallDrawing = 0;
            return;
        }
        wallDrawing = 3;
    }
    else if (event->key() == Qt::Key_3)
    {
        if(wallDrawing == 4)
        {
            wallDrawing = 0;
            return;
        }
        wallDrawing = 4;
    }
    else if (event->key() == Qt::Key_4)
    {
        bfs();
        wallDrawing = 0;
    }
}

void MainWindow::on_EnterButton_clicked()
{
    if(startDrawing) return;
    else startDrawing = true;

    QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);

    double width = ui->lineEdit->text().toDouble();
    double height = ui->lineEdit_2->text().toDouble();
    houseWidth = 10 * width;
    houseHeight = 10 * height;

    QPen outlinePen(Qt::blue);
    outlinePen.setWidth(1);

    experiorWall.clear();
    experiorWall.push_back(scene->addLine(100, 100, houseWidth, 100, outlinePen));
    experiorWall.push_back(scene->addLine(houseWidth, 100, houseWidth, houseHeight, outlinePen));
    experiorWall.push_back(scene->addLine(houseWidth, houseHeight, 100, houseHeight, outlinePen));
    experiorWall.push_back(scene->addLine(100, houseHeight, 100, 100, outlinePen));
}

void MainWindow::on_ResetButton_clicked()
{
    for(int i=0; i<=2000; i++)
        for(int j=0; j<=2000; j++)
            roomColor[i][j] = 0;

    QPixmap qPix = QPixmap::grabWidget(ui->graphicsView, 0, 0, 1001, 1001);
    QImage image(qPix.toImage());

    QRgb val = qRgb(255, 255 ,255);

    for(int i = 0; i <= 1000; i++)
        for(int j = 0; j <= 1000; j++)
            image.setPixelColor(i, j,  val);

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);

    for(auto index : experiorWall)
    {
        scene->removeItem(index);
    }
    for(auto index : interiorWall)
    {
        scene->removeItem(index);
    }
    for(auto index : windowList)
    {
        scene->removeItem(index);
    }
    for(auto index : doorList)
    {
        scene->removeItem(index);
    }
    experiorWall.clear();
    interiorWall.clear();
    windowList.clear();
    doorList.clear();
    startDrawing = false;
}

void MainWindow::mousePressEvent(QMouseEvent *mouse)
{
    if(!startDrawing || !wallDrawing) return;

    QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);
    QGraphicsRectItem *temp = new QGraphicsRectItem();

    int x = relativeOrigin.x();
    int y = relativeOrigin.y();

    if(x < 0 || y < 0 || x > houseWidth || y > houseHeight)
    {
        qmb.setText("Please Click in the house.");
        qmb.exec();
        return;
    }

    if(wallDrawing == 1)
    {
        wallDrawing++;

        double min = INF, length;
        QGraphicsLineItem *find;
        for(auto index : experiorWall)
        {
            if(index->line().x1() == index->line().x2())
                length = abs(index->line().toLine().x1() - x);
            else length = abs(index->line().toLine().y1() - y);

            if(length < min)
            {
                min = length;
                find = index;
            }
        }

        if(find->line().x1() == find->line().x2())
        {
            x = find->line().toLine().x1();
            dir = true;
        }
        else
        {
            y = find->line().toLine().y1();
            dir = false;
        }

        wallx1 = x;
        wally1 = y;

        QPen outlinePen(Qt::red);
        QBrush brush(Qt::red);
        temp = scene->addRect(wallx1 - 1, wally1 - 1, 3, 3, outlinePen, brush);
    }
    else if(wallDrawing == 2)
    {
        wallDrawing--;

        wallx2 = x;
        wally2 = y;

        if(dir) wally2 = wally1;
        else wallx2 = wallx1;

        QPen outlinePen(Qt::red);
        outlinePen.setWidth(1);
        interiorWall.push_back(scene->addLine(wallx1, wally1, wallx2, wally2, outlinePen));

        scene->removeItem(temp);
        delete temp;

        for(int i=wallx1; i<=wallx2; i++)
            for(int j=wally1; j<=wally2; j++)
                roomColor[i][j] = -1;
    }
    else if(wallDrawing == 3) // window
    {
        double min = INF, length;
        QGraphicsLineItem *Object;

        for(auto index : experiorWall)
        {
            if(index->line().x1() == index->line().x2())
                length = abs(index->line().toLine().x1() - x);
            else length = abs(index->line().toLine().y1() - y);

            if(length < min)
            {
                min = length;
                Object = index;
            }
        }

        for(auto index : interiorWall)
        {
            if(index->line().x1() == index->line().x2())
                length = abs(index->line().toLine().x1() - x);
            else length = abs(index->line().toLine().y1() - y);

            if(length < min)
            {
                min = length;
                Object = index;
            }
        }

        if(min > 20)
        {
            qmb.setText("Too far for the wall.");
            qmb.exec();
            return;
        }

        if(Object->line().x1() == Object->line().x2())
        {
            x = Object->line().toLine().x1();
            dir = true;
        }
        else
        {
            y = Object->line().toLine().y1();
            dir = false;
        }

        for(auto index : windowList)
        {
            if(index->line().x1() == index->line().x2())
                length = sqrt((index->line().toLine().x1() - x) * (index->line().toLine().x2() - x)
                        + ((index->line().toLine().y1() + index->line().toLine().y2()) / 2 - y)
                        * ((index->line().toLine().y1() + index->line().toLine().y2()) / 2 - y));
            else length = sqrt((index->line().toLine().y1() - y) * (index->line().toLine().y2() - y)
                               + ((index->line().toLine().x1() + index->line().toLine().x2()) / 2 - x)
                               * ((index->line().toLine().x1() + index->line().toLine().x2()) / 2 - x));

            if(length < 30)
            {
                scene->removeItem(index);
                windowList.erase(std::find(windowList.begin(), windowList.end(), index));
                return;
            }
        }

        for(auto index : doorList)
        {
            if(index->line().x1() == index->line().x2())
                length = sqrt((index->line().toLine().x1() - x) * (index->line().toLine().x2() - x)
                        + ((index->line().toLine().y1() + index->line().toLine().y2()) / 2 - y)
                        * ((index->line().toLine().y1() + index->line().toLine().y2()) / 2 - y));
            else length = sqrt((index->line().toLine().y1() - y) * (index->line().toLine().y2() - y)
                               + ((index->line().toLine().x1() + index->line().toLine().x2()) / 2 - x)
                               * ((index->line().toLine().x1() + index->line().toLine().x2()) / 2 - x));

            if(length < 30)
            {
                qmb.setText("Too Close");
                qmb.exec();
                return;
            }
        }

        QPen outlinePen(Qt::green);
        outlinePen.setWidth(5);
        if(!dir)
        {
            if((Object->line().toLine().x1() + Object->line().toLine().x2() / 2) > x)
                windowList.push_back(scene->addLine(x, y, x + 20, y, outlinePen));
            else windowList.push_back(scene->addLine(x, y, x - 20, y, outlinePen));
        }
        else
        {
            if((Object->line().toLine().y1() + Object->line().toLine().y2() / 2) > y)
                windowList.push_back(scene->addLine(x, y, x, y + 20, outlinePen));
            else windowList.push_back(scene->addLine(x, y, x, y - 20, outlinePen));
        }
    }
    else if(wallDrawing == 4) // door
    {
        double min = INF, length;
        QGraphicsLineItem *Object;

        for(auto index : experiorWall)
        {
            if(index->line().x1() == index->line().x2())
                length = abs(index->line().toLine().x1() - x);
            else length = abs(index->line().toLine().y1() - y);

            if(length < min)
            {
                min = length;
                Object = index;
            }
        }

        for(auto index : interiorWall)
        {
            if(index->line().x1() == index->line().x2())
                length = abs(index->line().toLine().x1() - x);
            else length = abs(index->line().toLine().y1() - y);

            if(length < min)
            {
                min = length;
                Object = index;
            }
        }

        if(min > 20)
        {
            qmb.setText("Too far for the wall.");
            qmb.exec();
            return;
        }

        if(Object->line().x1() == Object->line().x2())
        {
            x = Object->line().toLine().x1();
            dir = true;
        }
        else
        {
            y = Object->line().toLine().y1();
            dir = false;
        }

        for(auto index : windowList)
        {
            if(index->line().x1() == index->line().x2())
                length = sqrt((index->line().toLine().x1() - x) * (index->line().toLine().x2() - x)
                        + ((index->line().toLine().y1() + index->line().toLine().y2()) / 2 - y)
                        * ((index->line().toLine().y1() + index->line().toLine().y2()) / 2 - y));
            else length = sqrt((index->line().toLine().y1() - y) * (index->line().toLine().y2() - y)
                               + ((index->line().toLine().x1() + index->line().toLine().x2()) / 2 - x)
                               * ((index->line().toLine().x1() + index->line().toLine().x2()) / 2 - x));

            if(length < 30)
            {
                scene->removeItem(index);
                windowList.erase(std::find(windowList.begin(), windowList.end(), index));
                return;
            }
        }

        for(auto index : doorList)
        {
            if(index->line().x1() == index->line().x2())
                length = sqrt((index->line().toLine().x1() - x) * (index->line().toLine().x2() - x)
                        + ((index->line().toLine().y1() + index->line().toLine().y2()) / 2 - y)
                        * ((index->line().toLine().y1() + index->line().toLine().y2()) / 2 - y));
            else length = sqrt((index->line().toLine().y1() - y) * (index->line().toLine().y2() - y)
                               + ((index->line().toLine().x1() + index->line().toLine().x2()) / 2 - x)
                               * ((index->line().toLine().x1() + index->line().toLine().x2()) / 2 - x));

            if(length < 30)
            {
                qmb.setText("Too Close");
                qmb.exec();
                return;
            }
        }

        QPen outlinePen(Qt::black);
        outlinePen.setWidth(20);
        if(!dir)
        {
            if((Object->line().toLine().x1() + Object->line().toLine().x2() / 2) > x)
                windowList.push_back(scene->addLine(x, y, x + 20, y, outlinePen));
            else windowList.push_back(scene->addLine(x, y, x - 20, y, outlinePen));
        }
        else
        {
            if((Object->line().toLine().y1() + Object->line().toLine().y2() / 2) > y)
                windowList.push_back(scene->addLine(x, y, x, y + 20, outlinePen));
            else windowList.push_back(scene->addLine(x, y, x, y - 20, outlinePen));
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);

    int x = relativeOrigin.x();
    int y = relativeOrigin.y();

    //ui->lineEdit->setText(QString::number(x)); -> deleted debug mode
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(!(wallDrawing == 1 || wallDrawing == 2)) return;

    double length;

    QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);

    int x = relativeOrigin.x();
    int y = relativeOrigin.y();

    for(auto index : interiorWall)
    {
        if(index->line().x1() == index->line().x2())
            length = sqrt((index->line().toLine().x1() - x) * (index->line().toLine().x2() - x)
                           + ((index->line().toLine().y1() + index->line().toLine().y2()) / 2 - y)
                           * ((index->line().toLine().y1() + index->line().toLine().y2()) / 2 - y));
        else length = sqrt((index->line().toLine().y1() - y) * (index->line().toLine().y2() - y)
                           + ((index->line().toLine().x1() + index->line().toLine().x2()) / 2 - x)
                           * ((index->line().toLine().x1() + index->line().toLine().x2()) / 2 - x));

        if(length < 50)
        {
            scene->removeItem(index);
            interiorWall.erase(std::find(interiorWall.begin(), interiorWall.end(), index));
            return;
        }
    }
}

void MainWindow::bfs()
{
    QPixmap qPix = QPixmap::grabWidget(ui->graphicsView, 0, 0, 1001, 1001);
    QImage image(qPix.toImage());


    for(int i = 0; i <= 1000; i++)
        for(int j = 0; j <= 1000; j++)
        {
            if(i <= houseWidth && j <= houseHeight) continue;
            image.setPixelColor(i, j,  qRgb(255, 255, 255));
        }

    QRgb val[3] = {qRgb(155, 0 ,0), qRgb(0, 155, 0), qRgb(0, 0, 155)};
    int count = 0;

    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    for(int i = 0; i <= houseWidth; i++)
        for(int j = 0; j <= houseHeight; j++)
        {
            QColor color(image.pixelColor(i, j));
            // if(roomColor[i][j] == 0)
            if(color.blue() == 255 && color.red() == 255 && color.green() == 255)
            {
                std::queue<std::pair<int, int> > temp;
                temp.push(std::make_pair(i, j));
                while(1)
                {
                    if(temp.empty())
                    {
                        count++;
                        break;
                    }
                    int tx = temp.front().first;
                    int ty = temp.front().second;
                    temp.pop();

                    for(int k=0; k<4; k++)
                    {
                        int x = tx + dx[k];
                        int y = ty + dy[k];
                        if(x < 0 || y < 0 || x > houseWidth || y > houseHeight) continue;
                        QColor color2(image.pixelColor(x, y));
                        // if(roomColor[x][y]) continue;
                        if(color2.blue() != 255 || color2.red() != 255 || color2.green() != 255) continue;
                        roomColor[x][y] = count + 1;
                        image.setPixelColor(x, y,  val[count]);
                        temp.push(std::make_pair(x, y));
                    }
                }
            }
        }

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
}

void MainWindow::on_exit_clicked()
{ // close the application
    QApplication::quit();
}

void MainWindow::on_save_clicked()
{
    // toolBar.saveFile(); // data required
}

void MainWindow::on_open_clicked()
{
    // toolBar.openFile(); // how to put is required
}

void MainWindow::on_extraction_clicked()
{
    toolBar.imageExtraction(this->ui->graphicsView);
}
