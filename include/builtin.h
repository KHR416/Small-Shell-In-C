/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:55:53 by chakim            #+#    #+#             */
/*   Updated: 2025/03/15 23:36:15 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "ms_readline.h"
# include "minishell.h"

int	ms_cd(char **args, char ***envp, t_buf *buf);
int	ms_echo_n_option(char **args);
int	ms_echo(char **args);
int	ms_env(char **args, t_msvar *var);
int	ms_export(char **args, t_msvar *var);
int	ms_pwd(t_buf *buf);
int	ms_exit(char **args, t_msvar *var);
int	ms_unset(char **args, t_msvar *var);
int	is_builtin(char *cmd);
int	exec_builtin(char **argv, t_msvar *var);
int	is_valid_arg(char *str);

#endif