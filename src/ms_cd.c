/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/03/17 16:48:19 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_error_checker(char **args)
{
	char *path;

	path = args[1];
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (FAILURE);
	}
	if (access(args[1], F_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (127);
	}
	if (access(args[1], R_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (126);
	}
	return (SUCCESS);
}

// static char	*set_to_parent_dir(char *abs_path)
// {
// 	char	*result;
// 	size_t	diff;
// 	char	*last_slash;

// 	if (!abs_path)
// 		return (NULL);
// 	last_slash = ft_strrchr(abs_path, '/');
// 	if (last_slash == abs_path)
// 		diff = 1;
// 	else
// 		diff = (size_t)(last_slash - abs_path);
// 	result = ft_substr(abs_path, 0, diff);
// 	free(abs_path);
// 	return (result);
// }

static int	how_many_dots(char **args)
{
	if (ft_strcmp(args[1], ".") == 0)
		return (1);
	if (ft_strcmp(args[1], "..") == 0)
		return (2);
	return (0);
}

int	ms_cd(char **args, t_msvar *msvar)
{
	int		error_code;
	int		dot_case;

	if (!args[1])
		return (SUCCESS);
	dot_case = how_many_dots(args);
	if (dot_case == 0)
	{
		error_code = cd_error_checker(args);
		if (error_code != SUCCESS)
			return (error_code);
	}
	// if (dot_case == 1)
	// 	abs_path = ms_getcwd(msvar);
	// else if (dot_case == 2)
	// 	abs_path = set_to_parent_dir(ms_getcwd(msvar));
	// else
	// 	abs_path = ft_strdup(args[1]);
	// if (!abs_path)
	// 	return (FAILURE);
	clear_buf(msvar->buf);
	if (args[1][0] == '.')
	{
		cat_buf(msvar->buf, msvar->cw_backup);
		if (dot_case == 2)
		{
			char	*temp = ft_strrchr(msvar->buf->buffer, '/');
			if  (temp != msvar->buf->buffer)
				*temp = '\0';
			msvar->buf->length = ft_strlen(msvar->buf->buffer);
		}
	}
	else if (args[1][0] == '/')
		cat_buf(msvar->buf, args[1]);
	else
	{
		cat_buf(msvar->buf, msvar->cw_backup);
		append_buf(msvar->buf, '/');
		cat_buf(msvar->buf, args[1]);
	}
	if (chdir(msvar->buf->buffer) == -1)
	{
		perror("minishell: cd");
		return (FAILURE);
	}
	free(msvar->old_cw_backp);
	msvar->old_cw_backp = msvar->cw_backup;
	msvar->cw_backup = ft_strdup(msvar->buf->buffer);
	ms_setenv("OLDPWD", msvar->old_cw_backp, &msvar->envp, msvar->buf);
	ms_setenv("PWD", msvar->cw_backup, &msvar->envp, msvar->buf);
	return (SUCCESS);
}
