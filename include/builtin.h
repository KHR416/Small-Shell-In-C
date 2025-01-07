/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:55:53 by chakim            #+#    #+#             */
/*   Updated: 2025/01/07 20:22:13 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "ms_readline.h"

int	is_valid_builtins(t_command *command, t_msvar *var);
int	ms_cd(char **args);
int	ms_echo_n_option(char **args);
int	ms_echo(char **args);
int	ms_env(char **args, t_msvar *var);
int	ms_exit(char **args);
int	ms_export(char **args, t_msvar *var);
int	ms_pwd(void);
int	ms_exit(char **args);

#endif