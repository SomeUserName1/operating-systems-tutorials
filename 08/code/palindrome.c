int is_palindrome(char const* s) {
    char const* p = s + strlen(s);
    
    while (s < p) {
        if (*s++ != *(--p)) {
            return 0;
        }
    }
    
    return 1;
}
