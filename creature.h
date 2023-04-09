#ifndef CREATURE_H
#define CREATURE_H
#include"config.h"
#include<QPixmap>
#include<QPainter>
#include<QRect>


class Creature  //负责所有生物（怪物英雄等）的虚基类
{
public:
    int hp;
    int damage;
    int attackcooltime = 0;
    bool isfaceingright = true;
    bool iscooltime = false;
    int xspeed;
    int yspeed = 0;
    int x;
    int y;
    int width;
    int height;
    int deathframe = 0;
    int walkingpixmapsection = 0;
    int maxwalkingcooltime = 0;
    int deathpixmapsection = 0;
    int maxdeathcooltime = 0;
    int attackpixmapsection = 0;
    int maxattackcooltime = 0;
    QRect rect;
    QRect sensor;
    QRect attackrange;
    int frame = 0;
    QPixmap pixmap;
    bool gravityinfluence = true;
    int typenum = 0;
public:
    Creature(int thp,int tspeed,int tx,int ty,int twidth,int theight);
    void updateRectPosition();
    virtual void updateStatement(){}


};

class Hero:public Creature  //英雄类
{
public:
    int heroacc;
    int shootcooltime = 0;
    bool isshootingcooltime = false;
    int stonenum = 10;
public:
    QPixmap Getheropmp();
    Hero(int tx,int ty);
    void updateRectPosition();
    void updateHeroCooltime();
    virtual void updateStatement(){}
};

class BasicMonster: public Creature //小怪类
{
public:
    BasicMonster(int tx,int ty);
    void updateRectPosition();
    virtual void updateStatement();
};

class StrongMonster: public Creature //大怪类
{
public:
    StrongMonster(int tx,int ty);
    void updateRectPosition();
    virtual void updateStatement();
};

class Mage: public Creature         //远程怪类
{
public:
    Mage(int tx,int ty);
    void updateRectPosition();
    virtual void updateStatement();
};

class Goal:public Creature               //终点类
{
public:
    Goal(int tx,int ty);
    void updateRectPosition();
    virtual void updateStatement(){}
};

#endif // CREATURE_H


