#ifndef ME_COLOR_H
#define ME_COLOR_H

#include <SDL.h>

typedef Uint32 MEColor;
typedef Uint8 MEColorValue;

// Color format -> RGB888
typedef enum me_color_components {
  MEColorRed = 1,
  MEColorGreen = 2,
  MEColorBlue = 3
} MEColorComponent;

MEColorValue me_color_get_value(MEColor color, MEColorComponent component) {
  // Casting to smaller types with unsigned values is well-defined and
  // drops the most significant bytes
  switch(component) {
    case MEColorBlue:
      return (MEColorValue) (color & 0x000000FF);
    case MEColorGreen:
      return (MEColorValue) ((color >> 8) & 0x000000FF);
    case MEColorRed:
      return (MEColorValue) ((color >> 16) & 0x000000FF);
    default:
      return 0x00;
  }
}


#endif// ME_COLOR_H
