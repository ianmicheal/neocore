/*
	David Vandensteen
	2018
*/
  // short  ->  2 bytes
  // word   ->  2 bytes
  // dword  ->  4 bytes
  // char   ->  1 byte
  // int    ->  4 bytes
  // byte   ->  1 byte

#ifndef NEOCORE_H
#define NEOCORE_H
#include <DATlib.h>
#include <math.h>

#define NEOCORE_INIT \
  typedef struct bkp_ram_info { \
    WORD debug_dips; \
    BYTE stuff[254]; \
  } bkp_ram_info; \
  bkp_ram_info bkp_data;

#define __ALIGN1__      __attribute__ ((aligned (1)))
#define __ALIGN2__      __attribute__ ((aligned (2)))
#define __ALIGN4__      __attribute__ ((aligned (4)))
#define __ALIGN64__ 		__attribute__ ((aligned (64)))
#define __ALIGN128__		__attribute__ ((aligned (128)))

#define MULT2              << 1
#define MULT4              << 2
#define MULT8              << 3
#define MULT16             << 4
#define MULT32             << 5
#define MULT64             << 6
#define DIV2               >> 1
#define DIV4               >> 2
#define DIV8               >> 3
#define DIV16              >> 4
#define DIV32              >> 5
#define DIV64              >> 6

#define Y_OFFSCREEN 240
#define X 0
#define Y 1

#define SHRUNK_TABLE_PROP_SIZE    0x2fe

#define JOYPAD  		    	BYTE p1, ps;
#define JOYPAD_READ		    p1 = volMEMBYTE(P1_CURRENT); ps = volMEMBYTE(PS_CURRENT);
#define JOYPAD_READ_EDGE  p1 = volMEMBYTE(P1_EDGE); ps = volMEMBYTE(PS_EDGE);
#define JOYPAD_IS_UP			p1&JOY_UP
#define JOYPAD_IS_DOWN		p1&JOY_DOWN
#define JOYPAD_IS_LEFT		p1&JOY_LEFT
#define JOYPAD_IS_RIGHT		p1&JOY_RIGHT
#define JOYPAD_IS_START   ps&P1_START
#define JOYPAD_IS_A       p1&JOY_A
#define JOYPAD_IS_B       p1&JOY_B
#define JOYPAD_IS_C       p1&JOY_C
#define JOYPAD_IS_D       p1&JOY_D

#define LOGGER_ON
#define LOGGER_X_INIT   1
#define LOGGER_Y_INIT   2

#define BOXCOPY(bFrom, bTo)   memcpy(bTo, bFrom, sizeof(Box))

#define FIX(value) value * 65536
#define RAND(value) rand() % value

#define SHRUNK_EXTRACT_X(value) value >> 8
#define SHRUNK_EXTRACT_Y(value) (BYTE)value

// overwrite aSpriteHide DAT macro
//#undef aSpriteHide(as)
//#define aSpriteHide(as)            { (as)->flags|=0x0080; clearSprites(as->baseSprite, as->tileWidth); }
//#define aSpriteHideDAT(as)         { (as)->flags|=0x0080; }

// overwrite pictureHide, pictureShow DAT func
// #define pictureHide(p) { short x = (p)->posX; short y = (p)->posY; pictureSetPos(p, HIDE_X, HIDE_Y); (p)->posX = x; (p)->posY = y; loggerInfo("OVER PHIDE"); }
// #define pictureShow(p) { pictureSetPos(p, (p)->posX, (p)->posY); loggerInfo("OVER PSHOW"); }

enum direction { NONE, UP, DOWN, LEFT, RIGHT };

typedef struct Vec2int Vec2int;
struct Vec2int {
  int x;
  int y;
};

typedef struct Vec2short Vec2short;
struct Vec2short {
  short x;
  short y;
};

typedef struct Vec2byte Vec2byte;
struct Vec2byte {
  BYTE x;
  BYTE y;
};

typedef struct Box Box;
struct Box {
  Vec2short p0;
  Vec2short p1;
  Vec2short p2;
  Vec2short p3;
  Vec2short p4;
  short width;
  short height;
  short widthOffset;
  short heightOffset;
};

typedef struct picture5 picture5;
struct picture5 {
  picture pic0;
  picture pic1;
  picture pic2;
  picture pic3;
  picture pic4;
};

typedef struct aSpritePhysic aSpritePhysic;
struct aSpritePhysic {
  aSprite as; //50 bytes
  Box box;
  WORD height;
};

typedef struct picturePhysic picturePhysic;
struct picturePhysic {
  picture p;
  Box box;
  BOOL visible;
};

typedef struct picturePhysicShrunkCentroid picturePhysicShrunkCentroid;
struct picturePhysicShrunkCentroid {
  picturePhysic pp;
  pictureInfo *pi;
  paletteInfo *pali;
  Vec2short positionCenter;
  Box boxOrigin;
};
//  a
void animated_sprite_physic_display(aSpritePhysic *asp, spriteInfo *si, paletteInfo *pali, short posX, short posY, WORD anim);
void animated_sprite_physic_collide(aSpritePhysic *asp, Box *box); // TODO not implementd ??? needed ???
void animated_sprite_physic_set_position(aSpritePhysic *asp, short x, short y);
void animated_sprite_physic_move(aSpritePhysic *asp, short x, short y);
void animated_sprite_physic_shrunk(aSprite *as, spriteInfo *si, WORD shrunk_value);

void animated_sprite_display(aSprite *as, spriteInfo *si, paletteInfo *pali, short posX, short posY, WORD anim);
WORD animated_sprite_index_auto(spriteInfo *si);
void animated_sprite_flash(aSprite *as, BYTE freq);
// todo
//void animated_sprite_flash_update(aSprite *as);
BOOL animated_sprite_is_visible(aSprite *as);
void animated_sprite_shrunk(aSprite *as, spriteInfo *si, WORD shrunk_value);

