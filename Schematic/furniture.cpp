#include "furniture.h"

Furniture::Furniture(const QString& name, const QString imageFileName):name(name){
    QPixmap *pixmap = new QPixmap(imageFileName);
    this->image = pixmap;
}

int Furniture::setName(const QString &name){
    this->name = name;
    if(this->name.isEmpty()) return -1;
    return 0;
}

int Furniture::setPosition(const QPointF &position){
    this->position = position;
    if(this->position.isNull()) return -1;
    return 0;
}

int Furniture::setSize(const QRectF &size){
    this->size = size;
    if(this->size.isEmpty()) return -1;
    return 0;
}


bool Furniture::isCollide(const QRectF &rect){
    return this->size.intersects(rect);
}

QString Furniture::getName() const{
    return this->name;
}

QPointF Furniture::getPosition() const{
    return this->position;
}

QRectF Furniture::getSize() const{
    return this->size;
}

QPixmap* Furniture::getImage(){
    return this->image;
}

Furniture::~Furniture(){
    delete this->image;
}
