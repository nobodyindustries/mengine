#ifndef ME_FONTS_H
#define ME_FONTS_H

#define ME_FONT_64_WIDTH 8
#define ME_FONT_64_HEIGHT 8
#define ME_FONT_64_LINE_HEIGHT 10

const unsigned char me_font_f64[56][8] = {

  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  /* [SP] */

  {0x3C, 0x7E, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66},  /* A */
  {0x7C, 0x7E, 0x66, 0x7C, 0x7E, 0x66, 0x7E, 0x7C},  /* B */
  {0x3C, 0x7E, 0x66, 0x60, 0x60, 0x66, 0x7E, 0x3C},  /* C */
  {0x7C, 0x7E, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x7C},  /* D */
  {0x7E, 0x7E, 0x60, 0x78, 0x78, 0x60, 0x7E, 0x7E},  /* E */
  {0x7E, 0x7E, 0x60, 0x78, 0x78, 0x60, 0x60, 0x60},  /* F */
  {0x3E, 0x7E, 0x60, 0x6E, 0x6E, 0x66, 0x7E, 0x3E},  /* G */
  {0x66, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66, 0x66},  /* H */
  {0x3C, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x3C},  /* I */
  {0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x7E, 0x3C}, /* J */
  {0x66, 0x6E, 0x7C, 0x78, 0x78, 0x7C, 0x6E, 0x66}, /* K */
  {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x7E}, /* L */
  {0x66, 0x7E, 0x5A, 0x5A, 0x42, 0x42, 0x66, 0x66}, /* M */
  {0x66, 0x76, 0x7E, 0x7E, 0x6E, 0x66, 0x66, 0x66}, /* N */
  {0x3C, 0x7E, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x3C}, /* O */
  {0x3C, 0x7E, 0x66, 0x7E, 0x7C, 0x60, 0x60, 0x60}, /* P */
  {0x3C, 0x7E, 0x66, 0x66, 0x6E, 0x6E, 0x7E, 0x3E}, /* Q */
  {0x3C, 0x7E, 0x66, 0x66, 0x7C, 0x7E, 0x66, 0x66}, /* R */
  {0x3E, 0x7E, 0x60, 0x7C, 0x3E, 0x06, 0x7E, 0x7C}, /* S */
  {0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, /* T */
  {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x3C}, /* U */
  {0x66, 0x66, 0x66, 0x66, 0x66, 0x6E, 0x3C, 0x18}, /* V */
  {0x66, 0x66, 0x42, 0x5A, 0x4A, 0x6E, 0x7E, 0x3C}, /* W */
  {0x66, 0x66, 0x66, 0x24, 0x18, 0x24, 0x66, 0x66}, /* X */
  {0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x18}, /* Y */
  {0x7E, 0x7E, 0x0E, 0x1C, 0x38, 0x70, 0x7E, 0x7E}, /* Z */

  {0x3C, 0x7E, 0x66, 0x6E, 0x76, 0x66, 0x7E, 0x3C}, /* O */
  {0x3C, 0x3C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C}, /* 1 */
  {0x7C, 0x7E, 0x0E, 0x1C, 0x38, 0x70, 0x7E, 0x7E}, /* 2 */
  {0x7C, 0x7E, 0x06, 0x7E, 0x7E, 0x06, 0x7E, 0x7C}, /* 3 */
  {0x66, 0x66, 0x66, 0x7E, 0x3E, 0x06, 0x06, 0x06}, /* 4 */
  {0x7E, 0x7E, 0x60, 0x7C, 0x7E, 0x06, 0x7E, 0x7C}, /* 5 */
  {0x3C, 0x7E, 0x60, 0x7C, 0x7E, 0x66, 0x7E, 0x3C}, /* 6 */
  {0x7E, 0x7E, 0x06, 0x1E, 0x1E, 0x06, 0x06, 0x06}, /* 7 */
  {0x3C, 0x7E, 0x66, 0x3C, 0x7E, 0x66, 0x7E, 0x3C}, /* 8 */
  {0x3C, 0x7E, 0x66, 0x7E, 0x3E, 0x06, 0x06, 0x06}, /* 9 */

  {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18}, /* ! */
  {0x36, 0x36, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00}, /* " */
  {0x24, 0x7E, 0x7E, 0x24, 0x24, 0x7E, 0x7E, 0x24}, /* # */
  {0x00, 0x66, 0x6E, 0x1C, 0x38, 0x76, 0x66, 0x00}, /* % */
  {0x0C, 0x3E, 0x6C, 0x7E, 0x6C, 0x7E, 0x3E, 0x0C}, /* & */
  {0x1C, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x1C}, /* ( */
  {0x38, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x38}, /* ) */
  {0x00, 0x18, 0x18, 0x7E, 0x7E, 0x18, 0x18, 0x00}, /* + */
  {0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x08, 0x10}, /* , */
  {0x00, 0x00, 0x00, 0x7E, 0x7E, 0x00, 0x00, 0x00}, /* - */
  {0x00, 0x06, 0x0E, 0x1C, 0x38, 0x70, 0x60, 0x00}, /* / */
  {0x7C, 0x7E, 0x06, 0x3E, 0x3C, 0x30, 0x00, 0x30}, /* ? */
  {0x00, 0x60, 0x70, 0x38, 0x1C, 0x0E, 0x06, 0x00}, /* \ */
  {0x3C, 0x7E, 0x6A, 0x6A, 0x6E, 0x60, 0x7E, 0x3C}, /* @ */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x7E}, /* _ */
  {0x00, 0x60, 0x38, 0x0E, 0x0E, 0x38, 0x60, 0x00}, /* > */
  {0x00, 0x7E, 0x7E, 0x00, 0x00, 0x7E, 0x7E, 0x00}, /* = */
  {0x00, 0x06, 0x1C, 0x70, 0x70, 0x1C, 0x06, 0x00}, /* < */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18}, /* . */

};

