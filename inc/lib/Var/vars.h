#ifndef VARS_H
# define VARS_H

# include <defines.h>
# include <libft.h>
# include <stdlib.h>
# include <stdbool.h>

void *trash(char **array);
char	*varlib_execute(char *s, t_shell *h);
void	*free_array(char **array);
bool	does_have_var(char *s);
int		varlib_start_position(char *ptr);

#endif
