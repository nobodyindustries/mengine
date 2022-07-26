#ifndef ME_SCENE_MANAGER_H
#define ME_SCENE_MANAGER_H

#include "me_object_bag.h"

typedef struct me_scene_manager {
    MEObjectBag *scenes;
    MESceneIdx currentScene;
} MESceneManager;

MERet me_scene_manager_init(MESceneManager **sm) {
    *sm = calloc(1, sizeof(MESceneManager));
    (*sm)->currentScene = 0; // Always start at scene 0
    MERet ret;
    ret = me_object_bag_init(&((*sm)->scenes));
    if (ret != ME_OK) {
        free(*sm);
        return ME_ERROR_SCENE_MANAGER_INIT;
    }
    return ME_OK;
}

MEScene *me_scene_manager_get_current_scene(MESceneManager *sm) {
    return (MEScene *) me_object_bag_get(sm->scenes, sm->currentScene);
}

MERet me_scene_manager_set_current_scene(MESceneManager **sm, MESceneIdx newScene) {
    (*sm)->currentScene = newScene;
    return ME_OK;
}

void me_scene_manager_destroy(MESceneManager **sm) {
    int idx;
    MEObjectBag *scs = (*sm)->scenes;
    for (idx = 0; idx < scs->length; idx++) {
        MEScene *scene = me_object_bag_get(scs, idx);
        me_object_bag_remove(&scs, idx, (MEObjectDestroyFunction) scene->me_scene_destroy);
        free(scene);
    }
    me_object_bag_destroy(&scs, NULL);
    free(*sm);
}

unsigned int me_scene_manager_length(MESceneManager *sm) {
    return sm->scenes->length;
}


#endif //ME_SCENE_MANAGER_H