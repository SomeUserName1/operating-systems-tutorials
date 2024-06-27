#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 32
static int back = EOF;

static int getch(void) {
    if (back != EOF) {
        int r = back;
        back = EOF;
        return r;
    }
    return getchar();
}
static void ungetch(int c) {
    if (back != EOF) {
        printf("%s\n", "ungetch: can obly push back one char");
        exit(-1);
    }
    back = c;
}

int gettoken(double *num) {
    int i;
    int c;
    char buf[MAXOP + 1];

    while (isblank(c = getch())) {
        ;
    }

    if (!isdigit(c) && c != '.') {
        return c;
    }
    
    buf[0] = (char) c;
    i = 1;
    while(isdigit(c = getch())) {
        if (1 >= MAXOP) {
            printf("%s", "gettoken: number too long!\n");
            return EOF;
        }
        buf[i++] = (char) c;
    }
    
    if (c == '.') {
        buf[i++] = (char) c;
        while(isdigit(c = getch())) {
            if (1 >= MAXOP) {
                printf("%s", "gettoken: number too long!\n");
                return EOF;
            }
            buf[i++] = (char) c;
        }
    }
    buf[i] = '\0';

    if (c != EOF) {
        ungetch(c);
    }
    *num = atof(buf);
    return NUMBER;
}

