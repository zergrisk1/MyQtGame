#include "mainhandler.h"
#include "ui_mainhandler.h"
#include "config.h"
#include "creature.h"
#include "pages.h"
#include "bullets.h"
#include<QDebug>
#include<QTime>
#include<QtMath>

int debug;
mainhandler::mainhandler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainhandler)
{
    this->setMouseTracking(true);


    ui->setupUi(this);
    pages = new Pages;
    ui->mainstackedWidget->setMouseTracking(true);
    initStackedWidget();
    connect(ui->startBtn,SIGNAL(clicked()),this,SLOT(showNormalModePage()));
    connect(ui->mainmenuBtn_1,SIGNAL(clicked()),this,SLOT(showMainMenuPage()));
    connect(ui->mainmenuBtn_2,SIGNAL(clicked()),this,SLOT(showMainMenuPage()));
    connect(ui->mapeditorBtn,SIGNAL(clicked()),this,SLOT(showSaveFileSelectPage()));
    connect(ui->helpBtn,SIGNAL(clicked()),this,SLOT(showHelpPage()));
    connect(ui->quitBtn,SIGNAL(clicked()),this,SLOT(close()));

    connect(ui->save_1Btn,SIGNAL(clicked()),this,SLOT(showMapEditorPage()));
    connect(ui->save_2Btn,SIGNAL(clicked()),this,SLOT(showMapEditorPage()));
    connect(ui->save_3Btn,SIGNAL(clicked()),this,SLOT(showMapEditorPage()));
    //存档读取signalmapper
    savefilesignalmapper = new QSignalMapper;

    connect(ui->save_1Btn,SIGNAL(clicked()),savefilesignalmapper,SLOT(map()));
    savefilesignalmapper->setMapping(ui->save_1Btn,1);

    connect(ui->save_2Btn,SIGNAL(clicked()),savefilesignalmapper,SLOT(map()));
    savefilesignalmapper->setMapping(ui->save_2Btn,2);

    connect(ui->save_3Btn,SIGNAL(clicked()),savefilesignalmapper,SLOT(map()));
    savefilesignalmapper->setMapping(ui->save_3Btn,3);

    connect(ui->startBtn,SIGNAL(clicked()),savefilesignalmapper,SLOT(map()));
    savefilesignalmapper->setMapping(ui->startBtn,4);

    connect(savefilesignalmapper,SIGNAL(mapped(int)),this,SLOT(readFile(int)));
    //



    connect(ui->backBtn,SIGNAL(clicked()),this,SLOT(showMainMenuPage()));

    connect(ui->menu_continueBtn,SIGNAL(clicked()),this,SLOT(hideMenu()));
    connect(ui->menu_continueBtn,SIGNAL(clicked()),this,SLOT(timerRestart()));

    connect(ui->menuBtn,SIGNAL(clicked()),this,SLOT(showMenu()));
    connect(ui->menu_mainmenuBtn,SIGNAL(clicked()),this,SLOT(showMainMenuPage()));
    connect(ui->menu_mainmenuBtn,SIGNAL(clicked()),this,SLOT(timerRestart()));



    signalmapper = new QSignalMapper;

    connect(ui->heroBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->heroBtn,1);

    connect(ui->basicmonsterBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->basicmonsterBtn,2);

    connect(ui->strongmonsterBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->strongmonsterBtn,9);

    connect(ui->MageBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->MageBtn,10);


    connect(ui->blockBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->blockBtn,3);


    connect(ui->goalBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->goalBtn,4);


    connect(ui->trashBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->trashBtn,5);


    connect(ui->purpleblockBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->purpleblockBtn,6);


    connect(ui->breakableblockBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->breakableblockBtn,7);

    connect(ui->longblockBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->longblockBtn,8);

    connect(ui->springblockBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->springblockBtn,11);

    connect(ui->hpitemBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->hpitemBtn,200);

    connect(ui->stoneBtn,SIGNAL(clicked()),signalmapper,SLOT(map()));
    signalmapper->setMapping(ui->stoneBtn,201);

    connect(signalmapper,SIGNAL(mapped(int)),this,SLOT(changeCursorIcon(int)));

    connect(this,SIGNAL(leftKeyPressed()),this,SLOT(mapLeftMove()));
    connect(this,SIGNAL(rightKeyPressed()),this,SLOT(mapRightMove()));



    keyUpdate();
    playGame();
    // QTimer *tic = new QTimer;
    // connect(tic,SIGNAL(timeout()),this,SLOT(currentpage()));
    // tic->start(2000);
    //QTimer *tic = new QTimer;
    //connect(tic,SIGNAL(timeout()),this,SLOT();
    //tic->start(20);

}

void mainhandler::updateHeroLabel()
{
    QFont font("Microsoft YaHei",10,87);
    ui->herostatLabel->setFont(font);
    ui->herostonelabel->setPixmap(QPixmap(ITEM_STONES_ICON_PIXMAP));
    ui->herostonenumLabel->setFont(font);
    ui->herostonenumLabel->setNum(hero->stonenum);
    ui->herostatLabel->setNum(hero->hp);
}

int mainhandler::random()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int test =qrand() % 10;
    return test;
}

void mainhandler::writeFile(int num)
{
    QString filename;
    QString strnum;
    filename = "./data/save_";
    strnum.setNum(num);
    filename.append(strnum);
    filename.append(".txt");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"Error!";
        return;
    }
    QString line;
    QString strx;
    QString stry;
    QString strtype;
    QTextStream in(&file);
    if(hero != nullptr)
    {
        strx.setNum(hero->x);
        stry.setNum(hero->y);
        strtype.setNum(hero->typenum);
        line = strx + "," + stry + "," + strtype;
        in<<line<<endl;
    }
    if(goal != nullptr)
    {
        strx.setNum(goal->x);
        stry.setNum(goal->y);
        strtype.setNum(goal->typenum);
        line = strx + "," + stry + "," + strtype;
        in<<line<<endl;
    }
    for(int i = 0;i < creature.size();i++)
    {
        strx.setNum(creature[i]->x);
        stry.setNum(creature[i]->y);
        strtype.setNum(creature[i]->typenum);
        line = strx + "," + stry + "," + strtype;
        in<<line<<endl;
    }
    for(int i = 0;i < blocks.size();i++)
    {
        strx.setNum(blocks[i]->x);
        stry.setNum(blocks[i]->y);
        strtype.setNum(blocks[i]->typenum);
        line = strx + "," + stry + "," + strtype;
        in<<line<<endl;
    }
    for(int i = 0;i < enemybullets.size();i++)
    {
        strx.setNum(enemybullets[i]->x);
        stry.setNum(enemybullets[i]->y);
        strtype.setNum(enemybullets[i]->typenum);
        line = strx + "," + stry + "," + strtype;
        in<<line<<endl;
    }
    file.close();
}


