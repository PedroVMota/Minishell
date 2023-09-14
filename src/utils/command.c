#include <minishell.h>

// void LinkNode(t_cmds *recent, t_cmds *new)
// {
//     if(!recent || !new)
//         return ;
//     recent->prev = new;
//     new->next = recent;
// }

t_cmds *ReturnLastPos(t_cmds *cmds)
{
    if(!cmds)
        return NULL;
    while(cmds->next)
        cmds = cmds->next;
    return cmds;
}

