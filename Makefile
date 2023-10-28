NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
CFLAGS_EXTRA = -g
INC = -I inc/
EXT_LIBRARY = libft/libft.a


FILES = src/build.c src/builtins/cd.c src/builtins/echo.c src/builtins/env.c \
		src/builtins/exec.c src/builtins/exit.c src/builtins/export.c src/builtins/pwd.c \
		src/builtins/unset.c src/enviroment.c src/execution/decider.c src/execution/dups.c \
		src/execution/heredoc.c src/main.c src/parse.c src/execution/redirection.c \
		src/signal.c src/syntax.c src/utils/.utils.c src/utils/Permissions/perm.c \
		src/utils/commands.c src/utils/del.c src/utils/manipulation.c src/utils/quotes.c \
		src/utils/search.c src/utils/switchchar.c src/utils/t_mode.c src/utils/var.c

OBJS = $(FILES:.c=.o)

all: $(NAME)
	./$(NAME)
		@valgrind --track-fds=yes --trace-children=yes --leak-check=full ./$(NAME)


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

fclean: clean #useless
	@rm -f $(NAME) lst lst.txt
	rm -rf *.log *.del *.ign
	@make fclean -C libft/ --no-print
	clear \


re: fclean all