/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:38:12 by pedro             #+#    #+#             */
/*   Updated: 2023/11/24 11:24:14 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include <defines.h>
# include <libft.h>
# include <stdlib.h>
# include <stdbool.h>

char	*varlib_execute(char *s, t_shell *h);
void	*free_array(char **array);
bool	does_have_var(char *s);
int		varlib_start_position(char *ptr);

#endif
