NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
CFLAGS_EXTRA = -g #-fsanitize=address
INC = -I inc/ -I inc/lib/Builtin/ -Iinc/lib/Var/ -Iinc/lib/Libft
libft = inc/lib/Libft/utils

FILES =	src/init/parse.c src/init/enviroment.c src/init/main.c src/init/build.c \
		src/init/signal.c src/execution/set_dups/dups.c src/execution/heredoc.c src/execution/redirection.c \
		src/execution/chooser/decider_utils.c src/execution/chooser/decider.c src/utils/del.c src/utils/switchchar.c \
		src/utils/.utils.c src/utils/commands.c src/utils/manipulation.c src/syntax/syntax.c \
		src/syntax/syntax_utils.c inc/lib/Builtin/utils/unset.c inc/lib/Builtin/utils/pwd.c inc/lib/Builtin/utils/cd.c \
		inc/lib/Builtin/utils/echo.c inc/lib/Builtin/utils/env.c inc/lib/Builtin/utils/CommandPermissions/CommandPermission_utils1.c inc/lib/Builtin/utils/CommandPermissions/CommandPermission_utils0.c \
		inc/lib/Builtin/utils/CommandPermissions/CommandPermission_utils2.c inc/lib/Builtin/utils/CommandPermissions/main.c inc/lib/Builtin/utils/exec.c inc/lib/Builtin/utils/exit.c \
		inc/lib/Builtin/utils/export.c inc/lib/Builtin/utils/cd_utils.c inc/lib/Var/utils/var_utils.c inc/lib/Var/utils/var.c \

OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(libft) --no-print
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(INC) $(OBJS) inc/lib/Libft/utils/libft.a -lreadline  -lncurses -o $(NAME)

%.o: %.c
	@printf "\033[0;32mMinishell: \033[0;33mTaking care of the software...\033[0m\r"
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(INC) -c $< -o $@

clean:
	@make clean -C $(libft) --no-print
	@rm -rf  *.log */*.log */*/*.log  $(OBJS)

fclean: clean 
	@rm -f $(NAME) lst lst.txt *.log *.del *.ign
	@make fclean -C $(libft) --no-print

e:
	make && env -i ./minishell

d:
	make && valgrind --log-file="val.log" --suppressions="./pdfs/minishell.sup" --track-fds=yes ./minishell

f:
	make && valgrind --log-file="val.log"  --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=".minishell.sup" ./minishell

n:
	make && ./minishell
# make && ./minishell
#--log-file="val.log"

re: fclean all