void string_reverse_inplace(char* str) {
    char *end = str;
    char temp;

    for (; *end != '\0'; ++end) ; 
    for (; str < --end; ++str) {
        temp = *str;
        *str = *end;
        *end = temp;
    }
}
