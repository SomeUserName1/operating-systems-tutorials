
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define NCOLS 79
#define NROWS 25
#define SNOWFLAKE '*'

/*
 * Prints one frame of the animation.
 */

void print_frame(char const * world)
{
    // ANSI sequence clears screen and repositions cursor
    printf("\033[2J\033[1;1H");  

    // print rows
    for(int row = 0; row < NROWS; ++row)
        printf("%.*s\n", NCOLS, world + row*NCOLS);
    
    printf("\nPress ctrl+c to abort...");
    fflush(stdout);  // flush to print last line
}

/* 
 * Computes next frame of the animation.
 */

void simulate_timestep(char * world)
{
    // add one new snow flake 
    int pos = rand()/((RAND_MAX + 1u)/NCOLS);
    world[pos] = SNOWFLAKE;

    // float down snowflakes
    for(int row = NROWS-2; row >= 0; --row)
        for(int col = 0; col < NCOLS; ++col)
        if (world[row*NCOLS + col] == SNOWFLAKE
            && world[(row+1)*NCOLS + col] == ' ')
        {
            world[row*NCOLS + col] = ' ';
            world[(row+1)*NCOLS + col] = SNOWFLAKE;
        }
}

/*
 * Simulate and print animation frames.
 *
 * Runs until user signals interrupt.
 */

void run_simulation()
{
    char world[NROWS*NCOLS];
    memset(world, ' ', NROWS*NCOLS);

    while (1)
    {
        print_frame(world);
        simulate_timestep(world);
        usleep(0.35 * 1000000);
    }
}

int main(void)
{
    srand(time(NULL)); // seed PRNG with current time
    run_simulation();

    return (0);
}
