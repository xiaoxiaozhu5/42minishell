NAME = minishell

CC = gcc
RM = rm -f
INC = includes
INCLUDES = ft_minishell.h
CFLAGS = -Wall -Wextra -Werror -lreadline -I$(INC) -I$(LIBFT_FOLDER)
LIBFT_FOLDER = libft
LIBFT_ARCHIVE = libft.a
EXTERNAL_LIBS = -lreadline

SRCS = srcs/ft_main.c \
	srcs/ft_parser.c \
	srcs/ft_history.c \
	srcs/ft_process.c \
	srcs/ft_preparser.c \
	srcs/ft_errors.c

OBJS = $(SRCS:%.c=%.o)

.c.o:
	@$(CC) $(CFLAGS) -c $< $(EXTERNAL_LIBS) -o $(<:.c=.o)
	@echo "Building: \033[0;34m$<\033[0m"

$(NAME): $(INC)/$(INCLUDES) $(OBJS)
	@echo "Building: \033[0;34m$>$(LIBFT_ARCHIVE)\033[0m"
	@make -s -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(EXTERNAL_LIBS) -o $(NAME) $(LIBFT_FOLDER)/$(LIBFT_ARCHIVE)
	@echo "Binary \033[0;32m$(NAME)\033[0m successfully linked!"

all: $(NAME)

clean:
	@make -C libft clean -s
	$(RM) $(OBJS)
	@echo "Cleanup: \033[0;34mobject files\033[0m"

fclean: clean
	@make -C libft fclean -s
	@$(RM) $(NAME)
	@echo "Cleanup: \033[0;34mlinked files\033[0m"

re: clean all

norminette:
	norminette $(SRCS)
	norminette $(INC)/$(INCLUDES)
	@echo "\033[0;35mAll files in accordance with norminette!\033[0m"

.SILENT: clean
