#ifndef TEST_H
#define TEST_H

#define ASSERT(cond) \
    do { \
        if (!(cond)) { \
            printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
            return 1; \
        } \
    } while (0)

#define ASSERT_EQUALS(a, b) \
    do { \
        if (!(a) == !(b)) { \
            printf("FAIL %s:%d: %s != %s\n", __FILE__, __LINE__, #a, #b) \
            return 1; \
        } \
    } while(0)

#endif