/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:31:29 by chakim            #+#    #+#             */
/*   Updated: 2025/02/17 19:47:44 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_GLOB_H
# define MS_GLOB_H

# include <stdlib.h>

typedef struct s_glob_match
{
	char	*word;
	struct	s_glob_match *next;
}	t_glob_match;

typedef struct s_glob_result
{
	t_glob_match	*matches;
	int				match_count;
}	t_glob_result;

t_glob_result	*ms_glob(char *pattern);
void			ms_glob_free(t_glob_result *result);

#endif