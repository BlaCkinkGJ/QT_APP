#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "furniture.h"
#include "tool.cpp"
#include "buffer.cpp"

bool dir; // Not useful
int roomColor[1500][1500]; // ----- > to make a 800 x 600
int state = 0;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0, 0, 1000, 1000);
    ui->graphicsView->setScene(scene);

    this->furniture.insert("refrigerator", Furniture("refrigerator",
                  "refri.PNG"));
    this->furniture.insert("laundry", Furniture("laundry",
                  "laun.PNG"));
    for(auto i : this->furniture)
        this->ui->FurnitureList->addItem(i.getName());
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
            ui->label_5->setText("Default");
            wallDrawing = 0;
            return;
        }
        ui->label_5->setText("Make Wall");
        wallDrawing = 1;
    }
    else if (event->key() == Qt::Key_2)
    {
        if(wallDrawing == 3)
        {
            ui->label_5->setText("Default");
            wallDrawing = 0;
            return;
        }
        ui->label_5->setText("Make Door");
        wallDrawing = 3;
    }
    else if (event->key() == Qt::Key_3)
    {
        if(wallDrawing == 4)
        {
            ui->label_5->setText("Default");
            wallDrawing = 0;
            return;
        }
        ui->label_5->setText("Make Window");
        wallDrawing = 4;
    }
    else if (event->key() == Qt::Key_4)
    {
        ui->label_5->setText("Default");
        bfs();
        wallDrawing = 0;
    }
    else if (event->key() == Qt::Key_5)
    {
        ui->label_5->setText("Default");
        loadFunction();
        wallDrawing = 0;
    }
}

void MainWindow::on_EnterButton_clicked()
{
    if(startDrawing) return;
    else startDrawing = true;

    // QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
    // QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);

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
    for(int i=0; i<=1000; i++)
        for(int j=0; j<=1000; j++)
            roomColor[i][j] = 0;

    QPixmap qPix = QPixmap::grabWidget(ui->graphicsView, 0, 0, 1001, 1001);
    QImage image(qPix.toImage());

    QRgb val = qRgb(254, 254 ,254);

    for(int i = 0; i <= 1000; i++)
        for(int j = 0; j <= 1000; j++)
            image.setPixelColor(i, j,  val);

    QPixmap pixmap; pixmap.fromImage(image);
    scene->addPixmap(pixmap);

    /*
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
    */
    experiorWall.clear();
    interiorWall.clear();
    windowList.clear();
    doorList.clear();
    this->ui->listWidget->clear();
    this->ui->FurnitureList->clear();
    this->furniture.clear();
    scene->clear();
    startDrawing = false;

    ui->listWidget->clear();
    ui->listWidget_2->clear();
    this->furniture.insert("refrigerator", Furniture("refrigerator",
                  "refri.PNG"));
    this->furniture.insert("laundry", Furniture("laundry",
                  "laun.PNG"));
    for(auto i : this->furniture)
        this->ui->FurnitureList->addItem(i.getName());
}

