/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:00:14 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/10 18:34:34 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SUCCESS	0
# define FAILURE	1

typedef struct s_msvar
{
	int		argc;
	char	**argv;
	char	**envp;
	int		wstatus;
}	t_msvar;

char	*ms_getcwd(void);
char	**ms_envpcpy(char **envp);
void	ms_envp_destroy(char **arr);
char	*ms_getenv(char *name, char **envp);
int		ms_setenv(char *name, char *value, char ***envp);
int		ms_var_init(int argc, char **argv, char **envp, t_msvar *var);
void	free_msvar(t_msvar *msvar);

#endif	// MINISHELL_H