void mainhandler::readFile(int num)
{
    seletedsavefilenum = num;
    QString filename;
    QString strnum;
    filename = "./data/save_";
    strnum.setNum(num);
    filename.append(strnum);
    filename.append(".txt");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can't open this file!";
        return;
    }
    else
    {
        qDebug()<<"success";
        QTextStream in(&file);
        QString line = in.readLine();
        QStringList x_y_type;
        while (!line.isNull())
        {
            Debug();
            x_y_type  =line.split(",");
            Debug();
            int tx = x_y_type[0].toInt();
            Debug();
            int ty = x_y_type[1].toInt();
            Debug();
            int ttype = x_y_type[2].toInt();
            Debug();
            switch(ttype)
            {
            case 1:
            {
                hero = new Hero(tx,ty);
                phero = new Hero(tx,ty);
            }
                break;
            case 2:
            {
                Creature *tcreature = new BasicMonster(tx,ty);
                creature.push_back(tcreature);
            }
                break;
            case 3:
            {
                goal = new Goal(tx,ty);
            }
                break;
            case 4:
            {
                Block *tblock = new Block(tx,ty);
                blocks.push_back(tblock);
            }
                break;
            case 5:
            {
                Block *tblock = new PurpleBlock(tx,ty);
                blocks.push_back(tblock);
            }
                break;
            case 6:
            {
                Block *tblock = new BreakableBlock(tx,ty);
                blocks.push_back(tblock);
            }
                break;
            case 7:
            {
                Creature *tcreature = new StrongMonster(tx,ty);
                creature.push_back(tcreature);
            }
                break;
            case 8:
            {
                Block *tblock = new LongBlock(tx,ty);
                blocks.push_back(tblock);
            }
                break;
            case 10:
            {
                Creature *tcreature = new Mage(tx,ty);
                creature.push_back(tcreature);
            }
                break;
            case 11:
            {
                Block *tcreature = new SpringBlock(tx,ty);
                blocks.push_back(tcreature);
            }
                break;
            case 200:
            {
                Bullet *tbullet = new HpItem(tx,ty);
                enemybullets.push_back(tbullet);
            }
                break;
            case 201:
            {
                Bullet *tbullet = new Stone(tx,ty);
                enemybullets.push_back(tbullet);
            }
                break;
            default:
                break;

            }
            line = in.readLine();
        }
        file.close();
    }
}
void mainhandler::timerRestart()
{
    timer->start();
    keytimer->start();
}

void mainhandler::showMenu()
{
    ui->menu_continueBtn->show();
    ui->menu_helpBtn->show();
    ui->menu_mainmenuBtn->show();
    keytimer->stop();
    timer->stop();
}

void mainhandler::hideMenu()
{
    ui->menu_continueBtn->hide();
    ui->menu_helpBtn->hide();
    ui->menu_mainmenuBtn->hide();
}

void mainhandler::currentpage()
{
    qDebug()<<"current page is:"<<pages->currentpage;
}

void mainhandler::Debug()
{
    debug++;
    qDebug()<<debug;
}


void mainhandler::updateEtc()
{
    if(hero != nullptr)
    {
        updateHeroLabel();
        hero->updateHeroCooltime();
        if(hero->shootcooltime == 3 * HERO_SHOOTING_COOLTIME / 4)
        {
            Bullet *bullet = new HeroBullet(hero->x,hero->y + 5 );
            if(hero->isfaceingright)
            {
                bullet->xspeed = 2 * HERO_MAXSPEED;
            }
            else
            {
                bullet->xspeed = -2 * HERO_MAXSPEED;
            }
            allybullets.push_back(bullet);
        }
    }
    for(int i = 0;i < blocks.size();i++)
    {
        blocks[i]->updateStatement();
    }
    for(int i = 0;i < creature.size();i++)
    {
        creature[i]->updateStatement();
        if(creature[i]->typenum == 10
                && creature[i]->attackcooltime == 7 * creature[i]->maxattackcooltime / 8)
        {
            Bullet *bullet = new MageBullet(creature[i]->x + ui->mainstackedWidget->x(),
                                            creature[i]->y + ui->mainstackedWidget->y() + 20);
            double deltax = hero->x - (creature[i]->x + ui->mainstackedWidget->x());
            double deltay = hero->y - creature[i]->y - ui->mainstackedWidget->y();
            qDebug()<<"delta X ="<<deltax;
            qDebug()<<"delta Y ="<<deltay;
            //if(hero->rect.center().y() < creature[i]->rect.center().y())
                bullet->yspeed = 5*(deltay / sqrt((deltax * deltax) + (deltay * deltay)));
            if(hero->rect.center().x() < creature[i]->rect.center().x() + ui->mainstackedWidget->x())
            {
                bullet->xspeed = -sqrt(25 - (bullet->yspeed * bullet->yspeed));
                qDebug()<<"xspeed  ="<<bullet->xspeed;
                qDebug()<<"yspeed  ="<<bullet->yspeed;
            }
            else
            {
                bullet->xspeed = sqrt(25 - (bullet->yspeed * bullet->yspeed));
                qDebug()<<"xspeed  ="<<bullet->xspeed;
                qDebug()<<"yspeed  ="<<bullet->yspeed;
            }

           // bullet->xspeed = deltax / 15;
           // if(deltax>0)
           // {
           //     deltax = -deltax;
           // }
           // bullet->yspeed = deltax / 20;
            enemybullets.push_back(bullet);
        }
    }
    for(int i = 0;i < allybullets.size();i++)
    {
        allybullets[i]->updateStatement();
    }
    for(int i = 0;i < enemybullets.size();i++)
    {
        enemybullets[i]->updateStatement();
    }
}

mainhandler::~mainhandler()
{
    delete ui;
    delete pages;
    delete hero;
    delete phero;
}

int mainhandler::inttimer()
{
    if(t < 1000/GAME_RATE)
    {
        t++;
    }
    else
    {
        t = 0;
    }
    return t;
}

void mainhandler::playGame()
{
    timer->start();
    connect(timer,&QTimer::timeout,[=](){
        updatePosition();//负责刷新各种对象的位置的函数
        updateDeathJudgement();//负责刷新各种对象死亡判定的函数
        updateMonstersAI();//负责刷新怪AI的函数
        inttimer();//没用
        updateEtc();//负责刷新各种对象各种因素的函数
        collisionDetection();//负责刷新对象碰撞检测与攻击判定等的函数
        update();//负责刷新对象图片的函数
    });
}

void mainhandler::gravityOn()
{
    if(pages->currentpage == NORMAL_LEVEL_1
            ||pages->currentpage == NORMAL_LEVEL_2
            ||pages->currentpage == NORMAL_LEVEL_3
            ||pages->currentpage == MAP_EDITOR)
    {
        for(int i = 0;i < creature.size();i++)
        {
            if(creature[i]->gravityinfluence)
            {
                creature[i]->yspeed -= GRAVITY;
                creature[i]->y -= creature[i]->yspeed;
            }
        }
        if(hero != nullptr)
        {
            if(hero->gravityinfluence)
            {
                hero->yspeed -= GRAVITY;
                hero->y -= hero->yspeed;
            }
        }
        for(int i = 0;i < allybullets.size();i++)
        {
            if(allybullets[i]->gravityinfluence)
            {
                allybullets[i]->yspeed += GRAVITY;
            }
        }
        for(int i = 0;i < enemybullets.size();i++)
        {
            if(enemybullets[i]->gravityinfluence)
            {
                enemybullets[i]->yspeed += GRAVITY;
            }
        }
    }
}

void mainhandler::updatePosition()
{
    mapMove();
    updateRectPosition();
    gravityOn();

}

void mainhandler::mapLeftMove()
{
    if(ui->mainstackedWidget->currentWidget()->x()<0)
    {
        mapmovedtotal += 20;
        ui->mainstackedWidget->currentWidget()->move(mapmovedtotal,0);
        ui->heroBtn->move(-mapmovedtotal,0);
        ui->hpitemBtn->move(-mapmovedtotal + 93,31);
        ui->stoneBtn->move(-mapmovedtotal + 93,62);
        ui->purpleblockBtn->move(-mapmovedtotal,31);
        ui->blockBtn->move(-mapmovedtotal + 31,31);
        ui->springblockBtn->move(-mapmovedtotal + 124,0);
        ui->breakableblockBtn->move(-mapmovedtotal + 62,31);
        ui->longblockBtn->move(-mapmovedtotal + 31,93);
        ui->goalBtn->move(-mapmovedtotal,62);
        ui->trashBtn->move(-mapmovedtotal + 480,0);
        ui->basicmonsterBtn->move(-mapmovedtotal + 31,0);
        ui->strongmonsterBtn->move(-mapmovedtotal + 62,0);
        ui->MageBtn->move(-mapmovedtotal + 93,0);
        ui->mapeditorplatBtn->move(-mapmovedtotal + 870,40);
        ui->saveBtn->move(-mapmovedtotal + 870,70);
    }
}

