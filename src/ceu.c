/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/07 23:07:32 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

void	print_error_unexpected_token(t_token_type t)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	if (t == TOKEN_NONE)
		ft_putstr_fd("new_line", STDERR_FILENO);
	else if (t == TOKEN_LITERAL)
		ft_putstr_fd("command", STDERR_FILENO);	// Is this case possible?
	else if (t == TOKEN_PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (t == TOKEN_INPUT_REDIRECT)
		ft_putstr_fd("<>", STDERR_FILENO);
	else if (t == TOKEN_HERE_DOC)
		ft_putstr_fd("<<", STDERR_FILENO);
	else if (t == TOKEN_OUTPUT_REDIRECT)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (t == TOKEN_APPEND_REDIRECT)
		ft_putstr_fd(">>", STDERR_FILENO);
	else
		ft_putstr_fd("unknown token", STDERR_FILENO);
	ft_putendl_fd("`", STDERR_FILENO);
}

t_in_redir	*create_in_redir(t_in_redir_type type, char *data)
{
	t_in_redir	*ir;

	if (!(type == IR_DEFAULT || type == IR_HERE_DOC))
		return (NULL);
	ir = malloc(sizeof(t_in_redir));
	if (!ir)
		return (NULL);
	ir->type = type;
	ir->name = ft_strdup(data);
	return (ir);
}

void	destroy_in_redir(void *ir)
{
	free(((t_in_redir *)ir)->name);
	free(ir);
}

t_out_redir	*create_out_redir(t_out_redir_type type, char *data)
{
	t_out_redir	*or;

	if (!(type == OR_DEFAULT || type == OR_APPEND))
		return (NULL);
	or = malloc(sizeof(t_out_redir));
	if (!or)
		return (NULL);
	or->type = type;
	or->name = ft_strdup(data);
	return (or);
}

void	destroy_out_redir(void *or)
{
	free(((t_out_redir *)or)->name);
	free(or);
}

void	destroy_argv(char **argv)
{
	char	**it;

	if (!argv)
		return ;
	it = argv;
	while (*it)
	{
		free(*it);
		++it;
	}
	free(argv);
}

