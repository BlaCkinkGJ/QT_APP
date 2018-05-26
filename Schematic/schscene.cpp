#include "schscene.h"

SchScene::SchScene(QObject *parent) : QGraphicsScene(parent){
    this->item = nullptr;
}

void SchScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    //QGraphicsScene::mouseMoveEvent(event);
    static qint64 hello = 0;
    qDebug() << hello++ << " : "<< event->scenePos() << endl;
    if(item != nullptr){
        this->item->setPos(event->scenePos() - QPointF(+60.0, 0.0));
    }
}
