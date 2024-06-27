#include <stdio.h>

int main(void) {
    int* a;
    int b;
    a = &b;
    *a = 6;

    printf("Address of a: &a = %p\n", &a);
    printf("Value of a: a = %p\n", a);
    printf("Dereference of a: *a = %i\n", *a);

    return 0;
}
