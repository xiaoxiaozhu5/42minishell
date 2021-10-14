CC = gcc
RM = rm -f
INC = includes
INCLUDES = ft_minishell.h
LIBFT_FOLDER = libft
LIBFT_ARCHIVE = libft.a
CFLAGS = -Wall -Wextra -Werror -pthread -I$(INC) -I$(LIBFT_FOLDER)

NAME = minishell

SRCS = srcs/ft_main.c

OBJS = $(SRCS:%.c=%.o)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	@echo "Building: \033[0;34m$<\033[0m"

$(NAME): $(INC)/$(INCLUDES) $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_FOLDER)/$(LIBFT_ARCHIVE)
	@echo "Binary \033[0;32m$(NAME)\033[0m successfully linked!"

all: $(NAME)

clean:
	@make -C libft clean
	$(RM) $(OBJS)

fclean: clean
	@make -C libft fclean
	$(RM) $(NAME)

re: clean all

norminette:
	norminette $(SRCS)
	norminette $(INC)/$(INCLUDES)
	@echo "\033[0;35mAll files in accordance with norminette!\033[0m"
