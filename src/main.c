#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4

typedef struct {
    char pair[3];
} pair;

typedef struct {
    unsigned short value;
} token;

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Vector;

void init_vector(Vector* vec) 
{
    vec->data = malloc(INITIAL_CAPACITY * sizeof(int));
    if (vec->data == NULL) {
        perror("Failed to allocate memory for vector");
        exit(EXIT_FAILURE);
    }
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
}

void append_vector(Vector* vec, token element) 
{
    if (vec->size == vec->capacity) 
    {
        size_t new_capacity = vec->capacity * 2;
        int* new_data = realloc(vec->data, new_capacity * sizeof(int));
        if (new_data == NULL) 
        {
            perror("Failed to reallocate memory for vector");
            exit(EXIT_FAILURE);
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    vec->data[vec->size] = element.value;
    vec->size++;
}

void free_vector(Vector* vec) 
{
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

token tokenize_pair(pair Pair)
{
    token T;

    T.value =
        ((unsigned short)(unsigned char)Pair.pair[0] << 8) |
         (unsigned short)(unsigned char)Pair.pair[1];

    return T;
}

int main(void)
{
    const char str[] = "The lazy fox jumps over the lazy dog";
    size_t str_size = sizeof(str) - 1;


    Vector tokens;
    init_vector(&tokens);

    for (size_t i = 0; i + 1 < str_size; i++)
    {
        pair Pair;

        Pair.pair[0] = str[i];
        Pair.pair[1] = str[i + 1];
        Pair.pair[2] = '\0';

        token T = tokenize_pair(Pair);
        append_vector(&tokens, T);

        printf("%s = %d\n", Pair.pair, T.value);
    }


    return 0;
}


