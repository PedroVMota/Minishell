#include "minishell.h" 

bool t_redirection_has_hd(t_redirections *lst)
{
    while(lst)
    {
        if(lst->mode == FILE_IN_HEREDOC)
            return true;
        lst = lst->next;
    }
    return false;
}