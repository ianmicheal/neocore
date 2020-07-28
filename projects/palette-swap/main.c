/*
  David Vandensteen
  2020
*/
#include <neocore.h>
#include <math.h>
#include "externs.h"

NEOCORE_INIT

int main(void) {
  static Image logo;
  static paletteInfo logo_swap_palette;
  BYTE i = 0;
  GPU_INIT
  image_init(&logo, &logo_sprite, &logo_sprite_Palettes);
  image_display(&logo, 50, 100);
  logo_swap_palette.palCount = logo.pali->palCount;

  for (i = 0; i < (logo.pali->palCount MULT16); i++) { logo_swap_palette.data[i] = RAND(0xFFFF); }
  logo_swap_palette.data[1] = 0x0000;

  while(1) {
    WAIT_VBL
    if (DAT_frameCounter % 8 == 0) {
      for (i = 0; i < (logo.pali->palCount MULT16); i++) { logo_swap_palette.data[i] = RAND(0xFFFF); }
      logo_swap_palette.data[1] = 0x0000;
      palette_swap(logo.pic.basePalette, &logo_swap_palette, false);
    }
    SCClose();
  };
  SCClose();
  return 0;
}
