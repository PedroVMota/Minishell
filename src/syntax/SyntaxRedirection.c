
#include <minishell.h>

// SECTION - REDIRECTIONS ANALIZER
bool redi_ana(char *in, int *i, t_shell *sh)
{
    if (in[*i] == '<' && in[*i + 1] == '<')
        (*i) = (*i) + 2;
    else if (in[(*i)] == '>' && in[(*i) + 1] == '>')
        (*i) = (*i) + 2;
    else
        (*i)++;
    while (in[*i])
    {
        if (ft_isalnum(in[*i]))
            return false;
        else if (in[*i + 1] == '|')
            return (true);
        else if (in[*i] == '\'' || in[*i] == '\"')
        {
            skip_string_skip(in, i, sh);
            return false;
        }
        (*i)++;
    }
    return (true);
}