void MainWindow::mousePressEvent(QMouseEvent *mouse)
{
    static int test = 0;
    qDebug() << test++ << endl;
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

        QPen outlinePen(qRgb(51, 255, 255));
        outlinePen.setWidth(20);

        if(!dir)
        {
            if((Object->line().toLine().x1() + Object->line().toLine().x2() / 2) > x)
            {
                windowList.push_back(scene->addLine(x, y, x + 20, y, outlinePen));
                for(int i=x; i<=x+20; i++)
                    roomColor[i][y] = -2;
            }
            else
            {
                windowList.push_back(scene->addLine(x, y, x - 20, y, outlinePen));
                for(int i=x; i>=x-20; i--)
                    roomColor[i][y] = -2;
            }
        }
        else
        {
            if((Object->line().toLine().y1() + Object->line().toLine().y2() / 2) > y)
            {
                windowList.push_back(scene->addLine(x, y, x, y + 20, outlinePen));
                for(int i=y; i<=y+20; i++)
                    roomColor[x][i] = -2;
            }
            else
            {
                windowList.push_back(scene->addLine(x, y, x, y - 20, outlinePen));
                for(int i=y; i>=y-20; y--)
                    roomColor[x][i] = -2;
            }
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
                scene->removeItem(index);
                doorList.erase(std::find(doorList.begin(), doorList.end(), index));
                return;
            }
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
                qmb.setText("Too Close");
                qmb.exec();
                return;
            }
        }

        QPen outlinePen(qRgb(255, 127, 0));
        outlinePen.setWidth(20);

        if(!dir)
        {
            if((Object->line().toLine().x1() + Object->line().toLine().x2() / 2) > x)
            {
                doorList.push_back(scene->addLine(x, y, x + 20, y, outlinePen));
                for(int i=x; i<=x+20; i++)
                    roomColor[i][y] = -3;
            }
            else
            {
                doorList.push_back(scene->addLine(x, y, x - 20, y, outlinePen));
                for(int i=x; i>=x-20; i--)
                    roomColor[i][y] = -3;
            }
        }
        else
        {
            if((Object->line().toLine().y1() + Object->line().toLine().y2() / 2) > y)
            {
                doorList.push_back(scene->addLine(x, y, x, y + 20, outlinePen));
                for(int i=y; i<=y+20; i++)
                    roomColor[x][i] = -3;
            }
            else
            {
                doorList.push_back(scene->addLine(x, y, x, y - 20, outlinePen));
                for(int i=y; i>=y-20; y--)
                    roomColor[x][i] = -3;
            }
        }
    }
    else if(wallDrawing == 9)
    {
        QPixmap qPix = QPixmap::grabWidget(ui->graphicsView, 0, 0, 1001, 1001);
        QImage image(qPix.toImage());

        for(int i=x; i<=x+item->boundingRect().width() * imageScale; i++)
            for(int j=y; j<=x+item->boundingRect().height() * imageScale; j++)
            {
                QColor color(image.pixelColor(i, j));
                if(color == qRgb(255, 0, 0) || color == qRgb(0, 0, 255) ||
                        color == qRgb(255, 127, 0) || color == qRgb(51, 255, 255))
                {
                    qmb.setText("Can't establish here.");
                    qmb.exec();
                    return;
                }
            }

        item->setPos(x, y);
        this->scene->addItem(item);
        ui->label_5->setText("Default");
        wallDrawing = 0;

        for(int i = x; i <= x + item->boundingRect().width() * imageScale; i++)
            for(int j = y; j <= y + item->boundingRect().height() * imageScale; j++)
                roomColor[i][j] = -5;
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if((wallDrawing == 1 || wallDrawing == 2))
    {
        return;
    }

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
    roomList.clear();
    ui->listWidget->clear();
    ui->listWidget_2->clear();

    QPixmap qPix = QPixmap::grabWidget(ui->graphicsView, 0, 0, 1001, 1001);
    QImage image(qPix.toImage());

    for(int i = 0; i <= 1000; i++)
        for(int j = 0; j <= 1000; j++)
        {
            if(i <= houseWidth && j <= houseHeight) continue;
            image.setPixelColor(i, j,  qRgb(255, 255, 255));
        }

    QRgb val[11] = {qRgb(254, 254, 254), qRgb(255, 153, 128), qRgb(251, 231, 178),
                   qRgb(241, 231, 136), qRgb(175, 227, 19), qRgb(252, 128, 165),
                   qRgb(157, 224, 47),  qRgb(147, 223, 184), qRgb(0, 204, 153),
                   qRgb(147, 204, 143), qRgb(118, 110, 200)};

    int count = 0;
    roomInformation addRoom;
    addRoom.index = 0;
    addRoom.name = QString::number(addRoom.index);

    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    for(int i = 0; i <= houseWidth; i++)
        for(int j = 0; j <= houseHeight; j++)
        {
            QColor color(image.pixelColor(i, j));
            // if(roomColor[i][j] == 0)
            if(color.blue() == 255 && color.red() == 255 && color.green() == 255
                    && roomColor[i][j] != -5)
            {
                std::queue<std::pair<int, int> > temp;
                temp.push(std::make_pair(i, j));
                while(1)
                {
                    if(temp.empty())
                    {
                        roomList.push_back(addRoom);
                        if(addRoom.index)
                        {
                            ui->listWidget->addItem(addRoom.name);
                            ui->listWidget_2->addItem("");
                            ui->listWidget_2->item(addRoom.index - 1)->setBackground(
                                        QBrush(val[addRoom.index] ,Qt::SolidPattern));
                        }
                        addRoom.index = ++count;
                        addRoom.name = QString::number(addRoom.index);
                        addRoom.hasDoor = false;
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
                        if(roomColor[x][y] == -5) continue;
                        if(color2 == qRgb(51, 255, 255) || color2 == qRgb(255, 127, 0))
                        {
                            addRoom.hasDoor = true;
                        }
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

    for(auto index : experiorWall)
    {
        int tx1 = index->line().toLine().x1() < index->line().toLine().x2() ?
                    index->line().toLine().x1() : index->line().toLine().x2();
        int tx2 = tx1 == index->line().toLine().x2() ?
                    index->line().toLine().x1() : index->line().toLine().x2();
        int ty1 = index->line().toLine().y1() < index->line().toLine().y2() ?
                    index->line().toLine().y1() : index->line().toLine().y2();
        int ty2 = ty1 == index->line().toLine().y2() ?
                    index->line().toLine().y1() : index->line().toLine().y2();
        for(int i = tx1; i <= tx2; i++)
            for(int j = ty1; j <= ty2; j++)
            {
                QColor color2(image.pixelColor(i, j));
                if(color2 == qRgb(51, 255, 255) || color2 == qRgb(255, 127, 0))
                {
                    goto ABC;
                }
            }
        if(index == experiorWall[3])
        {
            ui->alertLabel->setText("Any Room must have a door or window.");
            break;
        }
    }

    ABC:

    for(size_t i = 1; i < roomList.size(); i++)
    {
        if(!roomList[i].hasDoor)
        {
            ui->alertLabel->setText("Any Room must have a door or window.");
            break;
        }
        if(i == roomList.size() - 1)
            ui->alertLabel->setText("");
    }
}

void MainWindow::loadFunction()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();

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
        int tx1 = index->line().toLine().x1() < index->line().toLine().x2() ?
                    index->line().toLine().x1() : index->line().toLine().x2();
        int tx2 = tx1 == index->line().toLine().x2() ?
                    index->line().toLine().x1() : index->line().toLine().x2();
        int ty1 = index->line().toLine().y1() < index->line().toLine().y2() ?
                    index->line().toLine().y1() : index->line().toLine().y2();
        int ty2 = ty1 == index->line().toLine().y2() ?
                    index->line().toLine().y1() : index->line().toLine().y2();
        for(int i = tx1; i <= tx2; i++)
            for(int j = ty1; j <= ty2; j++)
                image.setPixelColor(i, j, qRgb(0, 0, 255));
    }

    for(auto index : interiorWall)
    {
        int tx1 = index->line().toLine().x1() < index->line().toLine().x2() ?
                    index->line().toLine().x1() : index->line().toLine().x2();
        int tx2 = tx1 == index->line().toLine().x2() ?
                    index->line().toLine().x1() : index->line().toLine().x2();
        int ty1 = index->line().toLine().y1() < index->line().toLine().y2() ?
                    index->line().toLine().y1() : index->line().toLine().y2();
        int ty2 = ty1 == index->line().toLine().y2() ?
                    index->line().toLine().y1() : index->line().toLine().y2();
        for(int i = tx1; i <= tx2; i++)
            for(int j = ty1; j <= ty2; j++)
                image.setPixelColor(i, j, qRgb(255, 0, 0));
    }

    for(auto index : windowList)
    {
        if(index->line().toLine().x1() == index->line().toLine().x2())
        {
            int ty1 = index->line().toLine().y1() < index->line().toLine().y2() ?
                        index->line().toLine().y1() : index->line().toLine().y2();
            int ty2 = ty1 == index->line().toLine().y2() ?
                        index->line().toLine().y1() : index->line().toLine().y2();
            for(int i=index->line().toLine().x1() - 10; i<=index->line().toLine().x1() + 10; i++)
                for(int j=ty1 - 10; j<=ty2 + 10; j++)
                    image.setPixel(i, j, qRgb(51, 255, 255));
        }
        else
        {
            int tx1 = index->line().toLine().x1() < index->line().toLine().x2() ?
                        index->line().toLine().x1() : index->line().toLine().x2();
            int tx2 = tx1 == index->line().toLine().x2() ?
                        index->line().toLine().x1() : index->line().toLine().x2();
            for(int i=index->line().toLine().y1() - 10; i<=index->line().toLine().y1() + 10; i++)
                for(int j=tx1-10; j<=tx2+10; j++)
                    image.setPixel(j, i, qRgb(51, 255, 255));
        }
    }

    for(auto index : doorList)
    {
        if(index->line().toLine().x1() == index->line().toLine().x2())
        {
            int ty1 = index->line().toLine().y1() < index->line().toLine().y2() ?
                        index->line().toLine().y1() : index->line().toLine().y2();
            int ty2 = ty1 == index->line().toLine().y2() ?
                        index->line().toLine().y1() : index->line().toLine().y2();
            for(int i=index->line().toLine().x1() - 10; i<=index->line().toLine().x1() + 10; i++)
                for(int j=ty1-10; j<=ty2+10; j++)
                    image.setPixel(i, j, qRgb(255, 127, 0));
        }
        else
        {
            int tx1 = index->line().toLine().x1() < index->line().toLine().x2() ?
                        index->line().toLine().x1() : index->line().toLine().x2();
            int tx2 = tx1 == index->line().toLine().x2() ?
                        index->line().toLine().x1() : index->line().toLine().x2();
            for(int i=index->line().toLine().y1() - 10; i<=index->line().toLine().y1() + 10; i++)
                for(int j=tx1-10; j<=tx2+10; j++)
                    image.setPixel(j, i, qRgb(255, 127, 0));
        }
    }

    pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
}


void MainWindow::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Schematic"), "",
                                                    tr("Schematic(*.sch);;All Files (*)"));
    if(fileName.isEmpty()) return;
    else {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QTextStream out(&file);

        out << "house " << houseWidth << " " << houseHeight << endl;
        for(auto i : this->furniture)
            out << "hash " << i.getName() << " " << i.getImageDir() << endl;
        for(int i  = 0; i < this->ui->listWidget->count(); i++ )
            out << "list " << this->ui->listWidget->item(i)->text() << endl;
        for(auto i : this->experiorWall)
            out << "exper " << i->line().x1() << " " << i->line().y1() << " " << i->line().x2() << " " << i->line().y2() << endl;
        for(auto i : this->interiorWall)
            out << "inter " << i->line().x1() << " " << i->line().y1() << " " << i->line().x2() << " " << i->line().y2() << endl;
        for(auto i : this->windowList)
            out << "wind " <<  i->line().x1() << " " << i->line().y1() << " " << i->line().x2() << " " << i->line().y2() << endl;
        for(auto i : this->doorList)
            out << "door " <<  i->line().x1() << " " << i->line().y1() << " " << i->line().x2() << " " << i->line().y2() << endl;

        file.close();
    }
}

