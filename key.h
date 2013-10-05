#ifndef KEY_H
#define KEY_H

#include <QString>
#include <QList>

#include "sha2.h"

class Key
{
private:
    SHA2 mySHA;

public:
    QString magic;
    quint8 map[256][256];
    quint8 x, y, start;
    QList<quint8> directions;

    Key();
    QString getCode();
};

#endif // KEY_H
