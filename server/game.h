#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QMap>

#include "snake.h"
#include "food.h"

#define EQUAL 100
#define NOT_EQUAL 101

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);

    static const QList<QPair<QString,Snake*> > &getPlayers(void);

    const QList<Food*> &getFoods(void) const;
    Snake *getPlayer(const QString uuid);

    void rmPlayers(void);
    void delPlayer(const QString _uuid);

    void initFruit(void);
    void reInitFruits(void);

    void addPlayerToGame(const QString _uuid);

    QString getUuid(Snake *_snk, int _key);

    QString _cmpSize(void);
    QString _checkInc(Snake *_snk);

    void checkSize(void);

    void resetFlag(void);

    void setMaxSize(int _size);
    void setFine(int _fine);

signals:
    void stop(const QString msgData,const QString &_winner = 0);
    void sendData(const QList<QPair<QString,Snake*> >&, const QList<Food*>&);

public slots:
    void loopGame(void);
    void getWinner(int _event);

private:
    int fine;
    int maxSize;
    bool equal;

    int in;
    int startSize;

    int startPosx[2];
    int startPosy[2];

    QString winner;

    static QList<QPair<QString, Snake*> > players;

    QList<Food*> foods;

    void send(void);
};

#endif // GAME_H
