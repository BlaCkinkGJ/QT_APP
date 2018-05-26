#ifndef FURNITURE_H
#define FURNITURE_H

#include <QPointF>
#include <QRectF>
#include <QDebug>
#include <QPixmap>

class Furniture
{
private:
    QPixmap  *image;
    QString  name;
    QPointF  position;
    QRectF   size;
    QString image_dir;


public:
    Furniture();
    Furniture(const QString& name, const QString imageFileName);

    int setName		(const QString& name);
    int setPosition (const QPointF& position);
    int setSize	    (const QRectF& size);
    int setImage	(const QString& imageFileName);

    QString  getName() 	   const;
    QPointF  getPosition() const;
    QRectF   getSize()     const;
    QPixmap* getImage();
    QString  getImageDir();

    bool isCollide(const QRectF& other);

    ~Furniture();
};

#endif // FURNITURE_H
