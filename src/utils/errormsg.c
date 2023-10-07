#include <minishell.h>


int displayerror(void *ptr, char *msg, int size)
{
	write(2, "Minishell: ", 12);
	if(size == sizeof(int) && *(int*)ptr == -1)
		write(2, msg, ft_strlen(msg));
	else if(size == sizeof(char *) && ptr == NULL)
		write(2, msg, ft_strlen(msg));
	return 1;
}