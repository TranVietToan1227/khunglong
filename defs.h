#ifndef _DEFS__H
#define _DEFS__H




const int  SCREEN_WIDTH =800;
const int  SCREEN_HEIGHT =600;
#define WINDOW_TITLE "Hello word!"
#define BACKGROUND_IMG  "forest.jpg"
#define ANH_NHAN_VAT "anhkhunglong.png"
const int PLAYER_X=50;
const int PLAYER_Y=450;
const int PLAYER_WIDTH=70;
const int PLAYER_HEIGHT=70;

static const int distancebgr1=5;
static const int distancebgr2=8;
static const int distanceobs1=4;
static const int distanceobs2=6;

static const char*  BIRD_SPRITE_FILE = "chim_bay.png";
const int BIRD_CLIPS[][4] = {
    {0, 0, 182, 168},
    {181, 0, 182, 168},
    {364, 0, 182, 168},
    {547, 0, 182, 168},
    {728, 0, 182, 168},

    {0, 170, 182, 168},
    {181, 170, 182, 168},
    {364, 170, 182, 168},
    {547, 170, 182, 168},
    {728, 170, 182, 168},

    {0, 340, 182, 168},
    {181, 340, 182, 168},
    {364, 340, 182, 168},
    {547, 340, 182, 168},
};
const int BIRD_FRAMES = sizeof(BIRD_CLIPS)/sizeof(int)/4;


#endif
