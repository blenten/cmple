#include <stdio.h>
#include <stdlib.h>


#include "entity.h"



/* ------------------------------ Entity Result ----------------------------- */

typedef struct {
    Result status;
    EntityID id;
} e_Result;


e_Result e_res_ok(EntityID id)
{
    return (e_Result) {OK, id};
}


e_Result e_res_error(Result error)
{
    return (e_Result) {error, NULL_ENTITY};
}


EntityID e_res_unpack(e_Result res)
{
    switch (res.status)
    {
        case OK:
            return res.id;

        case ERR_OVERFLOW:
            printf("Entity overflow error.\n");
            break;
        case ERR_EMPTY:
            printf("Entity list empty error.\n");
            break;
        case ERR_NO_SUCH_ENTITY:
            printf("Entity does not exist error.\n");
            break;
        default:
            printf("Unexpected error: ENTITY.\n");
    }
    exit(-1);
}



/* ---------------------------------- Entity Func ---------------------------------- */

static EntityID eid_generate()
{
    static EntityID last = 0;
    return last++;
}


EntityList elist_new()
{
    EntityList result;
    result.count = 0;
    Entity defaultEntity = {
        .id = NULL_ENTITY, 
        .config = NONE
    };
    for (size_t i = 0; i < MAX_ENTITY_NUMBER; i++)
    {
        result.data[i] = defaultEntity;
    }
    return result;
}


e_Result _elist_newEntity(EntityList* elist, EntityConfiguration config)
{
    if (elist->count >= MAX_ENTITY_NUMBER)
    {
        return e_res_error(ERR_OVERFLOW);
    }
    EntityID id = eid_generate();
    elist->data[elist->count++] = (Entity) {.id = id, .config = config};
    return e_res_ok(id);
}

static void _elist_moveEntityData(EntityList* elist, size_t src, size_t dest)
{
    if (src == dest) return;
    elist->data[dest] = elist->data[src];
}

e_Result _elist_delete(EntityList* elist, EntityID id)
{
    if (elist->count == 0)
    {
        return e_res_error(ERR_EMPTY);   
    }
    size_t lastEntityPos = elist->count - 1;
    if (id == elist->data[lastEntityPos].id)
    {
        elist->count--;
        return e_res_ok(id);
    }
    // 
    for (size_t i = 0; i < lastEntityPos; i++)
    {
        if (elist->data[i].id == id)
        {
            _elist_moveEntityData(elist, lastEntityPos, i);
            elist->count--;
            return e_res_ok(id);
        }
        
    }
    return e_res_error(ERR_NO_SUCH_ENTITY); 
}

//  TODO: replace with DArray
EIDArray elist_query(EntityList* elist, EntityConfiguration config)
{
    EIDArray result;
    result.data = malloc(sizeof(EntityID) * elist->count);
    result.count = 0;

    for (size_t i = 0; i < elist->count; i++)
    {
        if ((config & elist->data[i].config) == config)
        {
            result.data[result.count++] = elist->data[i].id;
        }       
    }
    if (result.count == 0)
    {
        free(result.data);
        result.data = NULL;
    } else {
        result.data = realloc(result.data, sizeof(EntityID) * result.count);
    }
    return result;
}


/* ----------------------------- Entity Func API ---------------------------- */

EntityID elist_newEntity(EntityList* elist, EntityConfiguration config)
{
    return e_res_unpack(_elist_newEntity(elist, config));
}


EntityID elist_delete(EntityList* elist, EntityID id)
{
    return e_res_unpack(_elist_delete(elist, id));
}