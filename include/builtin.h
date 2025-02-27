/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:55:53 by chakim            #+#    #+#             */
/*   Updated: 2025/02/27 05:38:38 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "ms_readline.h"
# include "minishell.h"

int	is_valid_builtins(t_command *command, t_msvar *var);
int	ms_cd(char **args);
int	ms_echo_n_option(char **args);
int	ms_echo(char **args);
int	ms_env(char **args, t_msvar *var);
int	ms_export(char **args, t_msvar *var);
int	ms_pwd(void);
int	ms_exit(char **args, t_msvar *var);
int	ms_unset(char **args, t_msvar *var);
int	is_builtin(char *cmd);
int	exec_builtin(char **argv, t_msvar *var);
#endif