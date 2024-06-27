
#include <stdio.h>
#include <string.h>
#include <stdbool.h>  // requires C99

#define MAX_STRING_SIZE 500  // the maximal string length the program can process
#define MAX_WORD_LENGTH 15   // the maximal word length for the histogram
#define HISTOGRAM_WIDTH 20   // maximum width of histogram bars in characters

// stringification; see https://stackoverflow.com/questions/40591312
#define STRINGIFY_IMPL(arg) #arg 
#define STRINGIFY(arg) STRINGIFY_IMPL(arg)  // Turns literal constant into string

// scanf format string; specify maximum buffer length to prevent buffer overflow
#define FORMAT_STRING "%" STRINGIFY(MAX_STRING_SIZE) "s"

int main(void) 
{
    char s[MAX_STRING_SIZE+1];  // string buffer for input; +1 for terminating NULL
    int counts[MAX_WORD_LENGTH] = {0};  // index i-1 corresponds to word length i
    int long_words = 0;  // count of words longer than MAX_WORD_LENGTH
    int total_count = 0; // count of all words, short and long

    // loop reads from standard input and counts string lengths
    while (scanf(FORMAT_STRING, s) > 0)
    {
        const int length = strlen(s);
        if (length == MAX_STRING_SIZE)
        {
            printf("Maximum word length of %d exceeded, aborting.\n", MAX_STRING_SIZE);
            return 1;
        }
        if (length > MAX_WORD_LENGTH)
            ++long_words;
        else
            ++counts[length-1];
        ++total_count;
    }

    // special case: empty input
    if (total_count == 0)
    {
        printf("There were no words.\n");
        return 0;
    }

    // print histogram
    char bar[HISTOGRAM_WIDTH];
    memset(bar, '|', HISTOGRAM_WIDTH);

    printf("word    occurrence     histogram\n");
    printf("length  count percent  plot     \n");
    for (int i = 0; i < MAX_WORD_LENGTH; ++i)
    {
        // for generality, width specifiers would need to be computed based on
        // the values of the preprocessor constants MAX_WORD_LENGTH. 
        // We do not do this here for clarity.
        const float percent = (100. * counts[i]) / total_count;
        const int num_bars = (percent/100) * HISTOGRAM_WIDTH;
        printf("%2d   %6d %6.2f%%    %.*s\n",
            i+1, 
            counts[i], 
            percent, 
            num_bars, 
            bar
        );
    }
    
    const bool singular_lw = long_words == 1 ? true : false;
    printf("There %s %d word%s of length >= %d.\n", 
        singular_lw ? "is" : "are", 
        long_words,
        singular_lw ? "" : "s", 
        MAX_WORD_LENGTH+1
    );
    const bool singular_tc = total_count == 1 ? true : false;
    printf("There %s %d word%s in total.\n", 
        singular_tc ? "is" : "are", 
        total_count,
        singular_tc ? "" : "s"
    );

    return 0;
}
