#include "sample.h"

sample::sample(int value)
{
    this->value = value;
}

sample::~sample(){
    this->value = 0;
}


int sample::getValue(){
    return this->value;
}

void sample::setValue(QDataStream& stream){
    QString value;
    stream >> value;
    this->value = value.toInt();
}
