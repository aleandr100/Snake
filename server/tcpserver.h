#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTimer>
#include <QReadWriteLock>

#include "game.h"

class Client;

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(int _maxConnections, QObject *parent = 0);

    void startServer(void);
    void startGame(void);
    void regPlayer(QString uuid, Client *_client, const QList<QString> &_list);

    int isRunning(void);
    void resetFlag(void);
    const QString &getColor(void);
    void freeColor(void);

    void resetState(void);

signals:
    void sendData(const QList<QPair<QString,Snake*> >&, const QList<Food*>&);
    void endOfGame(const QString msgData, const QString &_winner = 0);
    void transmit(Client*,const QList<QString> &_list);

public slots:
    void newGame(QString msgData, QString uuid, const QList<QString> &list);
    void readyToStart(const QString msgData);

    void stopGame(QString _msgData, QString _win = 0);

    void setDirect(int _direction, const QString uuid);
    void removeClient(Client *_client);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    bool isInit;
    int order;
    int delay;

    QString level;

    int maxConnections;
    short int flag;

    Game *game;
    QTimer *timer;

    QReadWriteLock lock;

    QTcpServer *tcpServer;
    QMap<Client*,QThread*> threadPool;   

    QList<QPair<QString,int> > colors;

    QMap<QString,int> levels;

    void setLevel(QString _level);
};

#endif // SERVER_H
