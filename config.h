//道具类都放入了敌方子弹类中，因为碰到英雄消失的机制差不多
//



#ifndef CONFIG_H
#define CONFIG_H
#define HERO_PIXMAP ":/resource/hero_walk.png"
#define HERO_JUMP_PIXMAP ":/resource/hero_jump.png"
#define HERO_LEFT_PIXMAP ":/resource/hero_walk_left.png"
#define HERO_JUMP_LEFT_PIXMAP ":/resource/hero_jump_left.png"
#define HERO_ATTACK_PIXMAP ":/resource/hero_attack.png"
#define HERO_ATTACK_LEFT_PIXMAP ":/resource/hero_attack_left.png"
#define HERO_THROW_LEFT_PIXMAP ":/resource/hero_throw_left.png"
#define HERO_THROW_RIGHT_PIXMAP ":/resource/hero_throw_right.png"
#define HERO_MAX_HP 500
#define HERO_DAMAGE 50
#define HERO_ATTACK_COOLTIME 25
#define HERO_SHOOTING_COOLTIME 24
#define HERO_MAXSPEED 5
#define HERO_JUMP 10
#define HERO_ACC 1
#define HERO_WIDTH 48
#define HERO_HEIGHT 48
#define HERO_FRAME 25

#define HERO_BULLET_PIXMAP ":/resource/hero_bullet.png"
#define HERO_BULLET_WIDTH_HEIGHT 16


#define BLOCK_PIXMAP ":/resource/block.png"
#define LONG_BLOCK_PIXMAP ":/resource/longblock.png"
#define PURPLEBLOCK_PIXMAP ":/resource/purpleblock.png"
#define BREAKABLEBLOCK1_PIXMAP ":/resource/breakableblock1.png"
#define BREAKABLEBLOCK2_PIXMAP ":/resource/breakableblock2.png"
#define BREAKABLEBLOCK3_PIXMAP ":/resource/breakableblock3.png"
#define SPRINGBLOCK_PIXMAP ":/resource/springblock.png"
#define BLOCK_WIDTH 50
#define LONGBLOCK_WIDTH 500

#define BASICMONSTER_PIXMAP ":/resource/monsters/basicmonster/Walk.png"
#define BASICMONSTER_ICON_PIXMAP ":/resource/monsters/basicmonster/Red.png"
#define BASICMONSTER_ATTACK_PIXMAP ":/resource/monsters/basicmonster/Attack.png"
#define BASICMONSTER_ATTACK_RIGHT_PIXMAP ":/resource/monsters/basicmonster/Attack_right.png"
#define BASICMONSTER_WALK_LEFT_PIXMAP ":/resource/monsters/basicmonster/Walk.png"
#define BASICMONSTER_WALK_RIGHT_PIXMAP ":/resource/monsters/basicmonster/Walk_right.png"
#define BASICMONSTER_DEATH_RIGHT_PIXMAP ":/resource/monsters/basicmonster/Death_right.png"
#define BASICMONSTER_DEATH_LEFT_PIXMAP ":/resource/monsters/basicmonster/Death.png"
#define BASICMONSTER_WIDTH 48
#define BASICMONSTER_HEIGHT 48
#define BASICMONSTER_ATTACK_COOLTIME 24
#define BASICMONSTER_FRAME 50
#define BASICMONSTER_DEATH_FRAME 24

#define STRONGMONSTER_PIXMAP ":/resource/monsters/strongmonster/strongmonster.png"
#define STRONGMONSTER_WALK_RIGHT_PIXMAP ":/resource/monsters/strongmonster/Walk_right.png"
#define STRONGMONSTER_WALK_LEFT_PIXMAP ":/resource/monsters/strongmonster/Walk_left.png"
#define STRONGMONSTER_ATTACK_RIGHT_PIXMAP ":/resource/monsters/strongmonster/Attack_right.png"
#define STRONGMONSTER_ATTACK_LEFT_PIXMAP ":/resource/monsters/strongmonster/Attack_left.png"
#define STRONGMONSTER_DEATH_RIGHT_PIXMAP ":/resource/monsters/strongmonster/Death_right.png"
#define STRONGMONSTER_DEATH_LEFT_PIXMAP ":/resource/monsters/strongmonster/Death_left.png"
#define STRONGMONSTER_WIDTH 100
#define STRONGMONSTER_HEIGHT 100

