#include <stdio.h>
#include <stdlib.h>


#include "darrray.h"



/* ------------------------------ DArray Result ----------------------------- */

typedef struct {
    Result status;
    DArray result;
} da_Result;


da_Result da_res_ok(DArray result)
{
    return (da_Result) {OK, result};
}


da_Result da_res_error(Result error)
{
    return (da_Result) {error};
}


void da_err(Result err)
{
    printf("DARRAY: ");
    err_print(err);
    printf("\n");
    exit(-1);
}



/* ---------------------------------- Func ---------------------------------- */

da_Result _da_new(size_t elementSize, size_t size)
{
    DArray res = {
        .size = size,
        .elementSize = elementSize,
        .data = malloc(elementSize * size)
    };
    if (!res.data) return da_res_error(ERR_ALLOCATION_FAIL);
    return da_res_ok(res);
}


Result _da_resize(DArray* da, size_t newSize)
{
    da->data = realloc(da->data, newSize * da->elementSize);
    if(!da->data) return ERR_ALLOCATION_FAIL;
    da->size = newSize;
    return OK;
}


Result _da_walk(DArray* da, da_WalkCallback callback, void* context)
{
    size_t size = da->size;
    size_t elementSize = da->elementSize;
    void* data = da->data;

    Result res = OK;
    size_t i = 0;
    while (res == OK && i < size)
    {
        res = callback(data + (elementSize * i), context);
        i++;
    }
    return res;
}


void da_clear(DArray* da)
{
    free(da->data);
    da->data = NULL;
    da->size = 0;
    da->elementSize = 0;
}


bool da_isEmpty(DArray* da)
{
    return da->size <= 0;
}



/* ----------------------------------- API ---------------------------------- */

DArray da_new(size_t elementSize, size_t size)
{
    da_Result res = _da_new(elementSize, size);
    if(res.status == OK)
    {
        return res.result;
    }
    da_err(res.status);
    exit(-1);
}


void da_resize(DArray* da, size_t newSize)
{
    Result res = _da_resize(da, newSize);
    if (res == OK) return;
    da_err(res);
}


void da_walk(DArray* da, da_WalkCallback callback, void* context)
{
    Result res = _da_walk(da, callback, context);
    if (res == OK) return;
    da_err(res);
}
