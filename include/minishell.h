/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:00:14 by wchoe             #+#    #+#             */
/*   Updated: 2025/04/04 17:39:58 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ms_glob.h"
# include "ms_def.h"
# include "buffer.h"
# define MS_PROMPT	"minishell$ "

extern int	g_ms_signal;

typedef struct s_msvar
{
	int		argc;
	char	**argv;
	char	**envp;
	int		exit_status;
	int		ttydup[2];
	void	*ast;
	size_t	heredoc_count;
	t_buf	*buf;
	t_buf	*command_buf;
	char	*cw_backup;
	char	*old_cw_backp;
}	t_msvar;

char	*ms_getcwd(t_msvar *msvar);
char	**ms_envpcpy(char **envp);
void	ms_envp_destroy(char **arr);
char	*ms_getenv(char *name, char **envp);
int		ms_setenv(char *name, char *value, char ***envp, t_buf *buf);
int		ms_var_init(int argc, char **argv, char **envp, t_msvar *var);
void	clear_msvar(t_msvar *msvar);
void	clear_ttydup(t_msvar *msvar);
int		restore_ttydup(t_msvar *msvar);

#endif	// MINISHELL_H
