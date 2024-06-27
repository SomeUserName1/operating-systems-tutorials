void print_frame(const char* world) {
    // ANSI sequence clears screen and repositions cursor
    printf("\033[2J\033[1;1H");  

    // print rows
    for(int row = 0; row < NROWS; ++row)
        printf("%.*s\n", NCOLS, world + row * NCOLS);
    
    printf("\nPress ctrl+c to abort...");
    fflush(stdout);  // flush to print last line
}
