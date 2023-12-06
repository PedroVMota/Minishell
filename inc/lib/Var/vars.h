/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 04:57:29 by pedro             #+#    #+#             */
/*   Updated: 2023/12/06 04:57:30 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include <defines.h>
# include <libft.h>
# include <stdbool.h>
# include <stdlib.h>

void	*trash(char **array);
char	*varlib_execute(char *s, t_shell *h);
void	*free_array(char **array);
bool	does_have_var(char *s);
int		varlib_start_position(char *ptr);

#endif
