#include <stdlib.h>
#include <string.h>
#include "me_constants.h"

#ifndef ME_OBJECT_BAG_H
#define ME_OBJECT_BAG_H

#define ME_OBJECT_BAG_DEFAULT_CAPACITY 10
#define ME_OBJECT_BAG_DEFAULT_INCREASE 5

typedef void (*MEObjectDestroyFunction)(void *object);

typedef struct {
    void **objects;
    unsigned int length;
    unsigned int capacity;
    unsigned int increase;
} MEObjectBag;


MERet me_object_bag_init(MEObjectBag **bag) {
    *bag = calloc(1, sizeof(MEObjectBag));
    if (*bag == NULL) {
        return ME_ERROR_OBJECT_BAG_INIT;
    }
    (*bag)->length = 0;
    (*bag)->capacity = ME_OBJECT_BAG_DEFAULT_CAPACITY;
    (*bag)->increase = ME_OBJECT_BAG_DEFAULT_INCREASE;
    (*bag)->objects = calloc((*bag)->capacity, sizeof(void *));
    if ((*bag)->objects == NULL) {
        free(bag);
        return ME_ERROR_OBJECT_BAG_INIT;
    }
    return ME_OK;
}

// If the bag holds different types of structs this will cause leaks.
// The user should remove all the elements one by one with the right function,
// and then call this passing NULL as the object destroy function. The object
// destroy function can be used if all elements have the same type.
void me_object_bag_destroy(MEObjectBag **bag, MEObjectDestroyFunction object_destroy) {
    int idx;
    if (object_destroy != NULL) {
        for (idx = 0; idx < (*bag)->length; idx++) {
            object_destroy((*bag)->objects[idx]);
        }
    }
    free((*bag)->objects);
    free(*bag);
}

void me_object_bag_expand(MEObjectBag **bag) {
    void **aux_array = (void **) calloc((*bag)->capacity + (*bag)->increase, sizeof(void *));
    memcpy(aux_array, (*bag)->objects, (*bag)->capacity * sizeof(void *));
    (*bag)->capacity = (*bag)->capacity + (*bag)->increase;
    free((*bag)->objects);
    (*bag)->objects = aux_array;
}

void me_object_bag_add(MEObjectBag **bag, void *object) {
    if ((*bag)->length == (*bag)->capacity - 1) {
        me_object_bag_expand(bag);
    }
    (*bag)->objects[(*bag)->length] = object;
    (*bag)->length = (*bag)->length + 1;
}

// In order to remove an object it makes no sense to use NULL as object_destroy function
void me_object_bag_remove(MEObjectBag **bag, int idx, MEObjectDestroyFunction object_destroy) {
    if(object_destroy != NULL)
      object_destroy((*bag)->objects[idx]);
    (*bag)->objects[idx] = NULL;
    int internal_idx;
    // Reposition all the rest of the objects in the bag
    for (internal_idx = idx + 1; internal_idx < (*bag)->length; internal_idx++) {
        (*bag)->objects[internal_idx - 1] = (*bag)->objects[internal_idx];
    }
    (*bag)->length = (*bag)->length - 1;
}

void *me_object_bag_get(MEObjectBag *bag, int idx) {
    if (idx >= bag->length) {
        return NULL;
    }
    return bag->objects[idx];
}

// Generic way of freeing pointer as a MEObjectDestroyFunction
// You only need to provide your own destructor if there is something
// to free inside.
void me_object_bag_pointer_destructor(void *p) {
    free(p);
}

#endif //ME_OBJECT_BAG_H
