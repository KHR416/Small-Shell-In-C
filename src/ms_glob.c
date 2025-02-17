/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:34:51 by chakim            #+#    #+#             */
/*   Updated: 2025/02/17 19:39:58 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_glob.h"

t_glob_result	*ms_glob(char *pattern)
{

}

void	ms_glob_free(t_glob_result *result)
{
	t_glob_match *match;
	t_glob_match *next;

	if (result == NULL)
		return ;
	match = result->matches;
	while (match != NULL)
	{
        next = match->next;
		free(match->word);
		free(match);
		match = next;
	}
	free(result);
}
