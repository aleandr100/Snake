#ifndef SENDER_H
#define SENDER_H

#include <QThread>
#include <QTcpSocket>
#include <QDataStream>
#include <QMetaType>
#include <QDebug>
#include <QUuid>

#include "tcpserver.h"

typedef QList<QPair<QString,Snake*> > PLAYERS_LIST;

Q_DECLARE_METATYPE (PLAYERS_LIST);
Q_DECLARE_METATYPE(QList<Food*>);
Q_DECLARE_METATYPE(QList<QString>);

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(qintptr _socketDescriptor);

    const QString getUuid(void);
    void setState(int _state);

signals:
    void newGame(QString, QString, const QList<QString> &list);
    void startGame(const QString);
    void changeDirect(int, const QString);
    void disconnected(Client*);

    void error(QTcpSocket::SocketError socError);

public slots:
    void sendData(const QList<QPair<QString, Snake*> > &_list, const QList<Food*> &_foods);

    void readyRead(void);
    void rejectClient(void);
    void run(void);

    void gameOver(const QString _msgData, const QString &_winner = 0);
    void sendMessage(const QString _msgData, const QString &_winner = 0);
    void transmit(Client *_client, const QList<QString> &_list);

private:
    bool _state;
    int direction;

    QUuid uuid;

    qintptr socketDescriptor;
    QTcpSocket *tcpSocket;
};

#endif // SENDER_H
