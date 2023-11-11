#include "utils.h"

#include <stdio.h>



void err_print(Result error)
{
    switch (error)
    {
    case OK:
        return;
    case ERR_OVERFLOW:
        printf("Overflow error.");
        break;
    case ERR_EMPTY:
        printf("Empty error.");
        break;
    case ERR_NO_SUCH_ENTITY:
        printf("Entity does not exist error.");
        break;
    case ERR_ALLOCATION_FAIL:
        printf("Allocation failed.");
        break;
    default:
        printf("Unknown error.");
    }    
}