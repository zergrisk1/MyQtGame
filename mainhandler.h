//controlLer 负责所有类与类之间互动的类 碰撞检测等



#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include"creature.h"
#include"pages.h"
#include"blocks.h"
#include"bullets.h"
#include <QWidget>
#include<QTimer>
#include<QKeyEvent>
#include<QString>
#include<QVector>
#include<QSignalMapper>

namespace Ui {
class mainhandler;
}

class mainhandler : public QWidget
{
    Q_OBJECT
public:
    int mapmovedtotal = 0;
    int currentcursor = 0;
    int seletedsavefilenum = 0;
    int t = 0;
public:
    void initStackedWidget();
    void playGame();
    explicit mainhandler(QWidget *parent = 0);
    ~mainhandler();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mapMove();
    void updatePosition();
    void updateRectPosition();
    void collisionDetection();
    void gravityOn();
    void keyUpdate();
    void InitStack();
    void updateEtc();
    void drawButtonsIcon();
    void updateDeathJudgement();
    void updateMonstersAI();
private slots:
    void showNormalModePage();
    void showMapEditorPage();
    void showHelpPage();
    void showMainMenuPage();
    void showGameOverPage();
    void showNextStagePage();
    void showSaveFileSelectPage();
    void Debug();
    void currentpage();
    void changeCursorIcon(int num);
    void mapRightMove();
    void mapLeftMove();
    void showMenu();
    void hideMenu();
    void timerRestart();
    void readFile(int num);
    void writeFile(int num);
    void on_saveBtn_clicked();
    int random();
    int inttimer();
    void on_mapeditorplatBtn_clicked();
    void on_backtomapdeitorBtn_clicked();
    void updateHeroLabel();

signals:
    void rightKeyPressed();
    void leftKeyPressed();



private:
    Ui::mainhandler *ui;
    Creature *monster = nullptr;
    Pages *pages = nullptr;
    Hero *hero = nullptr;
    Hero *phero = nullptr;
    QVector <Creature*> creature;
    QVector <Block*> blocks;
    QVector <Block*> detectedblocks;
    QVector <Bullet*> allybullets;
    QVector <Bullet*> enemybullets;
    QPixmap pagesPixMap;
    QTimer *timer;
    QString str;
    QSet<int> pressedkeys;
    QTimer *keytimer;
    QPixmap temp;
    Goal *goal = nullptr;
    QSignalMapper *signalmapper;
    QSignalMapper *savefilesignalmapper;
    QString pressedobject;
    QString filestring;
};

#endif // MAINHANDLER_H
