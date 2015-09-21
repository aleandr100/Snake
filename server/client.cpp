#include "client.h"

Client::Client(qintptr _socketDescriptor) {

    this->_state = false;
    this->socketDescriptor = _socketDescriptor;
}

void Client::run(void) {

    tcpSocket = new QTcpSocket;
    if (!tcpSocket->setSocketDescriptor(this->socketDescriptor)) {
        emit error(tcpSocket->error());
        return;
    }

    qRegisterMetaType<QList<QPair<QString,Snake*> > >("QList<QPair<QString,Snake*> >");
    qRegisterMetaType<QList<Food*> >();
    qRegisterMetaType<QList<QString> >();

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()),Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(rejectClient()));
}

void Client::readyRead(void) {

    QByteArray block;
    QDataStream inStream(tcpSocket);

    QDataStream outStream(&block, QIODevice::WriteOnly);

    if (_state) {
        QByteArray block;
        quint16 _direction;

        inStream >> _direction;
        inStream >> block;

        emit changeDirect(_direction, block.constData());
    } else {
        QString msgData;

        inStream >> block;
        msgData = block.constData();

        if (msgData == "+REGISTER\r\n") {                       /* register client */
            this->uuid = QUuid::createUuid();
            outStream << "+OK\r\n";
            outStream << uuid.toString().toStdString().c_str();

            tcpSocket->write(block);
        } else if (msgData == "+START_GAME\r\n") {              /* start game */

            emit startGame("+START_GAME\r\n");
            this->_state = true;
        } else if (msgData == "+NEW_GAME\r\n") {                /* new game */
            QString level; int size, fine;

            QList<QString> list;

            inStream >> size >> fine >> level;

            list << QString::number(size);
            list << QString::number(fine);
            list << level;

            emit newGame(msgData, uuid.toString(), list);
        }
    }
}

void Client::sendData(const QList<QPair<QString,Snake*> > &_list, const QList<Food*> &_foods) {

    QByteArray block;
    QDataStream outStream(&block, QIODevice::WriteOnly);

    int _size;

    QList<Block*>::const_iterator s_it;

    QPair<QString,Snake*> item;
    foreach (item, _list) {
         _size = item.second->getBlocks().size();

         outStream << quint16(_size*sizeof(int)-4);

         s_it = item.second->getBlocks().begin();
         while (s_it != item.second->getBlocks().end()-1) {

             outStream << (*s_it)->getPosx() << (*s_it)->getPosy();
             ++s_it;
         }
    }

    _size = _foods.size();
    outStream << quint16(_size*sizeof(int));

    QList<Food*>::const_iterator f_it = _foods.begin();
    while (f_it != _foods.end()) {
        outStream << (*f_it)->getPosx() << (*f_it)->getPosy();
        ++f_it;
    }

    outStream << quint16(0xFFFF);

    tcpSocket->write(block);
}

void Client::gameOver(const QString _msgData, const QString &_winner) {

    QByteArray block;
    QDataStream stream(&block, QIODevice::WriteOnly);

    stream << quint8(0x0000);

    tcpSocket->write(block);

    tcpSocket->waitForBytesWritten(30000);
    QThread::currentThread()->msleep(50);

    sendMessage(_msgData, _winner);
}

void Client::sendMessage(const QString _msgData, const QString &_winner) {

    QByteArray block;
    QDataStream stream(&block, QIODevice::WriteOnly);

    stream << _msgData.toStdString().c_str();

    if (!_winner.isEmpty()) stream << _winner.toStdString().c_str();

    tcpSocket->write(block);
}

void Client::transmit(Client *_client, const QList<QString> &_list) {
    bool ok;

    QByteArray block;
    QDataStream outStream(&block, QIODevice::WriteOnly);

    if (_client == this) {
        outStream << "+TRANSMIT\r\n";

        outStream << _list.at(0).toStdString().c_str();
        outStream << _list.at(1).toStdString().c_str();
        outStream << _list.at(2).toInt(&ok,10);

        tcpSocket->write(block);
    }
}

void Client::rejectClient(void) {
    tcpSocket->close();
    tcpSocket->deleteLater();

    emit disconnected(this);
}

const QString Client::getUuid(void) {
    return this->uuid.toString();
}

void Client::setState(int _state) {
    this->_state = _state;
}