void mainhandler::mapRightMove()
{
    if(ui->mainstackedWidget->currentWidget()->x()>-(ui->mainstackedWidget->currentWidget()->width()-GAME_WIDTH))
    {
        mapmovedtotal -= 20;
        ui->mainstackedWidget->currentWidget()->move(mapmovedtotal,0);
        ui->heroBtn->move(-mapmovedtotal,0);
        ui->hpitemBtn->move(-mapmovedtotal + 93,31);
        ui->stoneBtn->move(-mapmovedtotal + 93,62);
        ui->purpleblockBtn->move(-mapmovedtotal,31);
        ui->springblockBtn->move(-mapmovedtotal + 124,0);
        ui->blockBtn->move(-mapmovedtotal + 31,31);
        ui->breakableblockBtn->move(-mapmovedtotal + 62,31);
        ui->longblockBtn->move(-mapmovedtotal + 31,93);
        ui->goalBtn->move(-mapmovedtotal,62);
        ui->trashBtn->move(-mapmovedtotal + 480,0);
        ui->basicmonsterBtn->move(-mapmovedtotal + 31,0);
        ui->strongmonsterBtn->move(-mapmovedtotal + 62,0);
        ui->MageBtn->move(-mapmovedtotal + 93,0);
        ui->mapeditorplatBtn->move(-mapmovedtotal + 870,40);
        ui->saveBtn->move(-mapmovedtotal + 870,70);
    }
}

void mainhandler::InitStack()
{
    hideMenu();
    creature.clear();
    blocks.clear();
    allybullets.clear();
    enemybullets.clear();
    hero = nullptr;
    //delete phero;
    phero = nullptr;
    goal = nullptr;
    mapmovedtotal = 0;
    // tempblocks.swap(blocks);
    ui->mainstackedWidget->currentWidget()->move(0,0);
    setCursor(Qt::ArrowCursor);
}

void mainhandler::showMainMenuPage()
{
    InitStack();
    ui->mainstackedWidget->setCurrentIndex(MAINMENU);
    pages->currentpage = MAINMENU;
    ui->menuBtn->hide();
    ui->helpBtn->hide();
    ui->herostatLabel->hide();
    ui->herostonelabel->hide();
    ui->herostonenumLabel->hide();
    ui->backtomapdeitorBtn->hide();
    seletedsavefilenum = 0;
}

void mainhandler::showSaveFileSelectPage()
{
    InitStack();
    ui->mainstackedWidget->setCurrentIndex(SAVEFILE_SELECT);
    pages->currentpage = SAVEFILE_SELECT;
}

void mainhandler::showNextStagePage()
{
    InitStack();
    ui->mainstackedWidget->setCurrentIndex(NEXTSTAGE);
    pages->currentpage = NEXTSTAGE;
    ui->herostatLabel->hide();
    ui->herostonelabel->hide();
    ui->herostonenumLabel->hide();
}

void mainhandler::showNormalModePage()
{

    InitStack();
    ui->mainstackedWidget->setCurrentIndex(NORMAL_LEVEL_1);
    pages->currentpage = NORMAL_LEVEL_1;
    ui->menuBtn->show();
    ui->herostatLabel->show();
    ui->herostonelabel->show();
    ui->herostonenumLabel->show();
    if(seletedsavefilenum != 0)
    {
        ui->backtomapdeitorBtn->show();
    }
    else
    {
        ui->backtomapdeitorBtn->hide();
    }
}

void mainhandler::showMapEditorPage()
{
    InitStack();
    ui->mainstackedWidget->setCurrentIndex(MAP_EDITOR);
    pages->currentpage = MAP_EDITOR;
    ui->menuBtn->show();
    ui->herostatLabel->hide();
    ui->herostonelabel->hide();
    ui->herostonenumLabel->hide();
}

void mainhandler::showHelpPage()
{
    ui->mainstackedWidget->setCurrentIndex(HELP);
    pages->currentpage = HELP;
    ui->herostatLabel->hide();
    ui->herostonelabel->hide();
    ui->herostonenumLabel->hide();

}

void mainhandler::showGameOverPage()
{
    ui->mainstackedWidget->setCurrentIndex(GAMEOVER);
    pages->currentpage = GAMEOVER;
    ui->herostatLabel->hide();
    ui->herostonelabel->hide();
    ui->herostonenumLabel->hide();
    InitStack();
}



void mainhandler::initStackedWidget()
{
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowIcon(QIcon(HERO_PIXMAP));
    drawButtonsIcon();
    timer = new QTimer;
    keytimer=new QTimer(this);
    timer->setInterval(GAME_RATE);
    showMainMenuPage();
}

void mainhandler::updateRectPosition()
{
    if(pages->currentpage == NORMAL_LEVEL_1
            ||pages->currentpage == MAP_EDITOR_GAME
            ||pages->currentpage == MAP_EDITOR)
    {
        if(hero != nullptr &&phero != nullptr && pages->currentpage != MAP_EDITOR)
        {
            hero->rect.moveTo(hero->x ,hero->y );
            phero->rect.moveTo(phero->x,phero->y);
        }
        else if(hero != nullptr && phero != nullptr && pages->currentpage == MAP_EDITOR)
        {
            hero->rect.moveTo(ui->mainstackedWidget->currentWidget()->x() + hero->x ,
                              hero->y + ui->mainstackedWidget->currentWidget()->y());
            phero->rect.moveTo(ui->mainstackedWidget->currentWidget()->x() + phero->x,
                               phero->y + ui->mainstackedWidget->currentWidget()->y());
        }
        if(goal != nullptr)
        {
            goal->rect.moveTo(goal->x+ ui->mainstackedWidget->currentWidget()->x(),
                              goal->y + ui->mainstackedWidget->currentWidget()->y());
        }
        for(int i = 0;i < blocks.size();i++)
        {
            blocks[i]->rect.moveTo(blocks[i]->x + ui->mainstackedWidget->currentWidget()->x(),
                                   blocks[i]->y + ui->mainstackedWidget->currentWidget()->y());
        }
        for(int i = 0;i < allybullets.size();i++)
        {
            allybullets[i]->rect.moveTo(allybullets[i]->x,
                                   allybullets[i]->y);
        }
        for(int i = 0;i < enemybullets.size();i++)
        {
            enemybullets[i]->rect.moveTo(enemybullets[i]->x + ui->mainstackedWidget->currentWidget()->x(),
                                   enemybullets[i]->y);
        }
        //creature rect
        for(int i = 0;i < creature.size();i++)
        {

            creature[i]->rect.moveTo(creature[i]->x + ui->mainstackedWidget->currentWidget()->x(),
                                     creature[i]->y + ui->mainstackedWidget->currentWidget()->y());
            creature[i]->sensor.moveTo(creature[i]->rect.x()-0.1 * creature[i]->width,
                                       creature[i]->y);
            // qDebug()<<"rect x:"<<creature[i]->rect.x();
            //qDebug()<<"sensor x:"<<creature[i]->sensor.x();
            if(creature[i]->typenum == 2
                    || creature[i]->typenum == 7)
            {
                creature[i]->attackrange.moveTo(creature[i]->rect.x() - 0.2 * creature[i]->width,
                                                creature[i]->y);
            }
            else if(creature[i]->typenum == 10)
            {
                creature[i]->attackrange.moveTo(creature[i]->rect.x() - 7 * creature[i]->width,
                                                creature[i]->y - GAME_HEIGHT);
            }
        }
    }
    else if(pages->currentpage == NORMAL_LEVEL_2)
    {

    }
    else if(pages->currentpage == NORMAL_LEVEL_3)
    {

    }
}

