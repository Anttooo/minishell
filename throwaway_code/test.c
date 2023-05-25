# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <strings.h>
# include <stdbool.h>

typedef struct s_vec
{
    void*   memory;
    size_t  elem_size;
    size_t  alloc_size;
    size_t  len;
}   t_vec;

void* ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t          i;
    unsigned char   *d;
    unsigned char   *s;

    d = (unsigned char *)dst;
    s = (unsigned char *)src;
    i = 0;
    if (d == NULL && s == NULL)
        return (d);
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (dst);
}

int vec_new(t_vec *dst, size_t init_len, size_t elem_size)
{
    if (!dst || elem_size == 0)
        return (-1);
    dst->alloc_size = init_len * elem_size;
    dst->elem_size = elem_size;
    dst->len = 0;
    if (init_len == 0)
        dst->memory = NULL;
    else
    {
        dst->memory = malloc(dst->alloc_size);
        if (!dst->memory)
            return (-1);
    }
    return (1);
}

int vec_free(t_vec *src)
{
    if (!src || src->alloc_size == 0)
        return (-1);
    free(src->memory);
    src->memory = NULL;
    src->alloc_size = 0;
    src->elem_size = 0;
    src->len = 0;
    return (1);
}

void* vec_get(t_vec *src, size_t index)
{
    unsigned char   *ptr;

    if (index >= src->len || !src || !src->memory)
        return (NULL);
    ptr = &((unsigned char *)src->memory)[src->elem_size * index];
    return (ptr);
}

int vec_resize(t_vec *src, size_t target_len)
{
    t_vec   dst;

    if (!src)
        return (-1);
    else if (!src->memory)
        return (vec_new(src, target_len, src->elem_size));
    else if (vec_new(&dst, target_len, src->elem_size) < 0)
        return (-1);
    ft_memcpy(dst.memory, src->memory, src->len * src->elem_size);
    dst.len = src->len;
    vec_free(src);
    *src = dst;
    return (1);
}

int vec_push(t_vec *dst, void *src)
{
    if (!dst || !src)
        return (-1);
    else if (!dst->memory)
    {
        if (vec_new(dst, 1, dst->elem_size) < 0)
            return (-1);
    }
    printf("vec_size before pushing %zu \n", dst->len);
    if (dst->elem_size * dst->len >= dst->alloc_size)
    {
        if (vec_resize(dst, dst->len * 2) < 0)
            return (-1);
    }
     printf("vec_size after pushing %zu \n", dst->len);
    ft_memcpy(((unsigned char*)dst->memory) + dst->elem_size * dst->len, src, dst->elem_size);
    dst->len++;
    return (1);
}

void setup_vectors(t_vec *token_vec, t_vec *type_vec) {
    vec_new(token_vec, 0, sizeof(char *));
    vec_new(type_vec, 0, sizeof(int));

    char *t1 = strdup("token1");
    int type1 = 1;
    vec_push(token_vec, &t1);
    vec_push(type_vec, &type1);

    char *t2 = strdup("token2");
    int type2 = 2;
    vec_push(token_vec, &t2);
    vec_push(type_vec, &type2);

    char *t3 = strdup("token3");
    int type3 = 3;
    vec_push(token_vec, &t3);
    vec_push(type_vec, &type3);

    char *t4 = strdup("This is a much longer token that we will test whether the vec get supports it.");
    int type4 = 4;
    vec_push(token_vec, &t4);
    vec_push(type_vec, &type4);
}

void print_token_and_type(t_vec *token_vec, t_vec *type_vec, size_t index) {
    char *token = *(char **)vec_get(token_vec, index);
    int *type = vec_get(type_vec, index);
    if (token != NULL) {
        printf("Token: %s, Type: %d\n", token, *type);
    }
}

void deallocate_vectors(t_vec *token_vec, t_vec *type_vec) {
    for (size_t i = 0; i < token_vec->len; i++) {
        char *token = *(char **)vec_get(token_vec, i);
        free(token);
    }
    vec_free(token_vec);
    vec_free(type_vec);
}

int main(void) {
    t_vec token_vec;
    t_vec type_vec;

    setup_vectors(&token_vec, &type_vec);

    for (size_t i = 0; i < token_vec.len; i++) {
        print_token_and_type(&token_vec, &type_vec, i);
    }

    deallocate_vectors(&token_vec, &type_vec);

    return (0);
}
