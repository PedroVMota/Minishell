NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
CFLAGS_EXTRA = -g #-fsanitize=address
INC = -I inc/ -I inc/lib/Builtin/ -Iinc/lib/Var/ -Iinc/lib/Libft
libft = inc/lib/Libft/utils

FILES =	src/init/main.c src/init/Signal.c src/LinkList/CommandLinkList.c src/LinkList/Redirection.functions.c \
		src/LinkList/EnviromentLinkList.c src/LinkList/RedirectionLinkList.c src/LinkList/CommandList.c src/LinkList/Redirection.utils.c \
		src/MemoryManegment/del.c src/MemoryManegment/del.utils.c src/execution/Runner.c src/execution/Runner.smf.c \
		src/execution/Runner.utils.c src/utils/Quote_Parse.c src/utils/SplitManipulator.c src/utils/HelperFunctions.c \
		src/utils/Tokenizer.c src/FileDescriptors/heredoc.c src/syntax/SyntaxSmallFunctions.c src/syntax/SyntaxUtils.c \
		src/syntax/SyntaxChecker.c inc/lib/Builtin/utils/unset.c inc/lib/Builtin/utils/pwd.c inc/lib/Builtin/utils/cd.c \
		inc/lib/Builtin/utils/Input_Output.c inc/lib/Builtin/utils/echo.c inc/lib/Builtin/utils/env.c inc/lib/Builtin/utils/CommandPermissions/CommandPermission_utils1.c \
		inc/lib/Builtin/utils/CommandPermissions/CommandPermission_utils0.c inc/lib/Builtin/utils/CommandPermissions/CommandPermission_utils2.c inc/lib/Builtin/utils/CommandPermissions/main.c inc/lib/Builtin/utils/exec.c \
		inc/lib/Builtin/utils/export.utils.c inc/lib/Builtin/utils/exit.c inc/lib/Builtin/utils/Input_Output.utils.c inc/lib/Builtin/utils/export.c \
		inc/lib/Builtin/utils/cd_utils.c inc/lib/Var/utils/var_utils.c inc/lib/Var/utils/var_utils2.c inc/lib/Var/utils/var.c \
		inc/lib/Var/utils/var.small.f.c 
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