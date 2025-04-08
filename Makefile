#•❅──────✧❅✦❅✧──────❅••❅──────✧❅✦❅✧───NAME───✧❅✦❅✧──────❅••❅──────✧❅✦❅✧──────❅•#

NAME = minishell
LIBFT = lib/libft/libft.a

#•❅──────✧❅✦❅✧──────❅••❅──────✧❅✦❅✧──COMPILE──✧❅✦❅✧──────❅••❅──────✧❅✦❅✧──────❅•#

CC = gcc
FLAGS = -Wall -Wextra -Werror -Iinc -lreadline -g
RM = rm -rf

#•❅──────✧❅✦❅✧──────❅••❅──────✧❅✦❅✧───FILES───✧❅✦❅✧──────❅••❅──────✧❅✦❅✧──────❅•#

OBJ_DIR = obj


SRCS = src/main/minishell.c \
		src/parsing/00_token.c \
		src/parsing/01_valid_tokens.c \
		src/parsing/02_parser.c \
		src/parsing/03_expansion.c \
		src/parsing/04_commands.c \
		src/parsing/05_commands_redir.c \
		src/parsing/command_utils.c \
		src/parsing/exp_utils.c \
		src/parsing/lexer_utils.c \
		src/parsing/token_utils.c \
		src/environment/convert_env.c \
		src/environment/init_env.c \
		src/environment/empty_env.c \
		src/builtins/echo.c \
		src/builtins/cd.c \
		src/builtins/cd_utils.c \
		src/builtins/env.c \
		src/builtins/pwd.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/unset.c \
		src/redirections/check_redirections.c \
		src/redirections/handle_redirections.c \
		src/pipe/error_pipe.c \
		src/pipe/execute_pipe.c \
		src/execution/command_execution.c \
		src/execution/external_command.c \
		src/execution/error_command.c \
		src/signals/signal.c \
		src/tools/free.c \
		src/tools/free_utils.c \
		src/tools/utils.c \

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

#•❅──────✧❅✦❅✧──────❅••❅──────✧❅✦❅✧───COLORS──✧❅✦❅✧──────❅••❅──────✧❅✦❅✧──────❅•#

NO_COLOR = \033[0m
OK_COLOR = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR = \033[0;33m

#•❅──────✧❅✦❅✧──────❅••❅──────✧❅✦❅✧───RULES───✧❅✦❅✧──────❅••❅──────✧❅✦❅✧──────❅•#

all: $(LIBFT) $(NAME)


$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBFT) $(FLAGS) -o $(NAME)
	@echo "\n\n ✅ $(OK_COLOR)$(NAME) created!$(NO_COLOR)\n\n"


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@


$(LIBFT):
	@make -C lib/libft > /dev/null 2>&1


clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C lib/libft > /dev/null 2>&1
	@echo "\n\n$(WARN_COLOR)Object files cleaned!$(NO_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C lib/libft > /dev/null 2>&1
	@echo "\n\n 🚮 $(ERROR_COLOR)Minishell removed$(NO_COLOR)\n\n"

re: fclean all

#•❅──────✧❅✦❅✧──────❅••❅──────✧❅✦❅✧───PHONY───✧❅✦❅✧──────❅••❅──────✧❅✦❅✧──────❅•#

.PHONY: all clean fclean re