void mainhandler::drawButtonsIcon()
{
    QPixmap icon(tr(HERO_JUMP_PIXMAP));
    ui->heroBtn->setIcon(icon);
    ui->heroBtn->setIconSize(QSize(31,31));

    icon.load(ITEM_HP_PIXMAP);
    ui->hpitemBtn->setIcon(icon);
    ui->hpitemBtn->setIconSize(QSize(31,31));

    icon.load(ITEM_STONES_ICON_PIXMAP);
    ui->stoneBtn->setIcon(icon);
    ui->stoneBtn->setIconSize(QSize(31,31));

    icon.load(BLOCK_PIXMAP);
    ui->blockBtn->setIcon(icon);
    ui->blockBtn->setIconSize(QSize(31,31));

    icon.load(BASICMONSTER_ICON_PIXMAP);
    ui->basicmonsterBtn->setIcon(icon);
    ui->basicmonsterBtn->setIconSize(QSize(40,40));

    icon.load(MAGE_PIXMAP);
    ui->MageBtn->setIcon(icon);
    ui->MageBtn->setIconSize(QSize(40,40));

    icon.load(STRONGMONSTER_PIXMAP);
    ui->strongmonsterBtn->setIcon(icon);
    ui->strongmonsterBtn->setIconSize(QSize(40,40));

    icon.load(GOAL_PIXMAP);
    ui->goalBtn->setIcon(icon);
    ui->goalBtn->setIconSize(QSize(40,40));

    icon.load(TRASH_PIXMAP);
    ui->trashBtn->setIcon(icon);
    ui->trashBtn->setIconSize(QSize(50,62));
    ui->trashBtn->setFlat(true);

    icon.load(PURPLEBLOCK_PIXMAP);
    ui->purpleblockBtn->setIcon(icon);
    ui->purpleblockBtn->setIconSize(QSize(40,40));

    icon.load(SPRINGBLOCK_PIXMAP);
    ui->springblockBtn->setIcon(icon);
    ui->springblockBtn->setIconSize(QSize(40,40));

    icon.load(BREAKABLEBLOCK1_PIXMAP);
    ui->breakableblockBtn->setIcon(icon);
    ui->breakableblockBtn->setIconSize(QSize(40,40));

    icon.load(LONG_BLOCK_PIXMAP);
    ui->longblockBtn->setIcon(icon);
    ui->longblockBtn->setIconSize(QSize(80,40));

    icon.load(PURPLE_BUTTON_CONTINUE_PIXMAP);
    ui->menu_continueBtn->setIcon(icon);
    ui->menu_continueBtn->setIconSize(QSize(261,100));
    ui->menu_continueBtn->setFlat(true);

    icon.load(PURPLE_BUTTON_SAVE1_PIXMAP);
    ui->save_1Btn->setIcon(icon);
    ui->save_1Btn->setIconSize(QSize(261,100));
    ui->save_1Btn->setFlat(true);

    icon.load(PURPLE_BUTTON_SAVE2_PIXMAP);
    ui->save_2Btn->setIcon(icon);
    ui->save_2Btn->setIconSize(QSize(261,100));
    ui->save_2Btn->setFlat(true);

    icon.load(PURPLE_BUTTON_SAVE3_PIXMAP);
    ui->save_3Btn->setIcon(icon);
    ui->save_3Btn->setIconSize(QSize(261,100));
    ui->save_3Btn->setFlat(true);

    icon.load(PURPLE_BUTTON_START_PIXMAP);
    ui->startBtn->setIcon(icon);
    ui->startBtn->setIconSize(QSize(261,100));
    ui->startBtn->setFlat(true);

    icon.load(PURPLE_BUTTON_MAPEDITOR_MAPEDITOR_PIXMAP);
    ui->mapeditorBtn->setIcon(icon);
    ui->mapeditorBtn->setIconSize(QSize(261,100));
    ui->mapeditorBtn->setFlat(true);

    icon.load(PURPLE_BUTTON_HELP_PIXMAP);
    ui->helpBtn->setIcon(icon);
    ui->helpBtn->setIconSize(QSize(261,100));
    ui->menu_helpBtn->setIcon(icon);
    ui->menu_helpBtn->setIconSize(QSize(261,100));
    ui->helpBtn->setFlat(true);
    ui->menu_helpBtn->setFlat(true);

    icon.load(PURPLE_BUTTON_QUIT_PIXMAP);
    ui->quitBtn->setIcon(icon);
    ui->quitBtn->setIconSize(QSize(261,100));
    ui->quitBtn->setFlat(true);

    icon.load(PURPLE_BUTTON_MAINMENU_PIXMAP);
    ui->menu_mainmenuBtn->setIcon(icon);
    ui->menu_mainmenuBtn->setIconSize(QSize(261,100));
    ui->menu_mainmenuBtn->setFlat(true);
    ui->backBtn->setIcon(icon);
    ui->backBtn->setIconSize(QSize(261,100));
    ui->backBtn->setFlat(true);

    ui->saveBtn->setCursor(Qt::PointingHandCursor);
    ui->mapeditorplatBtn->setCursor(Qt::PointingHandCursor);
    ui->menuBtn->setCursor(Qt::PointingHandCursor);
}

