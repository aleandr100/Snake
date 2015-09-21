#include "client.h"
#include "tcpserver.h"

const int FREE = 100;
const int BUSY = 101;

#define WRITELOCK(x) lock.lockForWrite(); (x); lock.unlock()

TcpServer::TcpServer(int _maxConnections, QObject *parent) : QTcpServer(parent) {
    game = new Game;

    this->isInit = false;

    this->order = 0;
    this->flag = -1;

    this->maxConnections = _maxConnections;

    colors.append(qMakePair(QString("PURPLE"),FREE));
    colors.append(qMakePair(QString("BLUE"),FREE));

    levels.insert("Low",300);
    levels.insert("Medium",250);
    levels.insert("High",150);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),game,SLOT(loopGame()));
    connect(game, SIGNAL(stop(QString,QString)),this,SLOT(stopGame(QString,QString)));

    connect(game, SIGNAL(sendData(QList<QPair<QString,Snake*> >,QList<Food*>)), this, SIGNAL(sendData(QList<QPair<QString,Snake*> >,QList<Food*>)));
}

void TcpServer::startServer(void) {
    if (!this->listen(QHostAddress::Any, 3425)) {
        qDebug() << "Server could not start!";
        tcpServer->close();
        return;
    } else {
        qDebug() << "Server started!";
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor) {

    if (threadPool.size() < maxConnections) {
        QThread *thread = new QThread;
        Client *client = new Client(socketDescriptor);
        client->moveToThread(thread);

        connect(thread, SIGNAL(started()), client, SLOT(run()));

        connect(client, SIGNAL(newGame(QString, QString, QList<QString>)),this,SLOT(newGame(QString, QString, QList<QString>)));
        connect(client, SIGNAL(startGame(QString)),this,SLOT(readyToStart(QString)));
        connect(this, SIGNAL(sendData(QList<QPair<QString,Snake*> >,QList<Food*>)), client, SLOT(sendData(QList<QPair<QString,Snake*> >,QList<Food*>)));

        connect(this, SIGNAL(transmit(Client*,QList<QString>)), client, SLOT(transmit(Client*,QList<QString>)));

        connect(client, SIGNAL(changeDirect(int,QString)), this, SLOT(setDirect(int,QString)));
        connect(client, SIGNAL(disconnected(Client*)), this, SLOT(removeClient(Client*)));
        connect(this, SIGNAL(endOfGame(QString,QString)), client, SLOT(gameOver(QString,QString)));                  //end of the game

        thread->start();

        WRITELOCK(threadPool.insert(client,thread));
    }
}

void TcpServer::removeClient(Client *_client) {

    this->order--;

    disconnect(this, SIGNAL(endOfGame(QString)), _client, SLOT(gameOver(QString)));

    game->delPlayer(_client->getUuid());

    if (isRunning()) stopGame("+CRASH_GAME\r\n");
    lock.lockForWrite();
    QMap<Client*,QThread*>::iterator t_it = threadPool.find(_client);
    if (t_it != threadPool.end()) {
        t_it.value()->quit();
        t_it.value()->wait();
        delete t_it.value();
        threadPool.erase(t_it);
    }
    lock.unlock();
    delete _client;
}

void TcpServer::startGame(void) {
    timer->start(this->delay);
}

void TcpServer::stopGame(QString _msgData, QString _winner) {

    timer->stop();
    resetFlag();

    resetState();
    freeColor();

    QThread::currentThread()->msleep(150);
    emit endOfGame(_msgData, _winner);
}

void TcpServer::regPlayer(QString uuid, Client *_client, const QList<QString> &_list) {
    game->addPlayerToGame(uuid);

    emit transmit(_client, _list);
}

void TcpServer::newGame(QString msgData, QString uuid, const QList<QString> &list) {
    if (msgData == "+NEW_GAME\r\n") {
        bool ok;

        if (!isInit) {
            game->setMaxSize(list.at(0).toInt(&ok,10));
            game->setFine(list.at(1).toInt(&ok,10));
            setLevel(list.at(2));
            isInit = true;
        }

        QList<QString> list;
        Client *client = (Client*)sender();

        list.append(this->level);
        list.append(getColor());
        list.append(QString::number(this->order++));

        regPlayer(uuid, client, list);
        QThread::currentThread()->msleep(150);

        emit sendData(game->getPlayers(), game->getFoods());
    }
}

void TcpServer::readyToStart(const QString msgData)  {
    if (msgData == "+START_GAME\r\n") {
        if ((++this->flag) > 0) {
            startGame();
        }
    }
}

void TcpServer::setDirect(int _direction, const QString uuid) {
    game->getPlayer(uuid)->setDirect(_direction);
}

const QString &TcpServer::getColor(void) {
    QList<QPair<QString,int> >::iterator c_it = this->colors.begin();
    while (c_it != this->colors.end()) {
        if ((*c_it).second == FREE){
            (*c_it).second = BUSY;
            return (*c_it).first;
        }
        c_it++;
    }
    return NULL;
}

void TcpServer::freeColor(void) {
    QList<QPair<QString,int> >::iterator c_it = this->colors.begin();
    while (c_it != this->colors.end()) {
        if ((*c_it).second == BUSY){
            (*c_it).second = FREE;
        }
        c_it++;
    }
}

void TcpServer::resetState(void) {
    QMap<Client*,QThread*>::iterator t_it = threadPool.begin();
    while (t_it != threadPool.end()) {
        t_it.key()->setState(false);
        t_it++;
    }
}

int TcpServer::isRunning(void) {
    return (this->flag > 0) ? 1 : 0;
}

void TcpServer::resetFlag(void) {
    this->flag = -1;
    this->order = 0;
    this->isInit = false;

    game->resetFlag();
}

void TcpServer::setLevel(QString _level) {
    this->level = _level;
    this->delay = levels[_level];
}






