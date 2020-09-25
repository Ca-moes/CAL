/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)
{
    if ( n > 1){
        return n * factorialRecurs(n-1);
    } else {
        return 1;
    }
}

int factorialDinam(int n)
{
    int sum = 1;
    for (int i = 2; i <= n ; ++i) {
        sum = sum * i;
    }
    return sum;
}