void mainhandler::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(pages->currentpage == MAINMENU ||pages->currentpage == SAVEFILE_SELECT)
    {
        pagesPixMap.load(MAINMENU_PIXMAP);
        painter.drawPixmap(0,0,GAME_WIDTH,GAME_HEIGHT,pagesPixMap);
    }
    if(pages->currentpage == NORMAL_LEVEL_1
            ||pages->currentpage == MAP_EDITOR
            ||pages->currentpage == MAP_EDITOR_GAME)
    {
        pagesPixMap.load(STAGE_1_PIXMAP);
        temp.load(":/resource/temphero.png");
         painter.drawPixmap(ui->mainstackedWidget->currentWidget()->x(),
                            ui->mainstackedWidget->currentWidget()->y(),
                            3000,GAME_HEIGHT,pagesPixMap);
        //All about Hero's animations
        if(hero != nullptr && pages->currentpage != MAP_EDITOR)
        {
            //painter.drawPixmap(hero->x ,hero->y ,hero->pixmap);
            //Jump and Walking Motion
            if(!hero->iscooltime && !hero->isshootingcooltime)
            {
                if(hero->gravityinfluence)
                {
                    if(hero->isfaceingright)
                    {
                        painter.drawPixmap(hero->x,hero->y,QPixmap(tr(HERO_JUMP_PIXMAP)));
                    }
                    else
                    {
                        painter.drawPixmap(hero->x,hero->y,QPixmap(tr(HERO_JUMP_LEFT_PIXMAP)));
                    }
                }
                else if(hero->xspeed == 0)
                {
                    if(hero->isfaceingright)
                    {
                        painter.drawPixmap(hero->x,hero->y,
                                           HERO_WIDTH,HERO_HEIGHT,
                                           hero->pixmap,
                                           HERO_WIDTH*2,0,
                                           HERO_WIDTH,HERO_HEIGHT);
                    }
                    else
                    {
                        painter.drawPixmap(hero->x,hero->y,
                                           HERO_WIDTH,HERO_HEIGHT,
                                           QPixmap(tr(HERO_LEFT_PIXMAP)),
                                           HERO_WIDTH*3,0,
                                           HERO_WIDTH,HERO_HEIGHT);
                    }


                }
                else
                {
                    if(hero->isfaceingright)
                    {
                        painter.drawPixmap(hero->x,hero->y,
                                           HERO_WIDTH,HERO_HEIGHT,
                                           hero->pixmap,
                                           HERO_WIDTH*(hero->frame/5),0,
                                           HERO_WIDTH,HERO_HEIGHT);
                    }
                    else
                    {
                        painter.drawPixmap(hero->x,hero->y,
                                           HERO_WIDTH,HERO_HEIGHT,
                                           QPixmap(tr(HERO_LEFT_PIXMAP)),
                                           HERO_WIDTH*(hero->frame/5),0,
                                           HERO_WIDTH,HERO_HEIGHT);
                    }
                }
            }
            //Attack Motion
            else if(hero->iscooltime)
            {
                if(hero->isfaceingright)
                {
                    painter.drawPixmap(hero->x,hero->y,
                                       HERO_WIDTH,HERO_HEIGHT,
                                       QPixmap(tr(HERO_ATTACK_PIXMAP)),
                                       HERO_WIDTH*(hero->attackcooltime/5),0,
                                       HERO_WIDTH,HERO_HEIGHT);
                }
                else
                {
                    painter.drawPixmap(hero->x,hero->y,
                                       HERO_WIDTH,HERO_HEIGHT,
                                       QPixmap(tr(HERO_ATTACK_LEFT_PIXMAP)),
                                       HERO_WIDTH*(5 - hero->attackcooltime/5),0,
                                       HERO_WIDTH,HERO_HEIGHT);
                }
            }
            else if(hero->isshootingcooltime)
            {
                if(hero->isfaceingright)
                {
                    painter.drawPixmap(hero->x,hero->y,
                                       HERO_WIDTH,HERO_HEIGHT,
                                       QPixmap(tr(HERO_THROW_RIGHT_PIXMAP)),
                                       HERO_WIDTH*(hero->shootcooltime/8),0,
                                       HERO_WIDTH,HERO_HEIGHT);
                }
                else
                {
                    painter.drawPixmap(hero->x,hero->y,
                                       HERO_WIDTH,HERO_HEIGHT,
                                       QPixmap(tr(HERO_THROW_LEFT_PIXMAP)),
                                       HERO_WIDTH*(3 - hero->shootcooltime/8),0,
                                       HERO_WIDTH,HERO_HEIGHT);
                }
            }
            if(hero->frame == HERO_FRAME)
                hero->frame = 0;
            else
            {
                hero->frame++;
            }
        }
        else if(hero != nullptr && pages->currentpage == MAP_EDITOR)
        {
            painter.drawPixmap(hero->x +ui->mainstackedWidget->currentWidget()->x(),
                               hero->y + ui->mainstackedWidget->currentWidget()->y(),
                               QPixmap(tr(HERO_JUMP_PIXMAP)));
        }
        //hero ends
        if(goal != nullptr)
        {
            painter.drawPixmap(goal->x +ui->mainstackedWidget->currentWidget()->x(),
                               goal->y + ui->mainstackedWidget->currentWidget()->y(),
                               goal->pixmap);
        }
        if(phero != nullptr)
        {
            //painter.drawPixmap(phero->x, phero->y ,temp);
        }
        //all about bullets
            //ally bullets
        for(int i = 0; i < allybullets.size();i++)
        {
            painter.drawPixmap(allybullets[i]->x,
                               allybullets[i]->y + ui->mainstackedWidget->currentWidget()->y(),
                               allybullets[i]->pixmap);
        }
            //enemy bullets
        for(int i = 0; i < enemybullets.size();i++)
        {
            painter.drawPixmap(enemybullets[i]->x + ui->mainstackedWidget->currentWidget()->x(),
                               enemybullets[i]->y + ui->mainstackedWidget->currentWidget()->y(),
                               enemybullets[i]->pixmap);
        }

        //all about creatures
        for(int i = 0;i < creature.size();i++)
        {
            if(creature[i]->deathframe == 0)
            {
                if(creature[i]->iscooltime)
                {
                    if(!creature[i]->isfaceingright)
                    {
                        painter.drawPixmap(creature[i]->x + ui->mainstackedWidget->currentWidget()->x(),
                                           creature[i]->y + ui->mainstackedWidget->currentWidget()->y(),
                                           creature[i]->width,creature[i]->height,
                                           creature[i]->pixmap,
                                           creature[i]->width*(creature[i]->attackcooltime
                                                               / (creature[i]->maxattackcooltime
                                                                  / creature[i]->attackpixmapsection)),0,
                                           creature[i]->width,creature[i]->height);
                    }
                    else
                    {
                        painter.drawPixmap(creature[i]->x + ui->mainstackedWidget->currentWidget()->x(),
                                           creature[i]->y + ui->mainstackedWidget->currentWidget()->y(),
                                           creature[i]->width,creature[i]->height,
                                           creature[i]->pixmap,
                                           creature[i]->width*(creature[i]->attackpixmapsection
                                                               - creature[i]->attackcooltime
                                                               / (creature[i]->maxattackcooltime
                                                                  / creature[i]->attackpixmapsection)),0,
                                           creature[i]->width,creature[i]->height);
                    }
                }
                else if(!creature[i]->iscooltime)
                {
                    if(!creature[i]->isfaceingright)
                    {
                        painter.drawPixmap(creature[i]->x + ui->mainstackedWidget->currentWidget()->x(),
                                           creature[i]->y + ui->mainstackedWidget->currentWidget()->y(),
                                           creature[i]->width,creature[i]->height,
                                           creature[i]->pixmap,
                                           creature[i]->width*(creature[i]->frame
                                                               /(creature[i]->maxwalkingcooltime
                                                                 /creature[i]->walkingpixmapsection)),0,
                                           creature[i]->width,creature[i]->width);
                    }

                    else
                    {
                        painter.drawPixmap(creature[i]->x + ui->mainstackedWidget->currentWidget()->x(),
                                           creature[i]->y + ui->mainstackedWidget->currentWidget()->y(),
                                           creature[i]->width,creature[i]->height,
                                           creature[i]->pixmap,
                                           creature[i]->width*(creature[i]->walkingpixmapsection - creature[i]->frame
                                                               /(creature[i]->maxwalkingcooltime
                                                                 /creature[i]->walkingpixmapsection)),0,
                                           creature[i]->width,creature[i]->height);
                    }
                }
            }
            else if(creature[i]->deathframe != DEAD_COMPLETE)
            {
                if(!creature[i]->isfaceingright)
                {
                    painter.drawPixmap(creature[i]->x + ui->mainstackedWidget->currentWidget()->x(),
                                       creature[i]->y + ui->mainstackedWidget->currentWidget()->y(),
                                       creature[i]->width,creature[i]->height,
                                       creature[i]->pixmap,
                                       creature[i]->width*(creature[i]->deathframe
                                                           /(creature[i]->maxdeathcooltime
                                                             /creature[i]->deathpixmapsection)),0,
                                       creature[i]->width,creature[i]->width);
                }

                else
                {
                    painter.drawPixmap(creature[i]->x + ui->mainstackedWidget->currentWidget()->x(),
                                       creature[i]->y + ui->mainstackedWidget->currentWidget()->y(),
                                       creature[i]->width,creature[i]->height,
                                       creature[i]->pixmap,
                                       creature[i]->width*(creature[i]->deathpixmapsection - creature[i]->deathframe
                                                           /(creature[i]->maxdeathcooltime
                                                             /creature[i]->deathpixmapsection)),0,
                                       creature[i]->width,creature[i]->height);
                }
            }

        }
        //all about blocks
        for(int i = 0;i < blocks.size();i++)
        {

            painter.drawPixmap( blocks[i]->x +ui->mainstackedWidget->currentWidget()->x(),
                                blocks[i]->y + ui->mainstackedWidget->currentWidget()->y(),
                                blocks[i]->pixmap);
        }
    }

}

