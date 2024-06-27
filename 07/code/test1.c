#include <stdio.h>

//#define ARRP

int main(void) {
    /* c is continuous in memory */
    int c[][2] = {{1, 2}, {3, 4}, {5, 6}};
    /* pointers continuous, the arrays of length 2 must not be continuous but of length 2 */
    int trd[3] = {7, 8, 9};
    int fst[3] = {1, 2, 3};
    int snd[3] = {4, 5, 6};
    int *d[3] = {fst, snd, trd};
    /* Pointers continuous but sub pointers not, variable length elements */
    int** e;

    printf("======== int[][2] =======\n");
    printf("sizeof(&c), &c: %lu, %p\n", sizeof(&c), &c);
    printf("sizeof(c), c: %lu, %p\n", sizeof(c), c);
    printf("sizeof(*c), *c: %lu, %p\n", sizeof(*c), *c);
    printf("sizeof(**c), **c: %lu, %d\n", sizeof(**c), **c);
    
    printf("======== int* [3] =======\n");
    printf("sizeof(&d), &d: %lu, %p\n", sizeof(&d), &d);
    printf("sizeof(d), d: %lu, %p\n", sizeof(d), d);
    printf("sizeof(*d), *d: %lu, %p\n", sizeof(*d), *d);
    printf("sizeof(**d), **d: %lu, %d\n", sizeof(**d), **d);
    
#ifdef ARRP
    e = d; /* Warning incompatible pointer types: */ 
    /* int** e may point to arrays of size other than 3 */
    
    printf("======== int** with assignment to int*[] =======\n");
    printf("sizeof(&e), &e: %lu, %p\n", sizeof(&e), &e);
    printf("sizeof(e), e: %lu, %p\n", sizeof(e), e);
    printf("sizeof(*e), *e: %lu, %p\n", sizeof(*e), *e);
    printf("sizeof(**e), **e: %lu, %d\n", sizeof(*e[0]), *e[0]);
    
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j)
            printf("d[%lu][%lu]: %d\n", i, j, *(*(d + i) + j));
    }
    
    *(e + 1) = *(c + 2);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j)
            printf("d[%lu][%lu]: %d\n", i, j, *(*(d + i) + j));
    }
#else
    e = c; /* Warning: incompatible pointer types: */
    /* e does not preserve c's structure constraint */
        
    printf("======== int** with assignment to int[][] =======\n");
    printf("sizeof(&e), &e: %lu, %p\n", sizeof(&e), &e);
    printf("sizeof(e), e: %lu, %p\n", sizeof(e), e);
    printf("sizeof(*e), *e: %lu, %d\n", sizeof(*e), *e);
    //printf("sizeof(**e), **e: %lu, %d\n", sizeof(e[0][0]), e[0][0]);
    
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 2; ++j)
            printf("c[%lu][%lu]: %d\n", i, j, *(*(c + i) + j));
    }

    /* c is continuous in memory */
    /* by asssigning to int** this constraint is dropped */
    *e = *(d + 1);
    /* *(d+1) points to subarray of length 3. */
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 2; ++j)
            printf("c[%lu][%lu]: %d\n", i, j, *(*(c + i) + j));
    }

#endif
    return 0;
}