void	**list_to_arr(t_list *lst, void *(*dup)())
{
	void	**arr;
	size_t	i;

	arr = malloc((ft_lstsize(lst) + 1) * sizeof(void *));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		arr[i++] = dup(lst->content);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

#include "generic_array.h"

t_ceu	*create_ceu(t_token *iter_begin, t_token *iter_end)
{
	t_ceu	*ceu;
	void	*temp;
	t_gen_arr	*ir_arr = create_gen_arr();
	t_gen_arr	*or_arr = create_gen_arr();
	t_gen_arr	*argv = create_gen_arr();

	if (iter_begin == iter_end)
	{
		print_error_unexpected_token(iter_begin->type);
		return (NULL);
	}
	ceu = ft_calloc(1, sizeof(t_ceu));
	if (!ceu)
		return (NULL);
	while (iter_begin < iter_end)
	{
		if (iter_begin->type == TOKEN_INPUT_REDIRECT)
		{
			if ((++iter_begin)->type != TOKEN_LITERAL)
			{
				print_error_unexpected_token(iter_begin->type);
				destroy_ceu(ceu);
				destroy_gen_arr(ir_arr, destroy_in_redir);
				destroy_gen_arr(or_arr, destroy_out_redir);
				destroy_gen_arr(argv, free);
				return (NULL);
			}
			temp = create_in_redir(IR_DEFAULT, iter_begin->data);
			if (!temp)
			{
				destroy_ceu(ceu);
				destroy_gen_arr(ir_arr, destroy_in_redir);
				destroy_gen_arr(or_arr, destroy_out_redir);
				destroy_gen_arr(argv, free);
				return (NULL);
			}
			append_gen_arr(ir_arr, temp, NULL);
		}
		else if (iter_begin->type == TOKEN_HERE_DOC)
		{
			if ((++iter_begin)->type != TOKEN_LITERAL)
			{
				print_error_unexpected_token(iter_begin->type);
				destroy_ceu(ceu);
				destroy_gen_arr(ir_arr, destroy_in_redir);
				destroy_gen_arr(or_arr, destroy_out_redir);
				destroy_gen_arr(argv, free);
				return (NULL);
			}
			temp = create_in_redir(IR_HERE_DOC, iter_begin->data);
			if (!temp)
			{
				destroy_ceu(ceu);
				destroy_gen_arr(ir_arr, destroy_in_redir);
				destroy_gen_arr(or_arr, destroy_out_redir);
				destroy_gen_arr(argv, free);
				return (NULL);
			}
			append_gen_arr(ir_arr, temp, NULL);
		}
		else if (iter_begin->type == TOKEN_OUTPUT_REDIRECT)
		{
			if ((++iter_begin)->type != TOKEN_LITERAL)
			{
				print_error_unexpected_token(iter_begin->type);
				destroy_ceu(ceu);
				destroy_gen_arr(ir_arr, destroy_in_redir);
				destroy_gen_arr(or_arr, destroy_out_redir);
				destroy_gen_arr(argv, free);
				return (NULL);
			}
			temp = create_out_redir(OR_DEFAULT, iter_begin->data);
			if (!temp)
			{
				destroy_ceu(ceu);
				destroy_gen_arr(ir_arr, destroy_in_redir);
				destroy_gen_arr(or_arr, destroy_out_redir);
				destroy_gen_arr(argv, free);
				return (NULL);
			}
			append_gen_arr(or_arr, temp, NULL);
		}
		else if (iter_begin->type == TOKEN_APPEND_REDIRECT)
		{
			if ((++iter_begin)->type != TOKEN_LITERAL)
			{
				print_error_unexpected_token(iter_begin->type);
				destroy_ceu(ceu);
				destroy_gen_arr(ir_arr, destroy_in_redir);
				destroy_gen_arr(or_arr, destroy_out_redir);
				destroy_gen_arr(argv, free);
				return (NULL);
			}
			temp = create_out_redir(OR_APPEND, iter_begin->data);
			if (!temp)
			{
				destroy_ceu(ceu);
				destroy_gen_arr(ir_arr, destroy_in_redir);
				destroy_gen_arr(or_arr, destroy_out_redir);
				destroy_gen_arr(argv, free);
				return (NULL);
			}
			append_gen_arr(or_arr, temp, NULL);
		}
		else if (iter_begin->type == TOKEN_LITERAL)
		{
			temp = ft_strdup(iter_begin->data);
			if (!temp)
			{
				destroy_ceu(ceu);
				destroy_gen_arr(ir_arr, destroy_in_redir);
				destroy_gen_arr(or_arr, destroy_out_redir);
				destroy_gen_arr(argv, free);
				return (NULL);
			}
			append_gen_arr(argv, temp, NULL);
		}
		else
		{
			print_error_unexpected_token(iter_begin->type);
			destroy_ceu(ceu);
			destroy_gen_arr(ir_arr, destroy_in_redir);
			destroy_gen_arr(or_arr, destroy_out_redir);
			destroy_gen_arr(argv, free);
			return (NULL);
		}
		++iter_begin;
	}
	ceu->argv = (char **)detach_gen_arr(argv);
	ceu->ir_arr = (t_in_redir **)detach_gen_arr(ir_arr);
	ceu->or_arr = (t_out_redir **)detach_gen_arr(or_arr);
	return (ceu);
}

void	destroy_ceu(void *ceu)
{
	if (!ceu)
		return ;
	destroy_void_arr((void **)((t_ceu *)ceu)->ir_arr, destroy_in_redir);
	destroy_void_arr((void **)((t_ceu *)ceu)->or_arr, destroy_out_redir);
	destroy_void_arr((void **)((t_ceu *)ceu)->argv, free);
	free(ceu);
}
