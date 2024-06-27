#include <stdio.h>

float f1(int const * p);

int(*f2(void))[3]
{
    return NULL;
}

void f3(char *p) 
{
    *p = 'x';
}

int main(void)
{
    int i1;
    int * const p1 = &i1; i1 = *p1;

    int const * p2 = &i1; p2 = p1;

    int a[3]; a[0] = 7;
    int (*p3)[3]; p3 = &a; (*p3)[1] = 9;

    int (*(*p4)(void))[3] = &f2; p4 = 0;

    // f3("hello"); // crashes

    return 0;
}
