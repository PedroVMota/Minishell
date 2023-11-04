NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
CFLAGS_EXTRA = -g -fsanitize=address
INC = -I inc/
EXT_LIBRARY = libft/libft.a


FILES = src/init/main.c src/init/build.c src/init/syntax.c src/init/signal.c \
		src/init/parse.c src/init/enviroment.c src/utils/manipulation.c src/utils/del.c \
		src/utils/Permissions/perm.c src/utils/search.c src/utils/t_mode.c src/utils/quotes.c \
		src/utils/.utils.c src/utils/var.c src/utils/switchchar.c src/utils/commands.c \
		src/builtins/exec.c src/builtins/cd_utils.c src/builtins/exit.c src/builtins/unset.c \
		src/builtins/env.c src/builtins/pwd.c src/builtins/export.c src/builtins/cd.c \
		src/builtins/echo.c src/execution/redirection.c src/execution/decider.c src/execution/heredoc.c \
		src/execution/dups.c src/init/prompt.c

OBJS = $(FILES:.c=.o)

all: $(NAME)
	./$(NAME)


$(NAME): $(OBJS)
	@make -C libft/ --no-print
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(INC) $(OBJS) $(EXT_LIBRARY) -lreadline  -lncurses -o $(NAME)

%.o: %.c
	@printf "\033[0;32mMinishell: \033[0;33mTaking care of the software...\033[0m\r"
	@$(CC) $(CFLAGS) -D MAIN $(CFLAGS_EXTRA) $(INC) -c $< -o $@

clean:
	@make clean -C libft/ --no-print
	@rm -f $(OBJS)
	@rm -rf  *.log */*.log */*/*.log log.*

fclean: clean 
	@rm -f $(NAME) lst lst.txt *.log *.del *.ign
	@make fclean -C libft/ --no-print
	clear \


re: fclean all