# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kricky <kricky@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/16 14:16:38 by kricky            #+#    #+#              #
#    Updated: 2021/09/01 10:36:57 by kricky           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
RM = rm -f

INCLUDES = libft.h

SRCS = ft_memccpy.c\
		ft_memcpy.c\
		ft_memset.c\
		ft_strlen.c\
		ft_bzero.c\
		ft_memmove.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strcpy.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strnstr.c\
		ft_itoa.c\
		ft_strncmp.c\
		ft_atoi.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_strmapi.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		get_next_line.c\
		ft_wdcounter.c\
		ft_abs.c\
		ft_nbrcmp.c

SRCS_BONUSES = ft_lstnew.c\
	  			ft_lstadd_front.c\
	  			ft_lstsize.c\
	  			ft_lstlast.c\
	  			ft_lstadd_back.c\
	  			ft_lstdelone.c\
	  			ft_lstclear.c\
	  			ft_lstiter.c\
	  			ft_lstmap.c

OBJS = ${SRCS:.c=.o}
OBJS_BONUSES = ${SRCS_BONUSES:.c=.o}

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

$(NAME): $(OBJS)
	ar rcs $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUSES)

fclean: clean
	$(RM) $(NAME)

bonus: $(OBJS) $(OBJS_BONUSES)
	ar rcs $(NAME) $^

re: clean all
