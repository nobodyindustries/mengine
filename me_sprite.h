#ifndef ME_SPRITE_H
#define ME_SPRITE_H

#include <stdio.h>

#include "me_geometry.h"
#include "me_color.h"
#include "me_canvas.h"

#define ME_SPRITE_IDX(x, y, w) ((y) * (w)) + (x)

typedef struct me_sprite {
  MEVector2 position; // Top-left position
  Uint32 magic;       // Magic number
  Uint32 version;     // MDT format version
  Uint32 width;       // Width
  Uint32 height;      // Height
  MEColor tcolor;     // Transparent color
  MEColor *data;      // Pixel data
} MESprite;

// TODO: Load sprite from data with same format as an array of bytes

// Load sprite from file, will return NULL if error.
MESprite *me_sprite_load(const char *path, MEVector2 position) {

  MESprite *sprite = (MESprite *) calloc(1, sizeof(MESprite));
  if (sprite == NULL) {
    return NULL;
  }

  sprite->position.x = position.x;
  sprite->position.y = position.y;

  FILE *sprite_file = fopen(path, "rb");
  if(sprite_file == NULL) {
    goto error_file_open;
  }

  size_t ret = fread(&(sprite->magic), sizeof(Uint32), 1, sprite_file);
  if(ret != 1) {
    goto error_read_constants;
  }
  sprite->magic = htonl(sprite->magic);
  ret = fread(&(sprite->version), sizeof(Uint32), 1, sprite_file);
  if(ret != 1) {
    goto error_read_constants;
  }
  sprite->version = htonl(sprite->version);
  ret = fread(&(sprite->width), sizeof(Uint32), 1, sprite_file);
  if(ret != 1) {
    goto error_read_constants;
  }
  sprite->width = htonl(sprite->width);
  ret = fread(&(sprite->height), sizeof(Uint32), 1, sprite_file);
  if(ret != 1) {
    goto error_read_constants;
  }
  sprite->height = htonl(sprite->height);
  ret = fread(&(sprite->tcolor), sizeof(Uint32), 1, sprite_file);
  if(ret != 1) {
    goto error_read_constants;
  }
  sprite->tcolor = htonl(sprite->tcolor);

  Uint32 n_pixels = sprite->width * sprite->height;

  sprite->data = (MEColor *) calloc(n_pixels, sizeof(Uint32));
  if(sprite->data == NULL) {
    goto error_init_data;
  }
  for(Uint32 i = 0; i < n_pixels; i++) {
    ret = fread(&(sprite->data[i]), sizeof(Uint32), 1, sprite_file);
    if(ret != 1) {
      goto error_read_data;
    }
    sprite->data[i] = htonl(sprite->data[i]);
  }

  fclose(sprite_file);
  return sprite;

error_read_data:
error_init_data:
error_read_constants:
  fclose(sprite_file);
error_file_open:
  free(sprite);
  return NULL;
}

void me_sprite_destroy(MESprite *sprite) {
  free(sprite->data);
  free(sprite);
}

void me_sprite_draw(MESprite *s, MECanvas *c) {
  for(int y = s->position.y; y < (s->position.y + s->height); y++) {
    for(int x = s->position.x; x < (s->position.x + s->width); x++) {
      MEColor p = s->data[ME_SPRITE_IDX(x, y, s->width)];
      if(p != s->tcolor) {
        me_canvas_set(c, (MEVector2) {x, y}, p);
      }
    }
  }
}


#endif//ME_SPRITE_H
