#include"blocks.h"


Block::Block(int tx,int ty)
    :Creature(INT_MAX,0,tx,ty,BLOCK_WIDTH,BLOCK_WIDTH)
{
    gravityinfluence = false;
    pixmap.load(BLOCK_PIXMAP);
    rect.setWidth(pixmap.width());
    rect.setHeight(pixmap.height());
    rect.moveTo(tx,ty);
    typenum = 4;
}

LongBlock::LongBlock(int tx,int ty)
    :Block(tx,ty)
{
    gravityinfluence = false;
    pixmap.load(LONG_BLOCK_PIXMAP);
    width = 500;
    height = BLOCK_WIDTH;
    rect.setWidth(500);
    rect.setHeight(pixmap.height());
    rect.moveTo(tx,ty);
    typenum = 8;
}

PurpleBlock::PurpleBlock(int tx,int ty)
    :Block(tx,ty)
{
    hp = INT_MAX;
    xspeed = 0;
    width = BLOCK_WIDTH;
    height = BLOCK_WIDTH;
    gravityinfluence = false;
    pixmap.load(PURPLEBLOCK_PIXMAP);
    rect.setWidth(pixmap.width());
    rect.setHeight(pixmap.height());
    rect.moveTo(tx,ty);
    typenum = 5;
    original_x = tx;
}

void PurpleBlock::updateStatement()
{
    if(istoleft)
    {
        x -= 2;
    }
    else
    {
        x += 2;
    }
    if(original_x - x >= 200)
    {
        istoleft = false;
    }
    else if(original_x - x <= -200)
    {
        istoleft = true;
    }
}

BreakableBlock::BreakableBlock(int tx,int ty)
    :Block(tx,ty)
{
    hp = HERO_DAMAGE*6;
    xspeed = 0;
    width = BLOCK_WIDTH;
    height = BLOCK_WIDTH;
    gravityinfluence = false;

    pixmap.load(BREAKABLEBLOCK1_PIXMAP);

    rect.setWidth(pixmap.width());
    rect.setHeight(pixmap.height());
    rect.moveTo(tx,ty);
    typenum = 6;
}

void BreakableBlock::updateStatement()
{
    if(BreakableBlock::hp>4*HERO_DAMAGE)
    {
        pixmap.load(BREAKABLEBLOCK1_PIXMAP);
    }
    else if(BreakableBlock::hp<= HERO_DAMAGE * 4 &&BreakableBlock::hp > HERO_DAMAGE * 2)
    {
        pixmap.load(BREAKABLEBLOCK2_PIXMAP);
    }
    else
    {
        pixmap.load(BREAKABLEBLOCK3_PIXMAP);
    }
}

SpringBlock::SpringBlock(int tx,int ty)
    :Block(tx,ty)
{
    hp = INT_MAX;
    xspeed = 0;
    width = BLOCK_WIDTH;
    height = BLOCK_WIDTH;
    gravityinfluence = false;
    pixmap.load(SPRINGBLOCK_PIXMAP);
    rect.setWidth(pixmap.width());
    rect.setHeight(pixmap.height());
    rect.moveTo(tx,ty);
    typenum = 11;
}
