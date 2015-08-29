#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QMetaType>
#include <QDebug>

#define WIDTH  35
#define HEIGHT 20

#define EVENT_MOVE 100
#define BITE_NECK  101

#define DECREASE 102
#define INCREASE  103

#include "block.h"

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
