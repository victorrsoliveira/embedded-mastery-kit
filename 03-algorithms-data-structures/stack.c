#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(array) sizeof(array) / sizeof(array[0])

#ifdef STACK_DEBUG_ON
#define STACK_DEBUG_PRINTFN(...) \
    printf(__VA_ARGS__);         \
    printf("\n")
#else
#define STACK_DEBUG_PRINTFN(...)
#endif

#define PRINT_ARRAY(array, size, element_format)                          \
    do                                                                    \
    {                                                                     \
        for (uint32_t array##_ith = 0; array##_ith < size; array##_ith++) \
        {                                                                 \
            printf(element_format, array[array##_ith]);                   \
        }                                                                 \
        printf("\n");                                                     \
    } while (0)

/**
 * @brief Stack of bytes.
 *
 */
typedef struct
{
    uint8_t *buffer;       // Buffer that stores the stack items (bytes)
    size_t   buffer_size;  // Size of the buffer
    size_t   length;       // Number of bytes currently in the stack.
} Stack_st;

// Note: length field is used to reference the top of the stack, by the
// following rule: If length > 0, then top = length - 1; Else, top = 0

/**
 * @brief Create a Stack object
 *
 * @param stack stack object to be initiliazed
 * @param buffer pointer to the buffer that stores the stack items (bytes)
 * @param buffer_size size of buffer
 * @return int8_t error code indicating failure -1 or success 0
 */
int8_t createStack(Stack_st *stack, uint8_t *buffer, size_t buffer_size)
{
    // Validate input
    if ((NULL == stack) || (NULL == buffer) || (0 == buffer_size))
    {
        return -1;
    }

    stack->buffer      = buffer;
    stack->buffer_size = buffer_size;
    stack->length      = 0;

    return 0;
}

/**
 * @brief Push byte to the stack
 *
 * @param stack stack object reference
 * @param byte value to be pushed to the stack
 * @return int8_t error code indicating failure negative number or success 0
 */
int8_t pushByteToStack(Stack_st *stack, uint8_t byte)
{
    size_t top     = 0;
    int8_t ret_val = 0;

    // Validate input
    if (NULL == stack)
    {
        return -1;
    }

    top = stack->length;

    if (stack->length < stack->buffer_size)
    {
        stack->buffer[top] = byte;
        stack->length++;
    }
    else
    {
        // Stack is full; return different error code
        ret_val = -2;
    }

    return ret_val;
}

/**
 * @brief Pop byte from stack
 *
 * @param stack stack object reference
 * @param byte pointer the to popped byte
 * @return int8_t error code indicating failure negative value or success 0
 */
int8_t popByteFromStack(Stack_st *stack, uint8_t *byte)
{
    size_t top;
    int8_t ret_val = 0;

    // Validate input
    if ((NULL == stack) || (NULL == byte))
    {
        return -1;
    }

    if (stack->length > 0)
    {
        top   = stack->length - 1;
        *byte = stack->buffer[top];
        stack->length--;
    }
    else
    {
        // Stack is empty
        ret_val = -2;
    }

    return ret_val;
}

static inline size_t getStackLength(Stack_st *stack)
{
    return stack->length;
}

int main(int argc, char const *argv[])
{
    Stack_st stack;
    uint8_t  buffer[10];
    uint8_t  byte;

    int8_t err_val;

    err_val = createStack(&stack, buffer, sizeof(buffer));

    assert(err_val == 0);

    err_val = pushByteToStack(&stack, 5);
    assert(err_val == 0);
    err_val = pushByteToStack(&stack, 3);
    assert(err_val == 0);
    err_val = pushByteToStack(&stack, 9);
    assert(err_val == 0);
    err_val = pushByteToStack(&stack, 0);
    assert(err_val == 0);
    err_val = pushByteToStack(&stack, 1);
    assert(err_val == 0);

    size_t current_stack_length = getStackLength(&stack);

    assert(getStackLength(&stack) == 5);
    printf("Stack length = %ld\n", getStackLength(&stack));

    for (size_t i = 0; i < current_stack_length; i++)
    {
        err_val = popByteFromStack(&stack, &byte);
        assert(err_val == 0);
        printf("Popped value = %d\n", byte);
    }

    assert(getStackLength(&stack) == 0);

    err_val = popByteFromStack(&stack, &byte);
    assert(err_val == -2);

    for (size_t i = 0; i < sizeof(buffer); i++)
    {
        err_val = pushByteToStack(&stack, i);
        assert(err_val == 0);
    }

    err_val = pushByteToStack(&stack, 10);
    assert(err_val == -2);

    current_stack_length = getStackLength(&stack);
    assert(current_stack_length == sizeof(buffer));

    for (size_t i = 0; i < current_stack_length; i++)
    {
        err_val = popByteFromStack(&stack, &byte);
        assert(err_val == 0);
        printf("Popped value = %d\n", byte);
    }

    return 0;
}
