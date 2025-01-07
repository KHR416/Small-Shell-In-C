/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:49:39 by chakim            #+#    #+#             */
/*   Updated: 2025/01/07 19:22:07 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_pipes
{
	int		**pipes;
	pid_t	*pids;
	int		pipe_count;
	int		cmd_count;
}	t_pipes;

void	child_process(t_pipes *pipes, int i, t_msvar *var);
void	init_pipes(t_pipes *pipes, t_msvar *var);
void	handling_pipes(t_msvar *var);
void	destroy_pipes(t_pipes *pipes);
void	free_pipes(t_pipes *pipes, int i);
void	close_pipes(t_pipes *pipes, int except_index);

#endif