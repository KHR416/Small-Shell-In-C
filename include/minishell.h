/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:00:14 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/07 19:29:33 by chakim           ###   ########.fr       */
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
}	t_msvar;

char	*ms_getcwd(void);
char	**ms_envpcpy(char **envp);
void	ms_envp_destroy(void **arr);
char	*ms_getenv(char *name, char **envp);
int		ms_setenv(char *name, char *value, char ***envp);
void	ms_var_init(int argc, char **argv, char **envp, t_msvar *var);

#endif	// MINISHELL_H