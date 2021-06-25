#include "core.h"

int add(int var1, int var2){
    return var1 + var2;
}

int sub(int var1, int var2){
    return var1 - var2;
}

int mul(int var1, int var2){
    return var1 * var2;
}

int divide(int var1, int var2){
    return var1/var2;
}

int (*fPtrArray[])(int, int) = { add, sub, mul , divide};