#define MAGE_PIXMAP ":/resource/monsters/mage/Mage.png"
#define MAGE_WALK_LEFT_PIXMAP ":/resource/monsters/mage/Walk_left.png"
#define MAGE_WALK_RIGHT_PIXMAP ":/resource/monsters/mage/Walk_right.png"
#define MAGE_ATTACK_LEFT_PIXMAP ":/resource/monsters/mage/Attack_left.png"
#define MAGE_ATTACK_RIGHT_PIXMAP ":/resource/monsters/mage/Attack_right.png"
#define MAGE_DEATH_LEFT_PIXMAP ":/resource/monsters/mage/Death_left.png"
#define MAGE_DEATH_RIGHT_PIXMAP ":/resource/monsters/mage/Death_right.png"
#define MAGE_WIDTH 60
#define MAGE_HEIGHT 60
#define MAGE_BULLET_PIXMAP ":/resource/monsters/mage/Attack_ball.png"
#define MAGE_BULLET_WIDTH 12

#define DEAD_COMPLETE 1000


#define GOAL_PIXMAP ":/resource/goal.png"
#define GOAL_WIDTH 30
#define GOAL_HEIGHT 30

#define MAINMENU_PIXMAP ":/resource/mainmenu.png"
#define STAGE_1_PIXMAP ":/resource/background1.png"



#define NORMAL_LEVEL_2  5656
#define NORMAL_LEVEL_3  65656



#define TRASH_PIXMAP ":/resource/trash.png"

#define PURPLE_BUTTON_CONTINUE_PIXMAP ":/resource/buttons/purple_btn_continue.png"
#define PURPLE_BUTTON_QUIT_PIXMAP ":/resource/buttons/purple_btn_quit.png"
#define PURPLE_BUTTON_MAINMENU_PIXMAP ":/resource/buttons/purple_btn_mainmenu.png"
#define PURPLE_BUTTON_RETRY_PIXMAP ":/resource/buttons/purple_btn_retry.png"
#define PURPLE_BUTTON_HELP_PIXMAP ":/resource/buttons/purple_btn_help.png"
#define PURPLE_BUTTON_START_PIXMAP ":/resource/buttons/purple_btn_start.png"
#define PURPLE_BUTTON_MAPEDITOR_MAPEDITOR_PIXMAP ":/resource/buttons/purple_btn_mapeditor_mapeditor.png"
#define PURPLE_BUTTON_SAVE1_PIXMAP ":/resource/buttons/purple_btn_save1.png"
#define PURPLE_BUTTON_SAVE2_PIXMAP ":/resource/buttons/purple_btn_save2.png"
#define PURPLE_BUTTON_SAVE3_PIXMAP ":/resource/buttons/purple_btn_save3.png"

#define ITEM_HP_PIXMAP ":/resource/items/hp.png"
#define ITEM_STONES_PIXMAP ":/resource/items/stones.png"
#define ITEM_STONES_ICON_PIXMAP ":/resource/items/stone_icon.png"

#define MAINMENU  0
#define NORMAL_GAME  1
#define MAP_EDITOR  2
#define HELP  3
#define GAMEOVER  4
#define NEXTSTAGE 5
#define MAP_EDITOR_GAME 6
#define NORMAL_LEVEL_1  7
#define SAVEFILE_SELECT  8


#define GAME_RATE  20
#define GAME_WIDTH  960
#define GAME_HEIGHT  600

#define GRAVITY 1

#endif // CONFIG_H
