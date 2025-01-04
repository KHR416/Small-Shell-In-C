/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:15:41 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/04 19:22:21 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

#define WITHOUT_QUOTE	0
#define SINGLE_QUOTE	1
#define DOUBLE_QUOTE	2

char	*expand(char *str)
{
	int		quote_mode;
	char	*buf;
	size_t	size;

	quote_mode = WITHOUT_QUOTE;
	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	size = BUFFER_SIZE;
}