void mainhandler::keyUpdate()
{
    connect(keytimer,&QTimer::timeout,[this]
    {

        if(pressedkeys.isEmpty())
        {
            keytimer->stop();
            return;
        }

        for(int key:pressedkeys)
        {
            switch (key) {
            case Qt::Key_X:
            {
                if(hero != nullptr && pages->currentpage != MAP_EDITOR)
                {
                    if(hero->stonenum > 0 && !hero->iscooltime && !hero->isshootingcooltime)
                    {
                        hero->isshootingcooltime = true;
                        hero->stonenum --;
                    }
                }
            }
                break;
            case Qt::Key_Z:
            {
                if(hero != nullptr && pages->currentpage != MAP_EDITOR)
                {
                    if(!hero->iscooltime && !hero->isshootingcooltime)
                    {
                        hero->iscooltime = true;
                        qDebug()<<"attacked";
                    }
                }
            }
                break;
            case Qt::Key_Space:
            {
                if(hero != nullptr && pages->currentpage != MAP_EDITOR)
                {
                    if(!hero->gravityinfluence)
                    {
                        hero->yspeed += HERO_JUMP;
                        hero->y -= hero->yspeed;
                        hero->gravityinfluence = true;
                    }
                }
            }
                break;
            case Qt::Key_Right:
            {
                if(pages->currentpage == MAP_EDITOR)
                {
                    emit rightKeyPressed();
                }

                else if(hero != nullptr && timer->isActive())
                {
                    hero->isfaceingright = true;
                    if(hero->x + hero->width <= GAME_WIDTH - hero->xspeed )
                    {
                        if( hero->xspeed <= HERO_MAXSPEED)
                        {
                            hero->xspeed += hero->heroacc;
                            hero->x += hero->xspeed;
                        }
                        else
                        {
                            hero->xspeed = HERO_MAXSPEED;
                            hero->x += hero->xspeed;
                        }
                    }
                    else
                    {

                        hero->x = GAME_WIDTH - hero->width;
                    }
                }
            }
                break;
            case Qt::Key_Left:
            {
                if(pages->currentpage == MAP_EDITOR && timer->isActive())
                {
                    emit leftKeyPressed();
                }
                else if(hero != nullptr && timer->isActive())
                {
                    hero->isfaceingright = false;
                    if(hero->x >= 0 - hero->xspeed )
                    {
                        if( hero->xspeed <= HERO_MAXSPEED)
                        {
                            hero->xspeed += hero->heroacc;
                            hero->x -= hero->xspeed;
                        }
                        else
                        {
                            hero->xspeed = HERO_MAXSPEED;
                            hero->x -= hero->xspeed;
                        }
                    }
                    else
                    {
                        hero->x = 0;
                    }
                }
            }
                break;
            }

        }

    });
}

