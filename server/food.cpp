#include "food.h"
#include "game.h"

Food::Food(int _xPos, int _yPos) {
    this->xPos = _xPos;
    this->yPos = _yPos;
}

Food::Food(void) {
    this->xPos = -1;
    this->yPos = -1;
}

void Food::Spawn(void) {
    this->xPos = (int)(rand() % WIDTH);
    this->yPos = (int)(rand() % HEIGHT);

    QList<Block*>::const_iterator b_it;
    QList<QPair<QString,Snake*> >::const_iterator p_it;

    for (p_it = Game::getPlayers().begin(); p_it < Game::getPlayers().end(); p_it++) {
        b_it = (*p_it).second->getBlocks().begin();
        while (b_it < (*p_it).second->getBlocks().end()-1) {
            if (((*b_it)->getPosx() == this->xPos) && ((*b_it)->getPosy() == this->yPos)) {
                Spawn();
            }
            b_it++;
        }
    }
}

int Food::getPosx(void) {
    return this->xPos;
}

int Food::getPosy(void) {
    return this->yPos;
}
