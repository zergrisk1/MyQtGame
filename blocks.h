#ifndef BLOCKS_H
#define BLOCKS_H
#include "creature.h"
class Block:public Creature                   //方块类
{
public:
    QRect rect;
public:
    Block(int tx,int ty);
    virtual void updateStatement(){}
};

class PurpleBlock:public Block
{
public:
    QRect rect;
    int original_x = 0;
    bool istoleft = false;
public:
    PurpleBlock(int tx,int ty);
    virtual void updateStatement();
};

class LongBlock:public Block
{
public:
    QRect rect;
public:
    LongBlock(int tx,int ty);
    virtual void updateStatement(){}
};

class BreakableBlock:public Block
{
public:
    QRect rect;
public:
    BreakableBlock(int tx,int ty);
    virtual void updateStatement();
};

class SpringBlock:public Block
{
public:
    QRect rect;
public:
    SpringBlock(int tx,int ty);
    virtual void updateStatement(){}
};

#endif // BLOCKS_H
