# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 14:22:41 by jmykkane          #+#    #+#              #
#    Updated: 2023/06/06 15:43:26 by oanttoor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memcpy.c ft_memmove.c ft_memset.c\
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strncmp.c\
ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c\
ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_memchr.c ft_memcmp.c\
ft_strtrim.c ft_strnstr.c ft_calloc.c ft_strmapi.c ft_striteri.c ft_split.c\
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstadd_back.c ft_lstlast.c\
ft_puthex_lower_fd.c ft_puthex_upper_fd.c ft_memrcpy.c ft_hexlen.c\
get_next_line.c get_next_line_utils.c ft_printf.c convert_c.c\
convert_d_i.c convert_p.c convert_s.c convert_u.c convert_x.c\
convert_precentage.c dir_check.c\
vec_append.c vec_copy.c vec_filter.c vec_free.c vec_from.c vec_get.c\
vec_insert.c vec_iter.c vec_map.c vec_new.c vec_pop.c vec_prepend.c\
vec_push.c vec_remove.c vec_resize.c ft_strcmp.c ft_isnum.c

SRC_O = $(SRC:.c=.o)

INCLUDES = libft.h get_next_line.h ft_printf.h vec.h

FLAGS = -Wall -Werror -Wextra -g -I $(INCLUDES)

all: $(NAME)

$(NAME): $(SRC_O)
	cc -c $(FLAGS) $(SRC)
	ar rc $(NAME) $(SRC_O)

clean:
	rm -f $(SRC_O)

fclean:
	rm -f $(SRC_O)
	rm -f $(NAME)

re: fclean all
