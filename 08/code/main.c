#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define NCOLS 79
#define NROWS 25
#define SNOWFLAKE '*'

void run_simulation() {
    char world[NROWS * NCOLS];
    memset(world, ' ', NROWS * NCOLS);

    while (1) {
        print_frame(world);
        simulate_timestep(world);
        usleep(0.35 * 1000000);
    }
}

int main(void) {
    srand(time(NULL)); // seed PRNG with current time
    run_simulation();

    return 0;
}

