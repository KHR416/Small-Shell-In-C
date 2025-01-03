/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:00:14 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/03 16:35:05 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif	// BUFFER_SIZE
# define SUCCESS	0
# define FAILURE	1

typedef struct s_msvar
{
	char	**envp;
}	t_msvar;

char	*ms_getcwd(void);
char	**ms_envpcpy(char **envp);
void	ms_envp_destroy(void **arr);
char	*ms_getenv(char *name, char **envp);
int		ms_setenv(char *name, char *value, char ***envp);
#endif	// MINISHELL_H