#ifndef SAMPLE_H
#define SAMPLE_H

#include<QDataStream>

class sample
{

public:
    sample(int value);
    virtual ~sample();
    int value;
    int getValue();
    void setValue(QDataStream& stream);
};

#endif // SAMPLE_H
