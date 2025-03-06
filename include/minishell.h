/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:00:14 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/02 21:39:12 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef MEMCHECK
#  ifndef DEBUG
#   define MS_PROMPT	"minishell$ "
#  else
#   define MS_PROMPT	"debug$ "
#  endif	// DEBUG
# else
#  ifndef DEBUG
#   define MS_PROMPT	"memcheck$ "
#  else
#   define MS_PROMPT	"memcheck debug$ "
#  endif	// DEBUG
#endif	// MEMCHECK
# include "ms_glob.h"
# include "ms_def.h"

extern int	ms_signal;

typedef struct s_msvar
{
	int		argc;
	char	**argv;
	char	**envp;
	int		exit_status;
	int		ttydup[2];
	#ifdef DEBUG
	void	*ceu;
	void	*ps;
	#endif	// DEBUG
	void	*ast;
}	t_msvar;

char	*ms_getcwd(void);
char	**ms_envpcpy(char **envp);
void	ms_envp_destroy(char **arr);
char	*ms_getenv(char *name, char **envp);
int		ms_setenv(char *name, char *value, char ***envp);
int		ms_var_init(int argc, char **argv, char **envp, t_msvar *var);
void	clear_msvar(t_msvar *msvar);
void	clear_ttydup(t_msvar *msvar);
int		restore_ttydup(t_msvar *msvar);
char	*rl_gets(void);

#endif	// MINISHELL_H
