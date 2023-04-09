#ifndef BULLETS_H
#define BULLETS_H
#include "creature.h"

class Bullet
{
public:
    int x = 0;
    int y = 0;
    double xspeed = 0;
    double yspeed = 0;
    int width = 0;
    int height = 0;
    int damage = 0;
    int pixtimer = 0;
    bool isally = true;
    int typenum = 0;
    bool isblockpassable = false;
    QRect rect;
    QPixmap pixmap;
    bool gravityinfluence = false;
public:
    virtual void updateStatement(){}
};




class HeroBullet:public Bullet
{
public:
    HeroBullet(int tx,int ty);
    virtual void updateStatement();
};

class MageBullet:public Bullet
{
public:
    MageBullet(int tx,int ty);
    virtual void updateStatement();
};

class HpItem:public Bullet                    // 药包，继承了子弹类
{
public:
    bool pixtimerisup = true;
public:
    HpItem(int tx,int ty);
    virtual void updateStatement();
};

class Stone:public Bullet                           //同上
{
public:
    Stone(int tx,int ty);
    virtual void updateStatement();
};



#endif // BULLETS_H
