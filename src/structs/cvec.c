#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cvec.h"



CompactVector cvec_new(size_t datumSize)
{
    CompactVector cvec;
    cvec.data       = malloc(datumSize * MAX_ENTITY_NUMBER);
    cvec.datumSize  = datumSize;
    cvec.count      = 0;

    for (size_t i = 0; i < MAX_ENTITY_NUMBER; i++)
    {
        cvec.addressMap[i] = NULL_ENTITY;
        cvec.idMap[i] = NULL_ENTITY;
    }
    return cvec;
}


int cvec_registerEntity(CompactVector* cvec, EntityID id)
{
    size_t address = cvec->count;
    if (address >= MAX_ENTITY_NUMBER)
    {
        return -1;
    }
    cvec->addressMap[id] = address;
    cvec->idMap[address] = id;
    cvec->count++;
    return 0;
}


int cvec_deleteEntity(CompactVector* cvec, EntityID id)
{
    size_t address = cvec->addressMap[id];
    if (address == NULL_ENTITY)
    {
        return -1;
    }
    cvec->addressMap[id] = NULL_ENTITY;
    cvec->count--;
    size_t count = cvec->count;
    if (count == 0)
    {
        cvec->idMap[address] = NULL_ENTITY;
        return 0;
    }
    size_t size = cvec->datumSize;
    memcpy(cvec->data + (address * size), cvec->data + (count * size), size);
    cvec->addressMap[cvec->idMap[count]] = address;
    cvec->idMap[address] = cvec->idMap[count];
    cvec->idMap[count] = NULL_ENTITY;
    return 0;
}


void* cvec_getDatumHandle(CompactVector* cvec, EntityID id)
{
    size_t address = cvec->addressMap[id];
    if (address == NULL_ENTITY)
    {
        return NULL;
    }
    return cvec->data + (address * cvec->datumSize);
}


void cvec_clear(CompactVector* cvec)
{
    free(cvec->data);
    cvec->data = NULL;
}
