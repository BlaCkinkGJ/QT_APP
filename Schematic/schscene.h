#ifndef SCHSCENE_H
#define SCHSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QDebug>


class SchScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SchScene(QObject *parent = 0);
    QGraphicsPixmapItem* item;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SCHSCENE_H
