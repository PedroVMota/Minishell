/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:18:08 by pedro             #+#    #+#             */
/*   Updated: 2023/09/21 18:18:11 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Update the t_mode enum value only works for char;
void	ft_mode_changer_ascii(char set, t_mode *stat)
{
	if (!set)
		return ;
	if (set == '\"' && *stat == ENV_MODE_TOKEN)
		*stat = ENV_MODE_DQUOTE;
	else if (set == '\'' && *stat == ENV_MODE_TOKEN)
		*stat = ENV_MODE_QUOTE;
	else if (set == '\"' && *stat == ENV_MODE_DQUOTE)
		*stat = ENV_MODE_TOKEN;
	else if (set == '\'' && *stat == ENV_MODE_QUOTE)
		*stat = ENV_MODE_TOKEN;
}

// Update the t_mode enum value only works for special caracters;
void	ft_mode_changer_not_printable(char set, t_mode *stat)
{
	if (!set)
		return ;
	if (set == TOKEN_DQUOTE && *stat == ENV_MODE_TOKEN)
		*stat = ENV_MODE_DQUOTE;
	else if (set == TOKEN_QUOTE && *stat == ENV_MODE_TOKEN)
		*stat = ENV_MODE_QUOTE;
	else if (set == TOKEN_DQUOTE && *stat == ENV_MODE_DQUOTE)
		*stat = ENV_MODE_TOKEN;
	else if (set == TOKEN_QUOTE && *stat == ENV_MODE_QUOTE)
		*stat = ENV_MODE_TOKEN;
}
