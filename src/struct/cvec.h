#ifndef CMPLE_STRUCTS_CVEC_H
#define CMPLE_STRUCTS_CVEC_H


#include "entity.h"


typedef struct {
    void* data;
    size_t datumSize;
    int addressMap[MAX_ENTITY_NUMBER];
    EntityID idMap[MAX_ENTITY_NUMBER];
    size_t count;
} CompactVector;


CompactVector cvec_new(size_t datumSize);

int cvec_registerEntity(CompactVector* cvec, EntityID id);

int cvec_deleteEntity(CompactVector* cvec, EntityID id);

void* cvec_getDatumHandle(CompactVector* cvec, EntityID id);

void cvec_clear(CompactVector* cvec);


#endif // CMPLE_STRUCTS_CVEC_H