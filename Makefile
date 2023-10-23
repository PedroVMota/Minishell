NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
CFLAGS_EXTRA = -g -fsanitize=address,undefined
INC = -I include/
EXT_LIBRARY = libft/libft.a


FILES = $(shell find ./src/ -type f -name "*.c")

OBJS = $(FILES:.c=.o)

all: $(NAME)
	./$(NAME)
#@valgrind --leak-check=full env -i ./$(NAME)


$(NAME): $(OBJS)
	@make -C libft/ --no-print
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(INC) $(OBJS) $(EXT_LIBRARY) -lreadline  -lncurses -o $(NAME)

%.o: %.c
	@printf "\033[0;32mMinishell: \033[0;33mTaking care of the software...\033[0m\n"
	@$(CC) $(CFLAGS) -D MAIN $(CFLAGS_EXTRA) $(INC) -c $< -o $@

clean:
	@make clean -C libft/ --no-print
	@rm -f $(OBJS)
	@rm -rf  *.log */*.log */*/*.log log.*


useless: 
	rm -rf *.log *.del *.ign
	
fclean: clean useless
	@rm -f $(NAME) lst lst.txt
	@make fclean -C libft/ --no-print
	clear \


re: fclean all

	@valgrind --leak-check=full env -i ./$(NAME)
valgrind: $(NAME)