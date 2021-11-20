CC = gcc
RM = rm -f
INC = includes
INCLUDES = ft_minishell.h
LIBFT_FOLDER = libft
LIBFT_ARCHIVE = libft.a
CFLAGS = -Wall -Wextra -Werror -I$(INC) -I$(LIBFT_FOLDER) -g
LFLAGS = -lreadline -L ~/.brew/opt/readline/lib -I~/.brew/opt/readline/include/readline/

NAME = minishell

SRCS = srcs/ft_main.c \
	srcs/ft_parser.c \
	srcs/ft_history.c \
	srcs/ft_preprocess.c \
	srcs/ft_process.c \
	srcs/ft_preparser.c \
	srcs/ft_errors.c \
	srcs/ft_environment.c \
	srcs/ft_list.c \
	srcs/ft_list_clear.c \
	srcs/ft_list_main.c \
	srcs/ft_list_builder.c \
	srcs/ft_list_builder_utils.c \
	srcs/ft_split_args.c \
	srcs/ft_utils.c \
	srcs/ft_rm_whitespace.c \
	srcs/ft_strfind.c \
	srcs/ft_envp_utils.c \
	srcs/ft_exec_args.c \
	srcs/ft_buildin_export.c \
	srcs/ft_buildin_unset.c \
	srcs/ft_buildin_cd.c \
	srcs/ft_buildin_pwd.c \
	srcs/ft_buildin_echo.c \
	srcs/ft_buildin_env.c \
	srcs/ft_buildin_exit.c \
	srcs/ft_execve.c \
	srcs/pipe3.c \
	srcs/ft_redir.c \
	srcs/utils.c

OBJS = $(SRCS:%.c=%.o)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	@echo "Building: \033[0;34m$<\033[0m"

$(NAME):  $(INC)/$(INCLUDES) $(OBJS)
	@echo "Building: \033[0;34m$>$(LIBFT_ARCHIVE)\033[0m"
	@make -s -C libft
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS) $(LIBFT_FOLDER)/$(LIBFT_ARCHIVE)
	@echo "Binary \033[0;32m$(NAME)\033[0m successfully linked!"

all: $(NAME)

clean:
	@make -C libft clean -s
	@$(RM) $(OBJS)
	@echo "Cleanup: \033[0;34mobject files\033[0m"

fclean: clean
	@make -C libft fclean -s
	@$(RM) $(NAME)
	@echo "Cleanup: \033[0;34mlinked files\033[0m"

re: clean all

install:
	brew install readline || true

norminette:
	norminette $(SRCS)
	norminette $(INC)/$(INCLUDES)
	@echo "\033[0;35mAll files in accordance with norminette!\033[0m"
