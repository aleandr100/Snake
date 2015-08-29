#include "block.h"

Block::Block(int _xPos, int _yPos) {
    this->xPos = _xPos;
    this->yPos = _yPos;
}

Block::Block(void) {
    this->xPos = -1;
    this->yPos = -1;
}

int Block::getPosx(void) {
    return this->xPos;
}

int Block::getPosy(void) {
    return this->yPos;
}

void Block::addToPosx(int _xPos) {
    this->xPos += _xPos;
}

void Block::addToPosy(int _yPos) {
    this->yPos += _yPos;
}

void Block::setPosx(int _xPos) {
    this->xPos = _xPos;
}

void Block::setPosy(int _yPos) {
    this->yPos = _yPos;
}
