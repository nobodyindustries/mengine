#ifndef ME_CANVAS_H
#define ME_CANVAS_H

#include "me_geometry.h"
#include "me_color.h"
#include "me_math.h"
#include <SDL.h>
#include <math.h>

#define ME_CANVAS_IDX(x, y) (x) + ((y) * (ME_WINDOW_WIDTH))

typedef struct me_canvas {
    Uint32 *pixels;
    Uint32 width;
    Uint32 height;
} MECanvas;

MERet me_canvas_init(MECanvas **canvas, Uint32 width, Uint32 height) {
    (*canvas) = (MECanvas *) calloc(1, sizeof(MECanvas));
    if ((*canvas) == NULL) {
        return ME_ERROR_CANVAS_INIT;
    }
    (*canvas)->pixels = (Uint32 *) calloc((size_t) width * height, sizeof(Uint32));
    (*canvas)->width = width;
    (*canvas)->height = height;
    if ((*canvas)->pixels == NULL) {
        free(*canvas);
        return ME_ERROR_CANVAS_INIT;
    }
    return ME_OK;
}

void me_canvas_destroy(MECanvas **canvas) {
    free((*canvas)->pixels);
    free(*canvas);
}

void me_canvas_set(MECanvas *c, MEVector2 v, MEColor color) {
    if (v.x >= 0 && v.x < ME_WINDOW_WIDTH && v.y >= 0 && v.y < ME_WINDOW_HEIGHT) {
        c->pixels[ME_CANVAS_IDX(v.x, v.y)] = color;
    }
}

void me_canvas_clear(MECanvas *c, MEColor color) {
    for (int idx = 0; idx < c->height * c->width; idx++) {
        c->pixels[idx] = color;
    }
}

void me_canvas_draw_line(MECanvas *c, MELine line, MEColor color) {
    // These can't be unsigned
    int delta_x = abs(line.v1.x - line.v0.x);
    int slope_x = line.v0.x < line.v1.x ? 1 : -1;
    int delta_y = -abs(line.v1.y - line.v0.y);
    int slope_y = line.v0.y < line.v1.y ? 1 : -1;
    int error = delta_x + delta_y;
    int error_2;
    for (;;) {
        me_canvas_set(c, (MEVector2){line.v0.x, line.v0.y}, color);
        if (line.v0.x == line.v1.x && line.v0.y == line.v1.y) break;
        error_2 = 2 * error;
        if (error_2 >= delta_y) {
            if (line.v0.x == line.v1.x) break;
            error = error + delta_y;
            line.v0.x += slope_x;
        }
        if (error_2 <= delta_x) {
            if (line.v0.y == line.v1.y) break;
            error = error + delta_x;
            line.v0.y += slope_y;
        }
    }
}

void me_canvas_draw_rectangle(MECanvas *c, MERectangle rect, MEColor color, bool is_filled, MEColor fill_color) {
    // Obtain the center of the rectangle
    MEVector2 center = me_geometry_rectangle_center(rect);
    MEVector2 n_center = (MEVector2){-center.x, -center.y};
    // Get the points
    MEVector2 v0 = (MEVector2){rect.tl.x, rect.tl.y};
    MEVector2 v1 = (MEVector2){rect.tl.x + rect.w, rect.tl.y};
    MEVector2 v2 = (MEVector2){rect.tl.x + rect.w, rect.tl.y + rect.h};
    MEVector2 v3 = (MEVector2){rect.tl.x, rect.tl.y + rect.h};
    // Translate points towards (0, 0)
    v0 = me_geometry_vector_translate(v0, n_center);
    v1 = me_geometry_vector_translate(v1, n_center);
    v2 = me_geometry_vector_translate(v2, n_center);
    v3 = me_geometry_vector_translate(v3, n_center);
    // Rotate vectors
    v0 = me_geometry_vector_rotate(v0, rect.theta);
    v1 = me_geometry_vector_rotate(v1, rect.theta);
    v2 = me_geometry_vector_rotate(v2, rect.theta);
    v3 = me_geometry_vector_rotate(v3, rect.theta);
    // Translate back to the original center
    v0 = me_geometry_vector_translate(v0, center);
    v1 = me_geometry_vector_translate(v1, center);
    v2 = me_geometry_vector_translate(v2, center);
    v3 = me_geometry_vector_translate(v3, center);
    // Paint after translating back to the real center
    me_canvas_draw_line(c, (MELine){v0, v1}, color);
    me_canvas_draw_line(c, (MELine){v1, v2}, color);
    me_canvas_draw_line(c, (MELine){v2, v3}, color);
    me_canvas_draw_line(c, (MELine){v3, v0}, color);
    // Fill
    if (is_filled) {
        int min_x = me_math_min_int(4, v0.x, v1.x, v2.x, v3.x);
        int min_y = me_math_min_int(4, v0.y, v1.y, v2.y, v3.y);
        int max_x = me_math_max_int(4, v0.x, v1.x, v2.x, v3.x);
        int max_y = me_math_max_int(4, v0.y, v1.y, v2.y, v3.y);
        for (int current_x = min_x; current_x <= max_x; current_x++) {
            for (int current_y = min_y; current_y <= max_y; current_y++) {
                if (me_geometry_point_in_rectangle(v0, v1, v2, v3, (MEVector2){current_x, current_y})) {
                    me_canvas_set(c, (MEVector2){current_x, current_y}, fill_color);
                }
            }
        }
    }
}

/*
void me_canvas_draw_circle(MECanvas *c, MECircle circ, Uint32 color, bool is_filled, Uint32 fill_color) {
  int
}
 */

#endif//ME_CANVAS_H
