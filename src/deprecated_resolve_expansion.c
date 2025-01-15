/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deprecated_resolve_expansion.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:15:41 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/14 22:57:28 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include "buffer.h"
// #include "astree.h"
// #include <libft.h>
// #include <stdlib.h>

// int	set_mod(t_quote_mode *mode, char c)
// {
// 	if (c == '\'')
// 	{
// 		if (*mode == DOUBLE_QUOTE)
// 			return (FAILURE);
// 		else if (*mode == SINGLE_QUOTE)
// 			*mode = WITHOUT_QUOTE;
// 		else if (*mode == WITHOUT_QUOTE)
// 			*mode = SINGLE_QUOTE;
// 		return (SUCCESS);
// 	}
// 	else if (c == '\"')
// 	{
// 		if (*mode == SINGLE_QUOTE)
// 			return (FAILURE);
// 		else if (*mode == DOUBLE_QUOTE)
// 			*mode = WITHOUT_QUOTE;
// 		else if (*mode == WITHOUT_QUOTE)
// 			*mode = DOUBLE_QUOTE;
// 		return (SUCCESS);
// 	}
// 	return (FAILURE);
// }

// char	*get_path_name(char *str)
// {
// 	char	*name;
// 	size_t	len;

// 	len = 0;
// 	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
// 		++len;
// 	name = malloc(len + 1);
// 	if (!name)
// 		return (NULL);
// 	ft_strlcpy(name, str, len + 1);
// 	return (name);
// }

// size_t	expand_dollar_sign(t_buf *buf, char *str, char **envp)
// {
// 	char	*env_name;
// 	size_t	result;

// 	++str;
// 	if (*str == '?')
// 	{
// 		cat_buf(buf, "EXIT_STATUS");
// 		result = 2;
// 	}
// 	else if (ft_isalpha(*str) || *str == '_')
// 	{
// 		env_name = get_path_name(str);
// 		cat_buf(buf, ms_getenv(env_name, envp));
// 		result = ft_strlen(env_name) + 1;
// 		free(env_name);
// 	}
// 	else
// 	{
// 		append_buf(buf, '$');
// 		result = 1;
// 	}
// 	return (result);
// }

// /*
// resolve_expansion - Interpret meta characters in a string

// DESCRIPTION
// This function scans the input string `str` for meta characters
// such as single quotes ('), double quotes ("), and the dollar sign ($).
// It interprets these characters according to  shell-like expansion rules:
// - Toggles quote modes when encountering quotes.
// - Expands environment variables when encountering `$` outside of single quotes.
// - Removes quotes appropriately from the resulting string.

// The function uses the provided environment variables array `envp` to substitute 
// values for expanded variables.

// RETURN
// On success, a null-terminated string with all expansions and quote removals
// applied. Or `NULL` on failure.

// NOTE
// The caller is responsible for freeing the returned string to avoid memory leaks.
// Ensure that proper error handling and memory management are implemented
// when using this function.
// */
// char	*resolve_expansion(char *str, char **envp)
// {
// 	t_quote_mode	quote_mode;
// 	t_buf			*buf;

// 	quote_mode = WITHOUT_QUOTE;
// 	buf = create_buf();
// 	if (!buf)
// 		return (NULL);
// 	while (*str)
// 	{
// 		if (set_mod(&quote_mode, *str))
// 		{
// 			if (quote_mode != SINGLE_QUOTE && *str == '$')
// 				str += expand_dollar_sign(buf, str, envp);
// 			else
// 				append_buf(buf, *str++);
// 		}
// 		else
// 			++str;
// 	}
// 	return (detach_buf(buf));
// }