#define animated_sprite_set_animation(as, anim) aSpriteSetAnim(as, anim)
#define animated_sprite_animate(as) aSpriteAnimate(as)
#define animated_sprite_move(as, xOffset, yOffset) aSpriteMove(as, xOffset, yOffset)

// b
BYTE boxes_collide(Box *b, Box *boxes[], BYTE box_max);
BOOL box_collide(Box *b1, Box *b2);
void box_init(Box *b, short width, short height, short widthOffset, short heightOffset);
void box_update(Box *b, short x, short y);
void box_debug_update(picture5 *pics, Box *box);
void box_display(picture5 *pics, Box *box, pictureInfo *pi, paletteInfo *pali);
void box_shrunk(Box *b, Box *bOrigin, WORD shrunkValue);

// todo - deprecated ?
void box_resize(Box *Box, short edge);

// c
void inline clear_vram();

// f
void inline fix_print_neocore(int x, int y, char *label);

// g
void inline gpu_init();

// i
void image_physic_shrunk_centroid_init(picturePhysicShrunkCentroid *pps, pictureInfo *pi, paletteInfo *pali, short xCenter, short yCenter);
void image_physic_shrunk_centroid_set_position(picturePhysicShrunkCentroid *pps, short x, short y);
void image_physic_shrunk_centroid_move(picturePhysicShrunkCentroid *pps, short xShift, short yShift);
void image_physic_shrunk_centroid_update(picturePhysicShrunkCentroid *pps, WORD shrunk);
void image_physic_shrunk_centroid_display(picturePhysicShrunkCentroid *pps, WORD shrunk);
void image_physic_display(picturePhysic *pp, pictureInfo *pi, paletteInfo *pali, short posX, short posY);
void image_physic_set_position(picturePhysic *pp, short x, short y);
void image_physic_move(picturePhysic *pp, short x, short y);
void image_shrunk(picture *p, pictureInfo *pi, WORD shrunk_value);
void images_show(picture *p, WORD max, BOOL visible); // TODO deprecated, implement picturesHide, picturesShow, pictureHide, pictureShow
void image5_show(picture5 *pics, BOOL visible); // TODO deprecated
void image_display(picture *p, pictureInfo *pi, paletteInfo *pali, short posX, short posY);
void image_shrunk_centroid(picture *p, pictureInfo *pi, short centerPosX, short centerPosY, WORD shrunk_value);
void image_flash(picture *p, BYTE freq);
WORD image_get_sprite_index_autoinc(pictureInfo *pi);

// todo - change signature
BOOL vector_is_left(short x, short y, short v1x, short v1y, short v2x, short v2y);

// j
void        joypad_update();
void        joypad_update_edge();
BOOL        joypad_is_up();
BOOL        joypad_is_down();
BOOL        joypad_is_left();
BOOL        joypad_is_right();
BOOL        joypad_is_start();
BOOL        joypad_is_a();
BOOL        joypad_is_b();
BOOL        joypad_is_c();
BOOL        joypad_is_d();
void inline joypad_debug();

// l
void        logger_init();
void        logger_set_position(WORD _x, WORD _y);
WORD inline logger_info(char *txt);
void inline logger_word(char *label, WORD value);
void inline logger_int(char *label, int value);
void inline logger_dword(char *label, DWORD value);
void inline logger_short(char *label, short value);
void inline logger_byte(char *label, BYTE value);
void inline logger_bool(char *label, BOOL value);
void inline logger_animated_sprite(char *label, aSprite *as);
void inline logger_spriteInfo(char *label, spriteInfo *si);
void inline logger_box(char *label, Box *b);
void inline logger_pictureInfo(char *label, pictureInfo *pi);

// p
void palette_disable_autoinc();
void palette_enable_autoinc();
BYTE palette_get_index();
BYTE palette_set_index(BYTE index);
BYTE palette_get_index_autoinc(paletteInfo *pali);

// m
void mask_display(picture pic[], Vec2short vec[], BYTE vector_max); // TODO rename ? (vectorsDisplay)
void mask_update(short x, short y, Vec2short vec[], Vec2short offset[], BYTE vector_max); // TODO rename ? (vectorsDebug)
// TODO hardcode point\dot asset

void vec2int_init(Vec2int *vec, int x, int y);
void vec2short_init(Vec2short *vec, short x, short y);
void vec2byte_init(Vec2byte *vec, BYTE x, BYTE y);

BOOL vectors_collide(Box *box, Vec2short vec[], BYTE vector_max);

// s
WORD        shrunk_forge(BYTE xc, BYTE yc);
void inline shrunk_addr(WORD addr, WORD shrunk_value);
WORD        shrunk_range(WORD addr_start, WORD addr_end, WORD shrunk_value);
WORD        shrunk_prop_table_get(WORD index); // TODO rename shrunkGetPropTable ?
char        sin_table_get(WORD index);
void        scroller_display(scroller *s, scrollerInfo *si, paletteInfo *pali, short posX, short posY);
void        sprite_disable_autoinc();
void        sprite_enable_autoinc();
WORD        sprite_get_Index();
void        sprite_set_index(WORD index);
WORD        scroller_get_sprite_index_autoinc(scrollerInfo *si);
void        scroller_move(scroller *sc, short x, short y);
int         shrunk_centroid_get_translated_x(short centerPosX, WORD tileWidth, BYTE shrunkX);
int         shrunk_centroid_get_translated_y(short centerPosY, WORD tileHeight, BYTE shrunkY);

// w
DWORD inline wait_vbl_max(WORD nb);
#define WAIT_VBL waitVBlank();

#endif
