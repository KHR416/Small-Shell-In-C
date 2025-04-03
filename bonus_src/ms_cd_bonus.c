/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/03/22 16:51:31 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static int	how_many_dots(char **args)
{
	int	result;

	result = 0;
	if (ft_strcmp(args[1], ".") == 0)
		result = 1;
	else if (ft_strcmp(args[1], "..") == 0)
		result = 2;
	return (result);
}

static void	update_cwd(t_msvar *msvar)
{
	free(msvar->old_cw_backp);
	msvar->old_cw_backp = msvar->cw_backup;
	msvar->cw_backup = ft_strdup(msvar->buf->buffer);
	ms_setenv("OLDPWD", msvar->old_cw_backp, &msvar->envp, msvar->buf);
	ms_setenv("PWD", msvar->cw_backup, &msvar->envp, msvar->buf);
}

static int	handle_dot_cases(t_msvar *msvar, int dot_case)
{
	char	*temp;

	if (dot_case == 0)
		return (0);
	cat_buf(msvar->buf, msvar->cw_backup);
	if (dot_case == 2)
	{
		temp = ft_strrchr(msvar->buf->buffer, '/');
		if (temp != msvar->buf->buffer)
		{
			*temp = '\0';
		}
		msvar->buf->length = ft_strlen(msvar->buf->buffer);
	}
	return (1);
}

static void	build_path(t_msvar *msvar, char *arg)
{
	if (arg[0] == '/')
		cat_buf(msvar->buf, arg);
	else
	{
		cat_buf(msvar->buf, msvar->cw_backup);
		append_buf(msvar->buf, '/');
		cat_buf(msvar->buf, arg);
	}
}

int	ms_cd(char **args, t_msvar *msvar)
{
	int	error_code;
	int	dot_case;

	if (!args[1])
		return (SUCCESS);
	dot_case = how_many_dots(args);
	if (!handle_dot_cases(msvar, dot_case))
	{
		error_code = cd_error_checker(args);
		if (error_code != SUCCESS)
			return (error_code);
		clear_buf(msvar->buf);
		build_path(msvar, args[1]);
	}
	if (chdir(msvar->buf->buffer) == -1)
	{
		perror("minishell: cd");
		return (FAILURE);
	}
	update_cwd(msvar);
	return (SUCCESS);
}
