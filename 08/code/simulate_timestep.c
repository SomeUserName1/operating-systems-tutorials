void simulate_timestep(char* world) {
    // add one new snow flake 
    int pos = rand() / ((RAND_MAX + 1u) / NCOLS);
    world[pos] = SNOWFLAKE;

    // float down snowflakes
    for(int row = NROWS - 2; row >= 0; --row) {
        for(int col = 0; col < NCOLS; ++col) {
            if (world[row * NCOLS + col] == SNOWFLAKE 
              && world[(row + 1) * NCOLS + col] == ' ') {
                world[row * NCOLS + col] = ' ';
                world[(row + 1) * NCOLS + col] = SNOWFLAKE;
            } 
        }
    }
}
