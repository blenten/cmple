#ifndef CMPLE_UTILS_H_
#define CMPLE_UTILS_H_



typedef enum {
    OK,
    ERR_EMPTY,
    ERR_OVERFLOW,
    ERR_NO_SUCH_ENTITY,
    ERR_ALLOCATION_FAIL
} Result;



void err_print(Result error);



#endif // CMPLE_UTILS_H_