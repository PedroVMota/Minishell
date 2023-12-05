#include <builtins.h>

void get_default_fdi(t_cmds *command)
{
    int fdi_for_use;

    fdi_for_use = -1;
    if(!command->is_builtin && (command->next || command->prev))
        return ;
    if(command->redirection[0] != -1)
        fdi_for_use = command->redirection[0];
    if(fdi_for_use == -1)
        fdi_for_use = command->saved_stdin;
    return (fdi_for_use);    
}

void get_default_fdo(t_cmds *command)
{
    int fdo_for_use;

    fdo_for_use = -1;
    if(!command->is_builtin && (command->next || command->prev))
        return ;
    if(command->redirection[0] != -1)
        fdo_for_use = command->redirection[0];
    if(fdo_for_use == -1)
        fdo_for_use = command->saved_stdin;
    return (fdo_for_use);    
}