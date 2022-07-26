#ifndef ME_SCENE_H
#define ME_SCENE_H

#include "me_canvas.h"
#include <SDL.h>

typedef unsigned int MESceneIdx;

typedef enum me_scene_event_return {
    ME_SCENE_RETURN_OK = 0,
    ME_SCENE_RETURN_QUIT = 1,
} MESceneEventReturn;

typedef struct me_scene {

    /*
     * Updates the internal state of the scene once per frame
     */
    void (*me_scene_update)(struct me_scene *scene, long int frame);

    /*
     * Draws the scene on the canvas
     */
    void (*me_scene_paint)(struct me_scene *scene, MECanvas **canvas);

    /*
     * Returns whether to continue or quit, nextScene contains the idx
     * of the next scene to execute when the function ends.
     */
    MESceneEventReturn (*me_scene_event_process)(struct me_scene *scene, SDL_Event event, MESceneIdx *nextScene);

    /*
     * State (can be anything, a MEObjectBag, a complex struct or a simple int)
     */
    void *state;

    /*
     * Destroys the scene, freeing all the associated memory, including
     * state.
     */
    void (*me_scene_destroy)(struct me_scene *scene);

} MEScene;

// Allocates a new scene
MERet me_scene_get(MEScene **scene) {
    *scene = (MEScene *) calloc(1, sizeof(MEScene));
    if (*scene == NULL) {
        return ME_ERROR_SCENE_CREATE;
    }
    return ME_OK;
}

#endif//ME_SCENE_H
