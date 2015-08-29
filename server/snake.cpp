#include <GL/glut.h>

#include "food.h"
#include "snake.h"

Snake::Snake(int _size, int _startPosx, int _startPosy) {

    this->Size = _size;
    this->Direction = GLUT_KEY_UP;

    blocks.push_back(new Block(_startPosx, _startPosy));
    blocks.push_back(new Block(_startPosx, _startPosy-1));
    blocks.push_back(new Block(_startPosx, _startPosy-2));


    blocks.push_back(new Block());
}

bool Snake::move(void) {

    Block *block;
    QList<Block*>::iterator b_it = blocks.end()-1;
    while (b_it != blocks.begin()) {
        block = (*b_it); b_it--;
        block->setPosx((*b_it)->getPosx());
        block->setPosy((*b_it)->getPosy());
    }

    switch (Direction) {
        case GLUT_KEY_UP:
            blocks[0]->addToPosy(1);
            break;
        case GLUT_KEY_LEFT:
            blocks[0]->addToPosx(-1);
            break;
        case GLUT_KEY_RIGHT:
            blocks[0]->addToPosx(1);
            break;
        case GLUT_KEY_DOWN:
            blocks[0]->addToPosy(-1);
            break;
    }

    if (blocks[0]->getPosy() == HEIGHT) {
        emit event(EVENT_MOVE);
        return false;
    } else if (blocks[0]->getPosy() < 0) {
        emit event(EVENT_MOVE);
        return false;
    } else if (blocks[0]->getPosx() < 0) {
        emit event(EVENT_MOVE);
        return false;
    } else if (blocks[0]->getPosx() == WIDTH) {
        emit event(EVENT_MOVE);
        return false;
    }

    return true;
}

bool Snake::eat(QList<Food *> &foods) {
    QList<Food*>::iterator f_it;
    for (f_it = foods.begin(); f_it != foods.end(); f_it++) {
        if ((blocks[0]->getPosx() == (*f_it)->getPosx()) && (blocks[0]->getPosy() == (*f_it)->getPosy())) {
            Size++; (*f_it)->Spawn(); blocks.push_back(new Block());

            emit event(INCREASE);
            return true;
        }
    }
    return false;
}

bool Snake::cut(int _fine) {
    QList<Block*>::iterator b_it;
    for (b_it = blocks.begin()+1; b_it < blocks.end(); b_it++) {
        if ((blocks[0]->getPosx() == (*b_it)->getPosx()) && blocks[0]->getPosy() == (*b_it)->getPosy()) {
            shift();
            QList<Block*>::iterator b_it;
            for (b_it = blocks.end()-1; _fine != 0; b_it++) {
                delete (*b_it);
                blocks.removeAt(Size);
                this->Size--;_fine--;
            }

            emit event(DECREASE);
            return false;
        }
    }
    return true;
}

bool Snake::hunt(Snake *_snk, int _fine) {
    QList<Block*>::iterator b_it;
    for (b_it = _snk->getBlocks().begin(); b_it < _snk->getBlocks().end()-1; b_it++) {
        if ((blocks[0]->getPosx() == (*b_it)->getPosx()) && (blocks[0]->getPosy() == (*b_it)->getPosy())) {  //bite in the neck
            if (_snk->getBlocks().indexOf((*b_it)) == 1) {
                shift();
                emit event(BITE_NECK);
                return false;
            } else if (_snk->getBlocks().at(_snk->getSize()-1) == (*b_it)) {                                 //bite in the tail
                shift(); Size++;
                blocks.push_back(new Block());

                delete _snk->getBlock(_snk->getSize());
                _snk->getBlocks().removeAt(_snk->getSize());
                _snk->decSize();

                emit event(INCREASE);
                return false;
            } else {                                                                                         //bite in the body
                shift();
                QList<Block*>::iterator b_it;
                for (b_it = blocks.end()-1; _fine != 0; b_it++) {
                    delete (*b_it);
                    blocks.removeAt(Size);
                    this->Size--;_fine--;
                }

                emit event(DECREASE);
                return false;
            }
        }

    }
    return true;
}

void Snake::shift(void) {

    Block *block;
    QList<Block*>::iterator f_it = blocks.begin();
    while (f_it != blocks.end()-1) {
        block = (*f_it); f_it++;
        block->setPosx((*f_it)->getPosx());
        block->setPosy((*f_it)->getPosy());
    }
}

void Snake::delBlocks(void) {
    QList<Block*>::iterator s_it = blocks.begin();
    while (s_it != blocks.end()) {
        blocks.erase(s_it); s_it++;
    }
}

QList<Block*> &Snake::getBlocks(void) {
    return blocks;
}

Block *Snake::getBlock(int i) {
    return blocks[i];
}

int Snake::getSize(void) {
    return this->Size;
}

void Snake::setDirect(int _dir) {
    this->Direction = _dir;
}

int Snake::getDirect(void) {
    return this->Direction;
}

void Snake::decSize(void) {
    this->Size--;
}


