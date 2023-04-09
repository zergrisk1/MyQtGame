#include"creature.h"
#include<QPixmap>
#include<QPainter>
#include<QRect>
Creature::Creature(int thp,int speed,int tx,int ty,int twidth,int theight)
    :hp(thp),xspeed(speed),x(tx),y(ty),width(twidth),height(theight)
{
    pixmap.load(NULL);
    rect.setWidth(pixmap.width());
    rect.setHeight(pixmap.height());
    rect.moveTo(tx,ty);
}



Hero::Hero(int tx,int ty)
     :Creature(HERO_MAX_HP,0,tx,ty,HERO_WIDTH,HERO_HEIGHT),heroacc(HERO_ACC)
{
      pixmap.load(HERO_PIXMAP);
      rect.setWidth(48);
      rect.setHeight(48);
      rect.moveTo(tx,ty);
      damage = HERO_DAMAGE;
      typenum = 1;
}

void Hero::updateHeroCooltime()
{
    if(Hero::iscooltime) //进程攻击冷却机制
    {
        if(Hero::attackcooltime < HERO_ATTACK_COOLTIME)
        {
            Hero::attackcooltime ++;
        }
        else
        {
            Hero::attackcooltime = 0;
            Hero::iscooltime = false;
        }
    }
    if(isshootingcooltime)//远程攻击冷却机制
    {
        if(Hero::shootcooltime < HERO_SHOOTING_COOLTIME)
        {
            Hero::shootcooltime ++;
            xspeed = 0;
        }
        else
        {
            Hero::shootcooltime = 0;
            Hero::isshootingcooltime = false;
        }
    }

}


BasicMonster::BasicMonster(int tx,int ty)
    : Creature(100,2,tx,ty,BASICMONSTER_WIDTH,BASICMONSTER_HEIGHT)
{
    pixmap.load(BASICMONSTER_PIXMAP);
    rect.setWidth(48);
    rect.setHeight(48);
    rect.moveTo(tx,ty);
    sensor.setWidth(1.2*BASICMONSTER_WIDTH);
    sensor.setHeight(BASICMONSTER_HEIGHT);
    attackrange.setWidth(1.4*BASICMONSTER_WIDTH);
    attackrange.setHeight(BASICMONSTER_HEIGHT);
    typenum = 2;
    walkingpixmapsection = 5;
    maxwalkingcooltime = 50;
    attackpixmapsection = 3;
    maxattackcooltime = 24;
    deathpixmapsection = 3;
    maxdeathcooltime = 24;
}

void BasicMonster::updateStatement()
{
    if(deathframe == 0)
    {
        if(iscooltime)
        {
            if(!isfaceingright)
            {
                pixmap.load(BASICMONSTER_ATTACK_PIXMAP);
            }
            else
            {
                pixmap.load(BASICMONSTER_ATTACK_RIGHT_PIXMAP);
            }

            if(attackcooltime < maxattackcooltime)
            {
                attackcooltime ++;
            }
            else
            {
                attackcooltime = 0;
                iscooltime = false;
                if(!isfaceingright)
                {
                    xspeed -= 2;
                }
                else
                {
                    xspeed += 2;
                }
            }
        }
        else
        {
            if(xspeed >= 0)
            {
                isfaceingright = true;
                pixmap.load(BASICMONSTER_WALK_RIGHT_PIXMAP);
            }
            else
            {
                isfaceingright = false;
                pixmap.load(BASICMONSTER_WALK_LEFT_PIXMAP);
            }
            if(frame == maxwalkingcooltime)
            {
                frame = 0;
            }
            else
            {
                frame++;
            }
        }
    }
    else if(deathframe < maxdeathcooltime && deathframe > 0)
    {
        if(isfaceingright)
        {
            pixmap.load(BASICMONSTER_DEATH_RIGHT_PIXMAP);
            xspeed = 0;
        }
        else
        {
            pixmap.load(BASICMONSTER_DEATH_LEFT_PIXMAP);
            xspeed = 0;
        }
        deathframe ++;
    }
    else if(deathframe == maxdeathcooltime)
    {
        deathframe = DEAD_COMPLETE;
    }

}

StrongMonster::StrongMonster(int tx,int ty)
    : Creature(300,1,tx,ty,100,100)
{
    pixmap.load(STRONGMONSTER_PIXMAP);
    rect.setWidth(pixmap.width());
    rect.setHeight(pixmap.height());
    rect.moveTo(tx,ty);
    sensor.setWidth(1.2*STRONGMONSTER_WIDTH);
    sensor.setHeight(STRONGMONSTER_HEIGHT);
    attackrange.setWidth(1.4*STRONGMONSTER_WIDTH);
    attackrange.setHeight(STRONGMONSTER_HEIGHT);
    typenum = 7;
    walkingpixmapsection = 5;
    maxwalkingcooltime = 96;
    attackpixmapsection = 5;
    maxattackcooltime = 50;
    deathpixmapsection = 5;
    maxdeathcooltime = 50;
}

