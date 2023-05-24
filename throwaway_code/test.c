

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <strings.h>

typedef struct  s_token
{
  char  *token;
  int	type;
}               t_token;

# include <stdbool.h>

typedef struct s_vec
{
	unsigned char	*memory;
	size_t			elem_size;
	size_t			alloc_size;
	size_t			len;
}	t_vec;

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

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

int	vec_new(t_vec *dst, size_t init_len, size_t elem_size)
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

int	vec_free(t_vec *src)
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

void	*vec_get(t_vec *src, size_t index)
{
	unsigned char	*ptr;

	if (index >= src->len || !src || !src->memory)
		return (NULL);
	ptr = &src->memory[src->elem_size * index];
	return (ptr);
}

int	vec_resize(t_vec *src, size_t target_len)
{
	t_vec	dst;

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

int	vec_push(t_vec *dst, void **src)
{
	if (!dst || !src)
		return (-1);
	else if (!dst->memory)
	{
		if (vec_new(dst, 1, dst->elem_size) < 0)
			return (-1);
	}
	if (dst->elem_size * dst->len >= dst->alloc_size)
	{
		if (vec_resize(dst, dst->len * 2) < 0)
			return (-1);
	}
	ft_memcpy(&dst->memory[dst->elem_size * dst->len], *src, dst->elem_size);
    dst->len++;
	return (1);
}

int main(void)
{
    t_vec vec;
    t_token *t1 = malloc(sizeof(t_token));
    t_token *t2 = malloc(sizeof(t_token));
    t_token *t3 = malloc(sizeof(t_token));
    t_token *t4 = malloc(sizeof(t_token));

    t1->token = strdup("token1");
    t1->type = 1;

    t2->token = strdup("token2");
    t2->type = 2;

    t3->token = strdup("token3");
    t3->type = 3;

    t4->token = strdup("token4");
    t4->type = 4;

    vec_new(&vec, 0, sizeof(t_token *));

	vec_push(&vec, (void **)&t1);
    vec_push(&vec, (void **)&t2);
    vec_push(&vec, (void **)&t3);
    vec_push(&vec, (void **)&t4);

    for (size_t i = 0; i < vec.len; i++) {
        t_token *token = *(t_token **)vec_get(&vec, i);
        if (token != NULL) {
            printf("Token: %s, Type: %d\n", token->token, token->type);
        }
    }

    vec_free(&vec);

    free(t1->token);
    free(t2->token);
    free(t3->token);
    free(t4->token);

    free(t1);
    free(t2);
    free(t3);
    free(t4);

    return (0);
}

