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
        Item(int x,int y, int type);
        void moveAnimation();
        void action();
};



#endif