void me_font_f64_draw(MECanvas *c, MEVector2 p, int idx, int scale, MEColor color)
{
  Uint32 dx = p.x;
  Uint32 dy = p.y;
  unsigned char v;
  for(Uint32 y = 0; y < ME_FONT_64_HEIGHT; y++, dy += scale) {
    for(Uint32 x = 0; x < ME_FONT_64_WIDTH; x++, dx += scale) {
      v = (me_font_f64[idx][y] >> (7 - x)) & 0x01;
      if(v == 0x01)
        me_canvas_draw_rectangle(c,
                                 (MERectangle){
                                         (MEVector2) {dx, dy},
                                         scale,
                                         scale,
                                         0
                                    },
                                 color,
                                 true,
                                 color);
    }
    dx = p.x;
  }
}

unsigned int me_font_f64_idx(const char c)
{
  /* SPACE */
  if(c == 32)
    return 0;
  /* ALPHABETIC CHARS (CAPS): 65..90 -> 1..26 */
  else if(c >= 65 && c <= 90)
    return c - 64;
  /* ALPHABETIC CHARS (SMALLS): 97..122 -> 1..26 */
  else if(c >= 97 && c <= 122)
    return c - 96;
  /* NUMBERS: 48..57 ->  27..36 */
  else if(c >= 48 && c <= 57)
    return c - 21;
  /* SPECIAL CHARS */
  else {
    switch(c) {
      case '!': return 37;
      case '"': return 38;
      case '#': return 39;
      case '%': return 40;
      case '&': return 41;
      case '(': return 42;
      case ')': return 43;
      case '+': return 44;
      case ',': return 45;
      case '-': return 46;
      case '/': return 47;
      case '?': return 48;
      case '\\': return 49;
      case '@': return 50;
      case '_': return 51;
      case '>': return 52;
      case '=': return 53;
      case '<': return 54;
      case '.': return 55;
      default: return 0;
    }
  }
}

void font_64_write_string(MECanvas *c, const char *s, MEVector2 p, Uint32 scale, MEColor color)
{
  const char *cs = s;
  int cx = p.x;
  int cy = p.y;
  while(*cs != '\0') {
    if(*cs == '\n') {
      cy += (ME_FONT_64_LINE_HEIGHT * scale);
      cx = p.x;
    } else {
      me_font_f64_draw(c, (MEVector2){cx, cy}, me_font_f64_idx(*cs), scale, color);
      cx += (ME_FONT_64_WIDTH * scale);
    }
    cs++;
  }
  return;
}

#endif