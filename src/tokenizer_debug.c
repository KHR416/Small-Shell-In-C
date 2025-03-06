/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/06 01:54:51 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdio.h>

#ifdef DEBUG
void	print_token(t_token *t)
{

	if (t->type == TOKEN_LITERAL)
		fprintf(stderr, "LITERAL: %s\n", (char *)t->data);
	else if (t->type == TOKEN_PIPE)
		fprintf(stderr, "|\n");
	else if (t->type == TOKEN_INPUT_REDIRECT)
		fprintf(stderr, "<\n");
	else if (t->type == TOKEN_HERE_DOC)
		fprintf(stderr, "<<\n");
	else if (t->type == TOKEN_OUTPUT_REDIRECT)
		fprintf(stderr, ">\n");
	else if (t->type == TOKEN_APPEND_REDIRECT)
		fprintf(stderr, ">>\n");
	else if (t->type == TOKEN_GLOB)
	{
		fprintf(stderr, "GLOB: \n");
		for (size_t i = 0; ; ++i)
		{
			fprintf(stderr, "\tdata[%zu]: %s\n", i, ((char **)(t->data))[i]);
			if (!((char **)(t->data))[i])
				break ;
		}
	}
	else
		fprintf(stderr, "unknown token\n");
}

void	print_token_stream(t_token_stream *ts)
{
	for (size_t i = 0; ts->arr[i].type != TOKEN_NONE; ++i)
		print_token(ts->arr + i);
}
#endif	// DEBUG
