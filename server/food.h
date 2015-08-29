#ifndef FOOD_H
#define FOOD_H

class Snake;

class Food {

    int xPos, yPos;
public:
    Food(int _xPos, int _yPos);
    Food(void);

    void Spawn(void);

    int getPosx(void);
    int getPosy(void);
};

#endif // FOOD_H
