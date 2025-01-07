/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:40:42 by chakim            #+#    #+#             */
/*   Updated: 2025/01/07 20:30:11 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_READLINE_H
# define MS_READLINE_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
	assume cmd is total line of wrote in prompt,
	args are preprocessed args.
*/
typedef struct s_command
{
	char	*cmd;
	char	**args;
}	t_command;

char	*rl_gets(void);

#endif
