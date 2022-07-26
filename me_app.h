#ifndef ME_APP_H
#define ME_APP_H

#include <SDL.h>

#include "me_constants.h"
#include "me_scene.h"
#include "me_scene_manager.h"
#include "me_canvas.h"

typedef struct me_app {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    MECanvas *canvas;
    MESceneManager *scene_manager;
    MESceneIdx next_scene;
    long int frame;
} MEApp;

// Initializes the app object
MERet me_app_init(MEApp **app, const char *window_title) {
    MERet current_error;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return ME_ERROR_SDL_INIT;
    }
    *app = (MEApp *) calloc(1, sizeof(MEApp));
    (*app)->window = SDL_CreateWindow(
            window_title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            ME_WINDOW_WIDTH,
            ME_WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if ((*app)->window == NULL) {
        current_error = ME_ERROR_WINDOW_INIT;
        goto window_error;
    }
    (*app)->renderer = SDL_CreateRenderer((*app)->window, -1, SDL_RENDERER_ACCELERATED);
    if ((*app)->renderer == NULL) {
        current_error = ME_ERROR_RENDERER_INIT;
        goto error_renderer;
    }
    (*app)->texture = SDL_CreateTexture(
            (*app)->renderer,
            SDL_PIXELFORMAT_RGB888,
            SDL_TEXTUREACCESS_STATIC,
            ME_WINDOW_WIDTH,
            ME_WINDOW_HEIGHT);
    if ((*app)->texture == NULL) {
        current_error = ME_ERROR_TEXTURE_INIT;
        goto error_texture;
    }
    MERet ret_canvas = me_canvas_init(&((*app)->canvas), ME_WINDOW_WIDTH, ME_WINDOW_HEIGHT);
    if (ret_canvas != ME_OK) {
        current_error = ME_ERROR_CANVAS_INIT;
        goto error_canvas;
    }
    MERet ret_scene_manager = me_scene_manager_init(&(*app)->scene_manager);
    if (ret_scene_manager != ME_OK) {
        current_error = ME_ERROR_SCENE_MANAGER_INIT;
        goto error_scene_manager;
    }
    (*app)->next_scene = 0;
    (*app)->frame = 0;
    return ME_OK;
    // Error handling
    error_scene_manager:
    me_canvas_destroy(&(*app)->canvas);
    error_canvas:
    SDL_DestroyTexture((*app)->texture);
    error_texture:
    SDL_DestroyRenderer((*app)->renderer);
    error_renderer:
    SDL_DestroyWindow((*app)->window);
    window_error:
    SDL_Quit();
    free((*app));
    return current_error;
}

MERet me_app_destroy(MEApp **app) {
    me_scene_manager_destroy(&(*app)->scene_manager);
    me_canvas_destroy(&((*app)->canvas));
    SDL_DestroyTexture((*app)->texture);
    SDL_DestroyRenderer((*app)->renderer);
    SDL_DestroyWindow((*app)->window);
    SDL_Quit();
    free(*app);
    return ME_OK;
};

void me_app_paint(MEApp *app) {
    SDL_UpdateTexture(app->texture, NULL, app->canvas->pixels, ME_WINDOW_WIDTH * sizeof(Uint32));
    SDL_RenderClear(app->renderer);
    SDL_RenderCopy(app->renderer, app->texture, NULL, NULL);
    SDL_RenderPresent(app->renderer);
}

void me_app_scene_add(MEApp *app, MEScene *scene) {
    me_object_bag_add(&(app->scene_manager->scenes), scene);
}

void me_app_run(MEApp *app) {
    int tick_next = 0;
    SDL_Event event;

#ifdef MEDEBUG
    Uint32 old_tick = 0;
#endif

    app->next_scene = 0;

    while (1) {

        // FRAME LIMITING
        Uint32 tick = SDL_GetTicks();
        if (tick < tick_next) {
            SDL_Delay(tick_next - tick);
        }
        tick_next = tick + (Uint32) (1000 / ME_FPS);

        MEScene *current_scene = NULL;

        if (me_scene_manager_length(app->scene_manager) > 0) {
            current_scene = me_scene_manager_get_current_scene(app->scene_manager);
            if (current_scene != NULL) {
                current_scene->me_scene_update(current_scene, app->frame);
                current_scene->me_scene_paint(current_scene, &(app->canvas));
            }
        }

        me_app_paint(app);
        app->frame++;

        while (SDL_PollEvent(&event) != 0) {
            // EVENT HANDLING
            // Scene
            if (current_scene != NULL) {
                MESceneEventReturn ret = current_scene->me_scene_event_process(
                        current_scene,
                        event,
                        &(app->next_scene));
                me_scene_manager_set_current_scene(&(app->scene_manager), app->next_scene);
                if (ret == ME_SCENE_RETURN_QUIT) {
                    me_app_destroy(&app);
                    return;
                }
            }
            // Global, overrules scene (ex. SDL_QUIT)
            switch (event.type) {
                case SDL_QUIT:
                    me_app_destroy(&app);
                    return;
            }
        }

#ifdef MEDEBUG
        old_tick = SDL_GetTicks();
        printf("Frame took %d ticks\n", old_tick - tick);
#endif

    }
}

#endif //ME_APP_H
