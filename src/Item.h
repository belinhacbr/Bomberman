#ifndef ITEM_H
#define ITEM_H

#define SHOW    0
#define HIDE    1
#define PICK    2

#define BOMBPLUS    '0'
#define FIREPOWER   '1'
#define KEY         'K'
class Item{
    private:
    public:
        int x;
        int y;
        int type;
        int frame;
        int state;
        int dx0;
        int dy0;
        int colorkey;
        Item(int x,int y, int type, int dx0, int dy0);
        void moveAnimation();
        void action();
};



#endif
