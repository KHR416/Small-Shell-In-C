/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:11:23 by chakim            #+#    #+#             */
/*   Updated: 2025/03/22 14:49:51 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_valid_arg(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str != '=' && *str != '\0')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	is_equal_exist(char *str)
{
	return (ft_strchr(str, '=') != NULL);
}

char	*get_first_line(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		++i;
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}

char	*get_second_line(char *str)
{
	char	*equal;
	char	*result;

	if (!str)
		return (NULL);
	equal = ft_strchr(str, '=');
	if (equal == NULL)
		result = ft_strdup("");
	else
		result = ft_strdup(equal + 1);
	return (result);
}

void	print_single_env(char *env)
{
	char	*first_line;
	char	*second_line;

	if (is_equal_exist(env))
	{
		first_line = get_first_line(env);
		second_line = get_second_line(env);
		if (!first_line || !second_line)
		{
			free(first_line);
			free(second_line);
			return ;
		}
		printf("declare -x %s=\"%s\"\n", first_line, second_line);
		free(first_line);
		free(second_line);
	}
	else
		printf("declare -x %s\n", env);
}
