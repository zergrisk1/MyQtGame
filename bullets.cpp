#include "bullets.h"

HeroBullet::HeroBullet(int tx,int ty)
{
    x = tx;
    y = ty;
    pixmap.load(HERO_BULLET_PIXMAP);
    rect.setWidth(pixmap.width());
    rect.setHeight(pixmap.height());
    rect.moveTo(tx,ty);
    damage = HERO_DAMAGE;
    typenum = 100;
    yspeed = 0;
}

void HeroBullet::updateStatement()
{
    x += xspeed;
    y += yspeed;
}

//HeroBullet::HeroBullet(int tx,int ty)
//{
//    x = tx;
//    y = ty;
//    pixmap.load(HERO_BULLET_PIXMAP);
//    rect.setWidth(pixmap.width());
//    rect.setHeight(pixmap.height());
//    rect.moveTo(tx,ty);
//    damage = HERO_DAMAGE;
//    typenum = 100;
//    yspeed = 0;
//}

MageBullet::MageBullet(int tx,int ty)
{
    x = tx;
    y = ty;
    pixmap = QPixmap(MAGE_BULLET_PIXMAP).copy(0,0,12,12);
    rect.setWidth(MAGE_BULLET_WIDTH);
    rect.setHeight(MAGE_BULLET_WIDTH);
    rect.moveTo(tx,ty);
    damage = 100;
    typenum = 101;
    yspeed = 0;
    xspeed = 0;
    gravityinfluence = false;
    isblockpassable = true;
}

void MageBullet::updateStatement()
{
    x += xspeed;
    y += yspeed;
    pixtimer ++;
    if(pixtimer == 80)
    {
        pixtimer = 30;
    }
    pixmap = QPixmap(MAGE_BULLET_PIXMAP).copy((pixtimer/10)*12,0,12,12);
}

HpItem::HpItem(int tx,int ty)
{
    x = tx;
    y = ty;
    pixmap = QPixmap(ITEM_HP_PIXMAP).copy(0,0,12,12);
    rect.setWidth(32);
    rect.setHeight(48);
    rect.moveTo(tx,ty);
    damage = -200;
    typenum = 200;
    yspeed = 0;
    xspeed = 0;
    gravityinfluence = false;
    isblockpassable = true;
}

void HpItem::updateStatement()
{
    if(pixtimer == 0)
    {
        pixtimerisup = true;
    }
    if(pixtimer == 80)
    {
        pixtimerisup = false;
    }
    if(pixtimerisup)
    {
        pixtimer ++;
    }
    else
    {
        pixtimer --;
    }
    pixmap = QPixmap(ITEM_HP_PIXMAP).copy(0,0,48,48 + (pixtimer / 10) * 2);
    rect.setHeight(32 + (pixtimer / 10) * 2);
}

Stone::Stone(int tx,int ty)
{
    x = tx;
    y = ty;
    pixmap = QPixmap(ITEM_STONES_PIXMAP).copy(0,0,12,12);
    rect.setWidth(28);
    rect.setHeight(48);
    rect.moveTo(tx,ty);
    damage = -100;
    typenum = 201;
    yspeed = 0;
    xspeed = 0;
    gravityinfluence = false;
    isblockpassable = true;
}

void Stone::updateStatement()
{
    pixtimer ++;
    if(pixtimer == 30)
    {
        pixtimer = 0;
    }
    pixmap = QPixmap(ITEM_STONES_PIXMAP).copy((pixtimer/15)*28,0,28,48);
}

