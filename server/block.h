#ifndef BLOCK_H
#define BLOCK_H

class Block {

    int xPos, yPos;
public:
    Block(int _xPos, int _yPos);

    Block(void);

    int getPosx(void);
    int getPosy(void);

    void addToPosx(int _xPos);
    void addToPosy(int _yPos);

    void setPosx(int _xPos);
    void setPosy(int _yPos);
};

#endif // BLOCK_H
