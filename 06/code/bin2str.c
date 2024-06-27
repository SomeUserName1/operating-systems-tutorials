void binary_to_string(unsigned long int b, unsigned char k, char *s) {
    unsigned long shifted_to_place;
    for (unsigned char i = 0; i < k; ++i) {
        shifted_to_place = (b >> (k - 1 - i));
        s[i] = (shifted_to_place & 1) == 1 ? '1' : '0';
    }
    printf("%.*s\n", k, s);
}
 