void StrongMonster::updateStatement()
{
    if(deathframe == 0)
    {
        if(iscooltime)
        {
            if(!isfaceingright)
            {
                pixmap.load(STRONGMONSTER_ATTACK_LEFT_PIXMAP);
            }
            else
            {
                pixmap.load(STRONGMONSTER_ATTACK_RIGHT_PIXMAP);
            }

            if(attackcooltime < maxattackcooltime)
            {
                attackcooltime ++;
            }
            else
            {
                attackcooltime = 0;
                iscooltime = false;
                if(!isfaceingright)
                {
                    xspeed -= 1;
                }
                else
                {
                    xspeed += 1;
                }
            }
        }
        else
        {
            if(xspeed >= 0)
            {
                isfaceingright = true;
                pixmap.load(STRONGMONSTER_WALK_RIGHT_PIXMAP);
            }
            else
            {
                isfaceingright = false;
                pixmap.load(STRONGMONSTER_WALK_LEFT_PIXMAP);
            }
            if(frame == maxwalkingcooltime)
            {
                frame = 0;
            }
            else
            {
                frame++;
            }
        }
    }
    else if(deathframe < maxdeathcooltime && deathframe > 0)
    {
        if(isfaceingright)
        {
            pixmap.load(STRONGMONSTER_DEATH_RIGHT_PIXMAP);
            xspeed = 0;
        }
        else
        {
            pixmap.load(STRONGMONSTER_DEATH_LEFT_PIXMAP);
            xspeed = 0;
        }
        deathframe ++;
    }
    else if(deathframe == maxdeathcooltime)
    {
        deathframe = DEAD_COMPLETE;
    }
}

Mage::Mage(int tx,int ty)
    : Creature(150,2,tx,ty,MAGE_WIDTH,MAGE_HEIGHT)
{
    pixmap.load(MAGE_PIXMAP);
    rect.setWidth(MAGE_WIDTH);
    rect.setHeight(pixmap.height());
    rect.moveTo(tx,ty);
    sensor.setWidth(1.2*MAGE_WIDTH);
    sensor.setHeight(MAGE_HEIGHT);
    attackrange.setWidth(15 * MAGE_WIDTH);
    attackrange.setHeight(2 * GAME_HEIGHT);
    typenum = 10;
    walkingpixmapsection = 3;
    maxwalkingcooltime = 45;
    attackpixmapsection = 7;
    maxattackcooltime = 49;
    deathpixmapsection = 5;
    maxdeathcooltime = 65;
}

void Mage::updateStatement()
{
    //alive
    if(deathframe == 0)
    {
        //attacking
        if(iscooltime)
        {
            if(!isfaceingright)
            {
                pixmap.load(MAGE_ATTACK_LEFT_PIXMAP);
            }
            else
            {
                pixmap.load(MAGE_ATTACK_RIGHT_PIXMAP);
            }

            if(attackcooltime < maxattackcooltime)
            {
                attackcooltime ++;
            }
            else
            {
                attackcooltime = 0;
                iscooltime = false;
                if(!isfaceingright)
                {
                    xspeed -= 2;
                }
                else
                {
                    xspeed += 2;
                }
            }
        }
        //walking
        else
        {
            if(xspeed >= 0)
            {
                isfaceingright = true;
                pixmap.load(MAGE_WALK_RIGHT_PIXMAP);
            }
            else
            {
                isfaceingright = false;
                pixmap.load(MAGE_WALK_LEFT_PIXMAP);
            }
            if(frame == maxwalkingcooltime)
            {
                frame = 0;
            }
            else
            {
                frame++;
            }
        }
    }
    //dying
    else if(deathframe < maxdeathcooltime && deathframe > 0)
    {
        if(isfaceingright)
        {
            pixmap.load(MAGE_DEATH_RIGHT_PIXMAP);
            xspeed = 0;
        }
        else
        {
            pixmap.load(MAGE_DEATH_LEFT_PIXMAP);
            xspeed = 0;
        }
        deathframe ++;
    }
    else if(deathframe == maxdeathcooltime)
    {
        deathframe = DEAD_COMPLETE;
    }
}

Goal::Goal(int tx,int ty)
    :Creature(100,0,tx,ty,GOAL_WIDTH,GOAL_HEIGHT)
{
    pixmap.load(GOAL_PIXMAP);
    rect.setWidth(pixmap.width());
    rect.setHeight(pixmap.height());
    rect.moveTo(tx,ty);
    typenum = 3;
}
