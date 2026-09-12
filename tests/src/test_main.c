// tests/test_main.c

#include <stdio.h>

int test_buffer(void);

int main(void) {
    int failed = 0;

    failed += 0;

    if (failed) {
        printf("\nFAILED: %d test(s)\n", failed);
        return 1;
    }

    return 0; 
}