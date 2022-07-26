#ifndef ME_GEOMETRY_H
#define ME_GEOMETRY_H

#include <SDL.h>
#include <stdbool.h>

#define ADD_ROUND(n1, n2) (int) round((n1) + (n2))
#define SUB_ROUND(n1, n2) (int) round((n1) - (n2))

/*
 * (x, y) -> vector
 */
typedef struct me_vector {
    int x;
    int y;
} MEVector2;

/*
 * v0(x0, y0) -> starting point
 * v1(x1, y1) -> ending point
 */
typedef struct me_line {
    MEVector2 v0;
    MEVector2 v1;
} MELine;

/*
 * tl(x, y) -> top left corner
 * w -> width
 * h -> height
 * theta -> rotation (in radians)
 */
typedef struct me_rectangle {
    MEVector2 tl;
    int w;
    int h;
    double theta;
} MERectangle;

/*
 * Rotates a vector around (0,0)
 */
MEVector2 me_geometry_vector_rotate(MEVector2 v, double theta) {
    return (MEVector2){
            SUB_ROUND(v.x * (double) cos(theta), v.y * (double) sin(theta)),
            ADD_ROUND(v.x * (double) sin(theta), v.y * (double) cos(theta))};
}

/*
 * Translates a vector by a measure of another one
 */
MEVector2 me_geometry_vector_translate(MEVector2 v, MEVector2 t) {
    return (MEVector2){
            v.x + t.x,
            v.y + t.y};
}

/*
 * Calculates the magnitude of a vector
 */
double me_geometry_vector_magnitude(MEVector2 v) {
    return sqrt((v.x * v.x) + (v.y * v.y));
}

/*
 * Calculates the dot product of two vectors
 */
double me_geometry_vector_dot(MEVector2 v1, MEVector2 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y);
}

/*
 * Tells if the point is to the left of a line. The points
 * on MELine should be in a clockwise direction.
 */
bool me_geometry_point_left_line(MEVector2 v, MELine l) {
    return ((l.v1.x - l.v0.x) * (v.y - l.v0.y) - (v.x - l.v0.x) * (l.v1.y - l.v0.y)) > 0;
};

/*
 * Tells if a point is inside a rectangle if it is to
 * the left of all the boundary lines in clockwise order
 */
bool me_geometry_point_in_rectangle(MEVector2 x0, MEVector2 x1, MEVector2 x2, MEVector2 x3, MEVector2 p) {
    return (me_geometry_point_left_line(p, (MELine){x0, x1}) &&
            me_geometry_point_left_line(p, (MELine){x1, x2}) &&
            me_geometry_point_left_line(p, (MELine){x2, x3}) &&
            me_geometry_point_left_line(p, (MELine){x3, x0}));
}

/*
 * Calculates the center of a rectangle
 */
MEVector2 me_geometry_rectangle_center(MERectangle r) {
    return (MEVector2){
            ADD_ROUND(r.tl.x, r.w / 2.0),
            ADD_ROUND(r.tl.y, r.h / 2.0)};
}

#endif// ME_GEOMETRY_H