void MainWindow::on_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Schematic"), "",
                                                    tr("Schematic(*.sch);;All Files (*)"));
    if(fileName.isEmpty()) return;
    else {
        QFile file(fileName);

        if(!file.open(QIODevice::ReadOnly  | QIODevice::Text)){
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
            this->furniture.insert("refrigerator", Furniture("refrigerator",
                          "refri.PNG"));
            this->furniture.insert("laundry", Furniture("laundry",
                          "laun.PNG"));
            for(auto i : this->furniture)
                this->ui->FurnitureList->addItem(i.getName());
        }
        QTextStream in(&file);
        QString temp;
        this->on_ResetButton_clicked();
        this->furniture.clear();
        this->ui->FurnitureList->clear();
        do{
            QString tag;
            in >> tag;
            if(tag == "hash"){
                QString name;
                QString img_src;
                in >> name >> img_src;
                this->furniture.insert(name, Furniture(name, img_src));
                this->ui->FurnitureList->addItem(name);
            }
            else if(tag == "list"){
                QString temp;
                in >> temp;
                qDebug() << temp;
                this->ui->listWidget->addItem(temp);
            }
            else if(tag == "exper"){
                QPen outlinePen(Qt::red);
                QBrush brush(Qt::red);
                int x1, y1, x2, y2;
                in >> x1 >> y1 >> x2 >> y2;
                this->experiorWall.push_back(scene->addLine(x1, y1, x2, y2, outlinePen));
            }
            else if(tag == "inter"){
                QPen outlinePen(Qt::red);
                outlinePen.setWidth(1);
                int x1, y1, x2, y2;
                in >> x1 >> y1 >> x2 >> y2;
                this->interiorWall.push_back(scene->addLine(x1, y1, x2, y2, outlinePen));
            }
            else if(tag == "wind"){
                QPen outlinePen(qRgb(51, 255, 255));
                outlinePen.setWidth(20);
                int x1, y1, x2, y2;
                in >> x1 >> y1 >> x2 >> y2;
                this->windowList.push_back(scene->addLine(x1, y1, x2, y2, outlinePen));
            }
            else if(tag == "door"){
                QPen outlinePen(qRgb(255, 127, 0));
                outlinePen.setWidth(20);
                int x1, y1, x2, y2;
                in >> x1 >> y1 >> x2 >> y2;
                this->doorList.push_back(scene->addLine(x1, y1, x2, y2, outlinePen));
            }
            else if(tag == "house"){
                int width, height;
                in >> width >> height;
                this->ui->lineEdit->setText(QString::number(width/10));
                this->ui->lineEdit_2->setText(QString::number(height/10));
                qDebug() << width << " " << height << endl;
           }
        }while(!in.atEnd());
        file.close();
        this->on_EnterButton_clicked();
    }
}

