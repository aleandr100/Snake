#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QMetaType>
#include <QDebug>

#include "block.h"

#define WIDTH  35
#define HEIGHT 20

const int EVENT_MOVE = 100;
const int BITE_NECK =  101;

const int DECREASE = 102;
const int INCREASE =  103;

class Food;

class Snake : public QObject
{
    Q_OBJECT
public:
    Snake(int _size, int _startPosx, int _startPosy);

    bool move(void);
    bool eat(QList<Food*> &foods);
    bool cut(int _fine);

    bool hunt(Snake *_snk, int _fine);

    Block *getBlock(int i);

    QList<Block*> &getBlocks(void);

    int getSize(void);

    void setDirect(int _dir);
    int getDirect(void);

    void delBlocks(void);
    void decSize(void);

signals:
    void event(int _event);

private:
    int Size;
    int Direction;

    QList<Block*> blocks;

    void shift(void);
};

#endif // SNAKE_H
