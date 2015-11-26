#ifndef BOMB_H
#define BOMB_H

#define SET     0
#define EXPLODE 1
#define ASH     2
class Bomb {
private:
public:
    int x;
    int y;
    int range;
    int frame;
    int timer;
    int state;
    bool up,down,left,right;
    Bomb(int x, int y, int range);
    void moveAnimation();
    void action();
};

#endif
