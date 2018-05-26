#ifndef BUFFER_H
#define BUFFER_H

#include <QDataStream>

class buffer
{
public:
    buffer();

    void writeToFile(QDataStream& stream);
    void readFromFile(QDataStream& stream);

private:
    // save data
};

#endif // BUFFER_H
