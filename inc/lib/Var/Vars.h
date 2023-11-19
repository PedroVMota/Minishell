#ifndef VAR_H
#define VAR_H

#include <stdlib.h>
#include <defines.h>

char *varlib_replace(char **str, char *new_value, char *del);
char *varlib_delete_unknown(char *str);
int varlib_start_position(char *ptr);
char *varlib_obtain(char *str);
char *varlib_execute(char *s, t_shell *h);

#endif
