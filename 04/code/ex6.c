#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

int main(int argc, char* argv[]) { 
    if (argc != 2) {
        printf("Please specify only one string to count the vowels of.");
        return -1;
    }
    
    unsigned int vowel = 0;
    size_t len = strlen(argv[1]);

    for(size_t i = 0; i < len; i++) {
        switch(argv[1][i]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                vowel++;
                break;
            default:
                break;
        }
    }
    
    printf("Total number of vowels = %i\n", vowel);

    return 0;
}
