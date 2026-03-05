#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE(array) sizeof(array) / sizeof(array[0])

#define PRINTFN(...) printf(__VA_ARGS__); printf("\n")

#define PRINT_ARRAY(array, size, element_format)                          \
    do {                                                                  \
        for (uint32_t array##_ith = 0; array##_ith < size; array##_ith++) \
        {                                                                 \
            printf(element_format, array[array##_ith]);                   \
        }                                                                 \
        printf("\n");                                                     \
    } while (0)

#define A_VALUE(array) array[0]
#define B_VALUE(array) array[1]

#define TESTING_MODE 0

uint32_t test_values[][2] = {
    {0, 0}, 
    {0, 1}, 
    {1, 0}, 
    {0, UINT32_MAX}, 
    {UINT32_MAX, 0},
    {INT32_MIN, 0},
    {0, INT32_MIN},
    {INT32_MAX, 0},
    {0, INT32_MAX},
    {INT32_MIN, INT32_MAX},
    {INT32_MAX, INT32_MIN},
    {INT32_MIN, INT32_MIN / 2},
    {INT32_MIN / 2, 0},
    {0, INT32_MAX / 2},
    {INT32_MAX / 2, INT32_MAX}
    };

void swap_values(uint32_t * a, uint32_t * b)
{
    *a = *b - *a;
    *b = *b - (*a); // [b - (b - a)] = a
    *a = *a + *b;   // [(b - a) + a] = b
}

int main(int argc, char const *argv[])
{
    uint32_t a_before, b_before;
    uint32_t errors_found = 0;
    for (uint32_t i = 0; i < ARRAY_SIZE(test_values); i++)
    {
        a_before = A_VALUE(test_values[i]);
        b_before = B_VALUE(test_values[i]);

        swap_values(&A_VALUE(test_values[i]), &B_VALUE(test_values[i]));

        #if (TESTING_MODE)
        if ((a_before != B_VALUE(test_values[i])) || (b_before != A_VALUE(test_values[i])))
        {
        #endif
            PRINTFN("a before = %d", a_before);
            PRINTFN("b before = %d", b_before);
            PRINTFN("a new = %d", A_VALUE(test_values[i]));
            PRINTFN("b new = %d", B_VALUE(test_values[i]));
        #if (TESTING_MODE)
        }
        #endif
        PRINTFN("---");
    }
    PRINTFN("%ld", ARRAY_SIZE(test_values));
    PRINTFN("%d errors found", errors_found);
    return 0;
}