void MainWindow::on_extraction_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Schematic"), "",
                                                    tr("image(*.png);;All Files (*)"));
    if(fileName.isEmpty())
        return ; // invalid state
    else {
        QPixmap pix = QPixmap::grabWidget(this->ui->graphicsView);
        pix.save(fileName);
    return; // success}
    }
}

void MainWindow::on_FurnitureList_itemDoubleClicked(QListWidgetItem *item)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Change key data"),
                                         tr("name: "), QLineEdit::Normal,
                                         item->text(), &ok);
    if(ok && !text.isEmpty()){
        this->furniture[item->text()].setName(text);
        this->furniture.insert(text,this->furniture[item->text()]);
        this->furniture.remove(text);
        item->setText(text);
    }
}

void MainWindow::on_newfile_clicked()
{
    this->scene->clear();
    this->furniture.clear();
    this->roomList.clear();
    this->experiorWall.clear();
    this->interiorWall.clear();
    this->windowList.clear();
    this->doorList.clear();
    this->ui->listWidget->clear();
    this->ui->FurnitureList->clear();
    this->on_ResetButton_clicked();
}

void MainWindow::on_FurnitureList_itemSelectionChanged()
{
    if(!startDrawing) return;

    QInputDialog *dial;
    bool ok;
    QString scale = dial->getText(this, tr("Change key data"),
                              tr("scale: "), QLineEdit::Normal,
                              "", &ok);

    Furniture sample("Sample", QDir().absolutePath()+QString("/") +
                     QString(furniture[ui->FurnitureList->selectedItems().at(0)->text()].getImageDir()));
    QPixmap *map = sample.getImage();
    item = new QGraphicsPixmapItem(*map);
    item->setScale(scale.toDouble());
    imageScale = scale.toDouble();

    ui->label_5->setText("Furniture");
    wallDrawing = 9;
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Change data"),
                                         tr("data: "), QLineEdit::Normal,
                                         item->text(), &ok);
    item->setText(text);
}
