#ifndef CMPLE_SRC_STRUCTS_DARRRAY_H
#define CMPLE_SRC_STRUCTS_DARRRAY_H


#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"


/* ------------------------------ Types ------------------------------ */

typedef struct {
    void* data;
    size_t size;
    size_t elementSize;
} DArray;

typedef Result (*da_WalkCallback)(void* element, void* context);



/* ----------------------------------- API ---------------------------------- */

DArray da_new(size_t elementSize, size_t size);

void da_resize(DArray* da, size_t newSize);

void da_walk(DArray* da, da_WalkCallback callback, void* context);

void da_clear(DArray* da);

bool da_isEmpty(DArray* da);



#endif // CMPLE_SRC_STRUCTS_DARRRAY_H