void mainhandler::changeCursorIcon(int num)//改变鼠标的形状
{
    if(num == 1)
    {
        QCursor *mycorsor = new QCursor(QPixmap(HERO_JUMP_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "hero";
    }
    else if(num == 2)
    {
        QCursor *mycorsor = new QCursor(QPixmap(BASICMONSTER_ICON_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "basicmonster";
    }
    else if(num == 3)
    {
        QCursor *mycorsor = new QCursor(QPixmap(BLOCK_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "block";
    }
    else if(num == 4)
    {
        QCursor *mycorsor = new QCursor(QPixmap(GOAL_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "goal";
    }
    else if(num == 5)
    {
        this->setCursor(Qt::ArrowCursor);
        pressedobject = "trash";
    }
    else if(num == 6)
    {
        QCursor *mycorsor = new QCursor(QPixmap(PURPLEBLOCK_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "purpleblock";
    }
    else if(num == 7)
    {
        QCursor *mycorsor = new QCursor(QPixmap(BREAKABLEBLOCK1_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "breakableblock";
    }
    else if(num == 8)
    {
        QCursor *mycorsor = new QCursor(QPixmap(LONG_BLOCK_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "longblock";
    }
    else if(num == 9)
    {
        QCursor *mycorsor = new QCursor(QPixmap(STRONGMONSTER_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "strongmonster";
    }
    else if(num == 10)
    {
        QCursor *mycorsor = new QCursor(QPixmap(MAGE_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "mage";
    }
    else if(num == 11)
    {
        QCursor *mycorsor = new QCursor(QPixmap(SPRINGBLOCK_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "springblock";
    }
    else if(num == 200)
    {
        QCursor *mycorsor = new QCursor(QPixmap(ITEM_HP_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "hpitem";
    }
    else if(num == 201)
    {
        QCursor *mycorsor = new QCursor(QPixmap(ITEM_STONES_ICON_PIXMAP),-1,-1);
        this->setCursor(*mycorsor);
        pressedobject = "stoneitem";
    }
}

void mainhandler::keyPressEvent(QKeyEvent *event)
{
    //按键按下，key值放入容器，如果是长按触发的repeat就不判
    if(!event->isAutoRepeat())
        pressedkeys.insert(event->key());
    //判断是否运行，不然一直触发就一直不能timeout
    if(!keytimer->isActive())
        keytimer->start(GAME_RATE);
}

void mainhandler::mouseMoveEvent(QMouseEvent *event)
{
    ui->mapeditorWidget->setMouseTracking(true);
    if(pages->currentpage == MAP_EDITOR)
    {


    }
}

void mainhandler::mousePressEvent(QMouseEvent *event)
{
    if(pages->currentpage == MAP_EDITOR)
    {
        if(event->button() == Qt::LeftButton)
        {
            if(pressedobject =="basicmonster")
            {
                BasicMonster *object = new BasicMonster(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - BASICMONSTER_WIDTH/2,
                                                        -ui->mainstackedWidget->currentWidget()->y() + event->pos().y() - BASICMONSTER_HEIGHT/2);
                creature.push_back(object);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="strongmonster")
            {
                Creature *object = new StrongMonster(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - STRONGMONSTER_WIDTH/2,
                                                        -ui->mainstackedWidget->currentWidget()->y() + event->pos().y() - STRONGMONSTER_HEIGHT/2);
                creature.push_back(object);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="mage")
            {
                Creature *object = new Mage(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - MAGE_WIDTH/2,
                                                        -ui->mainstackedWidget->currentWidget()->y() + event->pos().y() - MAGE_HEIGHT/2);
                creature.push_back(object);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="block")
            {
                Block *object = new Block(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - BLOCK_WIDTH/2,
                                          -ui->mainstackedWidget->currentWidget()->y() + event->pos().y()- BLOCK_WIDTH/2);
                blocks.push_back(object);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="purpleblock")
            {
                Block *object = new PurpleBlock(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - BLOCK_WIDTH/2,
                                                -ui->mainstackedWidget->currentWidget()->y() + event->pos().y()- BLOCK_WIDTH/2);
                blocks.push_back(object);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="breakableblock")
            {
                Block *object = new BreakableBlock(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - BLOCK_WIDTH/2,
                                                   -ui->mainstackedWidget->currentWidget()->y() + event->pos().y()- BLOCK_WIDTH/2);
                blocks.push_back(object);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="longblock")
            {
                Block *object = new LongBlock(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - LONGBLOCK_WIDTH/2,
                                              -ui->mainstackedWidget->currentWidget()->y() + event->pos().y()- BLOCK_WIDTH/2);
                blocks.push_back(object);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="springblock")
            {
                Block *object = new SpringBlock(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - BLOCK_WIDTH/2,
                                              -ui->mainstackedWidget->currentWidget()->y() + event->pos().y()- BLOCK_WIDTH/2);
                blocks.push_back(object);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="hero")
            {
                hero = new Hero(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - HERO_WIDTH/2,
                                -ui->mainstackedWidget->currentWidget()->y() + event->pos().y() - HERO_HEIGHT/2);
                phero = new Hero(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - HERO_WIDTH/2,
                                 -ui->mainstackedWidget->currentWidget()->y() + event->pos().y() - HERO_HEIGHT/2);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="goal")
            {
                goal = new Goal(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - GOAL_WIDTH/2,
                                -ui->mainstackedWidget->currentWidget()->y() + event->pos().y() - GOAL_HEIGHT/2);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="hpitem")
            {
                Bullet *object = new HpItem(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - 24,
                                              -ui->mainstackedWidget->currentWidget()->y() + event->pos().y()- 24);
                enemybullets.push_back(object);
                qDebug()<<"spawned!";
            }
            if(pressedobject =="stoneitem")
            {
                Bullet *object = new Stone(-ui->mainstackedWidget->currentWidget()->x() + event->pos().x() - 14,
                                              -ui->mainstackedWidget->currentWidget()->y() + event->pos().y()- 14);
                enemybullets.push_back(object);
                qDebug()<<"spawned!";
            }
        }
        else if(event->button() == Qt::RightButton)
        {
            if(hero != nullptr && hero->rect.contains(event->pos()))
            {
                hero = nullptr;
            }
            if(goal != nullptr && goal->rect.contains(event->pos()))
            {
                goal = nullptr;
            }
            for(int i = 0; i < creature.size();i++)
            {
                if(creature[i]->rect.contains(event->pos()))
                {
                    creature.erase(creature.begin() + i);
                }
            }
            for(int i = 0; i < blocks.size();i++)
            {
                if(blocks[i]->rect.contains(event->pos()))
                {
                    blocks.erase(blocks.begin() + i);
                }
            }
            for(int i = 0; i < enemybullets.size();i++)
            {
                if(enemybullets[i]->rect.contains(event->pos()))
                {
                    enemybullets.erase(enemybullets.begin() + i);
                }
            }
        }
    }
}

void mainhandler::keyReleaseEvent(QKeyEvent *event)
{
    //QWidget::keyReleaseEvent(event);
    //按键释放，从容器中移除，如果是长按触发的repeat就不判断

    if(hero != nullptr)
    {
        if(!event->isAutoRepeat())
        {
            int temp = event->key();
            if(temp == Qt::Key_Right && pages->currentpage != MAP_EDITOR)
            {
                if(hero->x + hero->width <= GAME_WIDTH - hero->xspeed )
                {
                    if( hero->xspeed >=0)
                    {
                        hero->xspeed = 0;

                    }
                }
                else
                {
                    hero->x = GAME_WIDTH - hero->width;
                }

            }
            else if(temp == Qt::Key_Left && pages->currentpage != MAP_EDITOR)
            {
                if(hero->x >= 0 + hero->xspeed)
                {
                    hero->xspeed = 0;
                }
                else
                {
                    hero->x = 0;
                }
            }
            pressedkeys.remove(event->key());
        }
        if(pressedkeys.isEmpty())
        {
            keytimer->stop();
        }
    }
    else
    {
        pressedkeys.clear();
    }


}

void mainhandler::mapMove()
{
    if(pages->currentpage==NORMAL_LEVEL_1
            ||pages->currentpage == NORMAL_LEVEL_2
            ||pages->currentpage == NORMAL_LEVEL_3)
    {
        if(hero->x > GAME_WIDTH*7/10
                &&ui->mainstackedWidget->currentWidget()->x()>=-(ui->mainstackedWidget->currentWidget()->width()-GAME_WIDTH-30))
        {

            int temp = hero->x - GAME_WIDTH*7/10;
            mapmovedtotal += temp;
            ui->mainstackedWidget->currentWidget()->move(-mapmovedtotal,0);
            hero->x -= temp;
        }
        else if(hero->x < GAME_WIDTH*3/10
                &&ui->mainstackedWidget->currentWidget()->x() < 0 - 30)
        {
            int temp = hero->x - GAME_WIDTH*3/10;
            mapmovedtotal += temp;
            ui->mainstackedWidget->currentWidget()->move(-mapmovedtotal,0);
            hero->x -= temp;
        }

    }
}

void mainhandler::collisionDetection()
{
    bool herogravitydetected = false;
    if(pages->currentpage==NORMAL_LEVEL_1
            ||pages->currentpage==NORMAL_LEVEL_2
            ||pages->currentpage==NORMAL_LEVEL_3
            ||pages->currentpage==MAP_EDITOR
            ||pages->currentpage==MAP_EDITOR_GAME)
    {
        //with blocks
        if(hero != nullptr && hero->y >GAME_HEIGHT && pages->currentpage != MAP_EDITOR)
        {
            hero->hp = 0;
        }



        for(int i = 0;i < blocks.size();i++)
        {
            //block | creature
            for(int j = 0;j < creature.size();j++)
            {
                if(creature[j]->rect.intersects(blocks[i]->rect))
                {
                    if(creature[j]->y + creature[j]->height > blocks[i]->y)
                    {
                        //creature[j]->gravityinfluence = false;
                        creature[j]->yspeed = 0;
                        creature[j]->y = blocks[i]->y - creature[j]->height + 1;
                        //qDebug()<<creature[i]->x;
                    }
                }
            }
            //allybullet | block && out of boundary
            for(int j = 0; j < allybullets.size();j++)
            {
                if(!allybullets[j]->isblockpassable)
                {
                    if(blocks[i]->rect.intersects(allybullets[j]->rect))
                    {
                        allybullets.erase(allybullets.begin() + j);
                    }
                }
            }
            //enemy bullet | block && out of boundary
            for(int j = 0; j < enemybullets.size();j++)
            {
                if(!enemybullets[j]->isblockpassable)
                {
                    if(blocks[i]->rect.intersects(enemybullets[j]->rect))
                    {
                        enemybullets.erase(enemybullets.begin() + j);
                        qDebug()<<"pop";
                    }
                }

            }

            //hero | blocks
            if(hero != nullptr && (hero->rect.intersects(blocks[i]->rect)))
            {
                if(hero->y + hero->height > blocks[i]->y//主角下端在方块的下面
                        //&& hero->y + hero->height <=blocks[i]->y + 25
                        &&hero->x + hero->width >= blocks[i]->x + ui->mainstackedWidget->currentWidget()->x() //主角在方块左侧
                        &&hero->x <= blocks[i]->x + blocks[i]->width +ui->mainstackedWidget->currentWidget()->x())
                {
                    hero->gravityinfluence = false;
                    if(blocks[i]->typenum == 11)
                    {
                        hero->y = blocks[i]->y - hero->height - 1;
                        hero->yspeed = 15;
                    }
                    else
                    {
                        hero->yspeed = 0;
                        hero->y = blocks[i]->y - hero->height + 1;
                    }
                    //hero->y = blocks[i]->y - hero->height + 1;
                    herogravitydetected = true;
                    hero->pixmap.load(HERO_PIXMAP);
                    // qDebug()<<"hero x:"<<hero->x;
                }
                else
                {
                    hero->x = phero->x;
                    hero->y = phero->y;
                }

            }
            if(hero != nullptr && !herogravitydetected)
            {
                hero->gravityinfluence = true;
            }
        }
        if(hero != nullptr)
        {
            for(int i = 0; i < allybullets.size();i++)
            {
                if(allybullets[i]->x  < hero->rect.center().x() - GAME_WIDTH
                        ||allybullets[i]->x  > hero->rect.center().x() + GAME_WIDTH
                        ||allybullets[i]->y < 0
                        ||allybullets[i]->y > GAME_HEIGHT)
                {
                    allybullets.erase(allybullets.begin() + i);
                    qDebug()<<"hero bullet deleted!";
                }
            }
            //out of boundary
            for(int i = 0; i < enemybullets.size();i++)
            {
                if(enemybullets[i]->typenum != 200 && enemybullets[i]->typenum != 201
                        && (enemybullets[i]->x + ui->mainstackedWidget->currentWidget()->x() < hero->rect.center().x() - GAME_WIDTH
                        ||enemybullets[i]->x +ui->mainstackedWidget->currentWidget()->x() > hero->rect.center().x() + GAME_WIDTH
                        ||enemybullets[i]->y < enemybullets[i]->height
                        ||enemybullets[i]->y > GAME_HEIGHT))
                {
                    enemybullets.erase(enemybullets.begin() + i);
                    qDebug()<<"deleted!";
                    Debug();
                }
            }
        }
        //attack detection
        if(hero != nullptr && hero->attackcooltime == 1 && hero->iscooltime)//进程攻击判定      是1的原因是 因为keyupdate先执行updatecooltime后运行，导致加了1
        {

            for(int i = 0;i<creature.size();i++)
            {
                if(hero->isfaceingright && QRect(hero->x,hero->y,
                                                 1.5*HERO_WIDTH,HERO_HEIGHT).intersects(creature[i]->rect))
                {
                    creature[i]->hp -= 50;
                }
                else if(!hero->isfaceingright && QRect(hero->x - HERO_WIDTH,hero->y,
                                                       1.5*HERO_WIDTH,HERO_HEIGHT).intersects(creature[i]->rect))
                {
                    creature[i]->hp -= 50;
                }
            }
            for(int i = 0;i<blocks.size();i++)
            {
                if(hero->isfaceingright && QRect(hero->x,hero->y,
                                                 1.5*HERO_WIDTH,HERO_HEIGHT - 1).intersects(blocks[i]->rect))
                {
                    blocks[i]->hp -= 50;
                }
                else if(!hero->isfaceingright && QRect(hero->x - HERO_WIDTH,hero->y,
                                                       1.5*HERO_WIDTH,HERO_HEIGHT - 1).intersects(blocks[i]->rect))
                {
                    blocks[i]->hp -= 50;
                }
            }
        }
        //phero
        if(hero != nullptr &&phero != nullptr)
        {
            phero->x = hero->x;
            phero->y = hero->y;
        }
        //goal detection
        if(goal != nullptr && hero != nullptr && goal->rect.intersects(hero->rect))
        {
            if(pages->currentpage == NORMAL_LEVEL_1
                    ||pages->currentpage == NORMAL_LEVEL_2)
            {
                showNextStagePage();
            }
        }
        //with creature
        for(int i = 0;i < creature.size();i++)
        {
            if(creature[i]->y >GAME_HEIGHT)
            {
                creature[i]->hp = 0;
            }
            //melee creature attack detection
            if(creature[i]->typenum == 2 || creature[i]->typenum == 7)
            {
                if(hero != nullptr && creature[i]->attackcooltime == creature[i]->maxattackcooltime / 2
                        && creature[i]->iscooltime)//进程攻击判定      是/2的原因是 实现攻击延迟给予躲避的时间
                {
                    if(creature[i]->attackrange.intersects(hero->rect))
                    {
                        if(hero->x + hero->width <= creature[i]->rect.center().x())
                        {
                           // creature[i]->isfaceingright = false;
                            if(creature[i]->typenum == 2)
                            {
                                hero->hp -= 50;
                            }
                            else if(creature[i]->typenum == 7)
                            {
                                hero->hp -= 100;
                                hero->x -= 40;
                            }

                        }
                        else if(hero->x  > creature[i]->rect.center().x())
                        {
                            //creature[i]->isfaceingright = true;
                            if(creature[i]->typenum == 2)
                            {
                                hero->hp -= 50;

                            }
                            else if(creature[i]->typenum == 7)
                            {
                                hero->hp -= 100;
                                hero->x += 40;
                            }
                        }

                    }

                }
            }
            else if(creature[i]->typenum == 10)
            {

            }
            //allybullet | enemy
            for(int j = 0; j < allybullets.size();j++)
            {
                if(creature[i]->rect.intersects(allybullets[j]->rect))
                {
                    creature[i]->hp -= allybullets[j]->damage;
                    allybullets.erase(allybullets.begin() + j);
                }
            }
        }
        if(hero != nullptr)
        {
            for(int i = 0;i < enemybullets.size();i++)
            {
                if(enemybullets[i]->rect.intersects(hero->rect))
                {
                    hero->hp -= enemybullets[i]->damage;
                    if(enemybullets[i]->typenum == 201)
                    {
                        hero->stonenum += 15;
                    }
                    enemybullets.erase(enemybullets.begin() + i);
                    qDebug()<<"boom!";
                }
            }
        }
    }
}

void mainhandler::on_saveBtn_clicked()
{
    writeFile(seletedsavefilenum);
}

void mainhandler::updateDeathJudgement()
{
    if(hero != nullptr && phero != nullptr)
    {
        if(hero->hp <= 0)
        {
            showGameOverPage();
        }
    }
    for(int i = 0;i < creature.size();i++)
    {
        if(creature[i]->hp <= 0)
        {
            if(creature[i]->deathframe == 0)
            {
                creature[i]->deathframe ++;
            }
            else if(creature[i]->deathframe == DEAD_COMPLETE)
            {
                creature.erase(creature.begin() + i);
            }
        }
    }
    for(int i = 0;i < blocks.size();i++)
    {
        if(blocks[i]->hp <= 0)
        {
            blocks.erase(blocks.begin()+i);
        }
    }
}

void mainhandler::updateMonstersAI()
{
    //int randomnum = random();
    if(hero != nullptr && pages->currentpage != MAP_EDITOR)
    {
        //creature AI
        for(int i = 0;i < creature.size(); i++)
        {
            if((creature[i]->typenum == 2 || creature[i]->typenum ==7 ||creature[i]->typenum == 10)
                    && creature[i]->attackrange.intersects(hero->rect)
                    && !creature[i]->iscooltime)
            {
                    creature[i]->iscooltime = true;
                    creature[i]->xspeed = 0;
                    if(hero->x + hero->width <= creature[i]->rect.center().x())
                    {
                        creature[i]->isfaceingright = false;
                    }
                    else
                    {
                        creature[i]->isfaceingright = true;
                    }

            }
            bool isleftcliff = true;
            bool isrightcliff = true;
            for(int j = 0;j < blocks.size();j ++) //block stop
            {
                QRect r1(creature[i]->sensor.left(),
                         creature[i]->sensor.top(),
                         creature[i]->sensor.width(),
                         creature[i]->sensor.height()/2);
                QRect r2(creature[i]->sensor.left(),
                         creature[i]->sensor.bottom() + 1,
                         creature[i]->width / 3,
                         50);
                QRect r3(creature[i]->sensor.right(),
                         creature[i]->sensor.bottom() + 1,
                         creature[i]->width / 3,
                         50);//monster rect's 1/2 height
                if(r1.intersects(blocks[j]->rect))
                {
                    creature[i]->xspeed = -creature[i]->xspeed;
                   // qDebug()<<"intersects!";
                }
                else
                {
                    if(r2.intersects(blocks[j]->rect))
                    {
                        isleftcliff = false;
                    }
                    if(r3.intersects(blocks[j]->rect))
                    {
                        isrightcliff = false;
                    }
                }
            }
            if(isrightcliff || isleftcliff)
            {
                creature[i]->xspeed = -creature[i]->xspeed;
            }
           // if(randomnum == 1)//random stop
           // {
           //     creature[i]->xspeed = -creature[i]->xspeed;
           //     qDebug()<<"triggered!";
           // }
            creature[i]->x += creature[i]->xspeed;
        }
    }
}


void mainhandler::on_mapeditorplatBtn_clicked()
{
    showNormalModePage();
    readFile(seletedsavefilenum);
}

void mainhandler::on_backtomapdeitorBtn_clicked()
{
    showMapEditorPage();
    readFile(seletedsavefilenum);
    ui->backtomapdeitorBtn->hide();
}
