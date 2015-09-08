#include <QDebug>

#include "game.h"

QList<QPair<QString, Snake*> > Game::players;

Game::Game(QObject *parent) : QObject(parent) {

    this->equal = false;

    this->in = 0;

    startSize = 3;
    startPosx[0] = (int)(WIDTH / 2);
    startPosy[0] = (int)(HEIGHT / 2);

    startPosx[1] = (int)(WIDTH / 3);
    startPosy[1] = (int)(HEIGHT / 3);

    initFruit();
}

void Game::initFruit(void) {
    this->foods.push_back(new Food(5, 5));
    this->foods.push_back(new Food(10, 15));
}

void Game::reInitFruits(void) {
    QList<Food*>::iterator f_it = foods.begin();
    while (f_it != foods.end()) {
        delete (*f_it);
        foods.erase(f_it);
        f_it++;
    }
    initFruit();
}

void Game::loopGame(void) {
    Snake *_snk = players.last().second;
    QListIterator<QPair<QString, Snake*> > p_it(this->players);
    while (p_it.hasNext()) {
        if (!p_it.peekNext().second->move()) {
            emit stop("+GAME_OVER\r\n", this->winner);
            return;
        }

        if (!p_it.peekNext().second->cut(this->fine)) {
            if (!winner.isEmpty()) {
                send();

                emit stop("+GAME_OVER\r\n", this->winner);
                return;
            }
        }

        if (p_it.peekNext().second->eat(foods)) {
            if (!winner.isEmpty()) {
                send();

                emit stop("+GAME_OVER\r\n", this->winner);
                return;
            }
        }

        if (!p_it.peekNext().second->hunt(_snk, this->fine)) {
            if (!winner.isEmpty()) {
                send();

                emit stop("+GAME_OVER\r\n", this->winner);
                return;
            }
        }

        _snk = p_it.peekNext().second;

        p_it.next();
    }

    checkSize();
    if (!winner.isEmpty()) {
        send();

        emit stop("+GAME_OVER\r\n", this->winner);
        return;
    }

    send();
}

void Game::send(void) {
    emit sendData(getPlayers(), getFoods());
}

void Game::getWinner(int _event) {
    Snake *_snk = (Snake*)sender();
    switch (_event) {
       case EVENT_MOVE: this->winner = getUuid(_snk,NOT_EQUAL);
                        break;
       case BITE_NECK:  this->winner = getUuid(_snk,EQUAL);
                        break;
       case INCREASE:   this->winner = _checkInc(_snk);
                        break;
       case DECREASE:   this->winner = _cmpSize();
                        break;
       default:
                        break;
    }
}

QString Game::getUuid(Snake *_snk, int _key) {
    QListIterator<QPair<QString,Snake*> > p_it(this->players);
    while (p_it.hasNext()) {
        if (_key == NOT_EQUAL) {
            if (p_it.peekNext().second != _snk) {
                return p_it.peekNext().first;
            }
        } else if (_key == EQUAL) {
            if (p_it.peekNext().second == _snk) {
                return p_it.peekNext().first;
            }
        }

        p_it.next();
    }
    return NULL;
}

QString Game::_checkInc(Snake *_snk) {
    if (equal) {
        return getUuid(_snk,EQUAL);
    }
    return NULL;
}

void Game::checkSize(void) {
    int _first = players[0].second->getSize();
    int _second = players[1].second->getSize();

    if ((_first == this->maxSize) && (_second == this->maxSize)) {
        this->equal = true;
    } else if (_first == this->maxSize) {
        this->winner = players[0].first;
    } else if (_second == this->maxSize) {
        this->winner = players[1].first;
    }
}

QString Game::_cmpSize(void) {

    Snake *_first = players[0].second;
    Snake *_second = players[1].second;

    if (_first->getSize() > _second->getSize()) {
        return players[0].first;
    } else if (_second->getSize() > _first->getSize()) {
        return players[1].first;
    }
    return NULL;
}

const QList<QPair<QString,Snake*> > &Game::getPlayers(void) {
    return players;
}

void Game::addPlayerToGame(const QString uuid) {
    if (players.size() == 2) {
        rmPlayers();
        reInitFruits();
    }
    Snake *_snk = new Snake(startSize,startPosx[in],startPosy[in]);
    connect(_snk, SIGNAL(event(int)), this, SLOT(getWinner(int)));
    players.append(qMakePair(QString(uuid),_snk));
    in++;
}

Snake *Game::getPlayer(const QString _uuid) {
    QListIterator<QPair<QString,Snake*> > p_it(this->players);
    while (p_it.hasNext()) {
        if (p_it.peekNext().first == _uuid){
            return p_it.peekNext().second;
        }
        p_it.next();
    }
    return NULL;
}

const QList<Food*> &Game::getFoods(void) const {
    return this->foods;
}

void Game::rmPlayers(void) {
    this->in = 0;
    QList<QPair<QString,Snake*> >::iterator p_it = players.begin();
    while (p_it != players.end()) {
        delPlayer((*p_it).first);
        p_it++;
    }
    players.clear();
}

void Game::delPlayer(const QString _uuid) {
    QList<QPair<QString,Snake*> >::iterator p_it = players.begin();
    while (p_it != players.end()) {
        if ((*p_it).first == _uuid) {
            (*p_it).second->delBlocks();
            players.erase(p_it);
            return;
        }
        p_it++;
    }
}

void Game::resetFlag(void) {
    this->equal = false;
    this->winner.clear();
}

void Game::setMaxSize(int _size) {
    this->maxSize =_size;
}

void Game::setFine(int _fine) {
    this->fine = _fine;
}






