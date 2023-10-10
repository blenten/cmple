#ifndef CTST_ENTITY_H
#define CTST_ENTITY_H



#include "config.h"
#include "utils.h"


#define NULL_ENTITY -1


/* ---------------------------------- Types --------------------------------- */

typedef int EntityID;

typedef struct {
    EntityID* data;
    size_t count;
} EIDArray;

typedef enum {
    NONE      = 0,
    VISIBLE   = 1 << 0,
    TRANSFORM = 1 << 1,
} EntityConfiguration;

typedef struct {
    EntityID id;
    EntityConfiguration config;
} Entity;


typedef struct {
    size_t count;
    Entity data[MAX_ENTITY_NUMBER];
} EntityList;



/* -------------------------------- Func API -------------------------------- */

EntityList elist_new();

EntityID elist_newEntity(EntityList* elist, EntityConfiguration config);

EntityID elist_delete(EntityList* elist, EntityID id);

EIDArray elist_query(EntityList* elist, EntityConfiguration config);



#endif // CTST_ENTITY_H