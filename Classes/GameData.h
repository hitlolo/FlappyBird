#pragma once


typedef enum :uint8_t {
	ColliderTypeBird = 0x1,
	ColliderTypeLand = 0x1 << 1,
	ColliderTypePip = 0x1 << 2
} ColliderType;

#define CHECK_POINT          Director::getInstance()->getVisibleOrigin().x +  Director::getInstance()->getVisibleSize().width/4

#define MSG_GAME_START       "GO"
#define MSG_GAME_STOP        "STOP"
#define MSG_PIPE_START       "pipe_start"
#define MSG_GET_POINT        "point"

#define RES_PLIST           "images.plist"
#define RES_PNG             "images.png"

#define PIC_LOADING         "splash.png"


#define PIC_BG_DAY           "bg_day.png"
#define PIC_BG_NIGHT         "bg_night.png"
#define PIC_BG_LAND          "land.png"
#define PIC_BG_COPYRIGHT     "brand_copyright.png"

#define PIC_READY            "text_ready.png"
#define PIC_TUTOR            "tutorial.png"

#define PIC_PIPE_DAY_UP      "pipe_up.png"
#define PIC_PIPE_DAY_DOWN    "pipe_down.png"

#define THROUGH_HEIGHT		  100										//С��ͨ���������Ӽ�ĸ߶�
#define PIPE_RANGE			  200										//�����ƶ�Yֵ�ķ�Χ
#define READY_DISTANCE        100
#define PIPE_HEIGHT           320

#define PIC_PIPE_NIGHT_UP    "pipe2_up.png"
#define PIC_PIPE_NIGHT_DOWN  "pipe2_down.png"

#define PIC_BG_TITLE         "title.png"

#define FONT_BIG             "font1.fnt"
#define NAME_SCORE           "SCORE"                                //scoreSprite������

//physics attribute
#define GRAVITY				 Point(0,-980)							//�������ٶ�
#define VELOCITY			 Point(0,260)							//С�������Ϸ��ٶ�
#define BIRD_RADIUS		     15										//��İ뾶


#define PIC_B_PLAY           "button_play.png"


#define M_DIE                "sfx_die.ogg"
#define M_HIT                "sfx_hit.ogg"
#define M_GETPOINT		     "sfx_point.ogg"
#define M_WING			     "sfx_wing.ogg"
#define M_SWOOSH		     "sfx_swooshing.ogg"



//Physics
#define GRAVITY											Point(0,-980)							//�������ٶ�
#define VELOCITY										Point(0,260)							//С�������Ϸ��ٶ�
#define THROUGH_HEIGHT									120										//С��ͨ���������Ӽ�ĸ߶�
