/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/06 21:02:31 by wchoe            ###   ########.fr       */
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

int	print_in_redir(t_in_redir *ir)
{
	#ifdef DEBUG
	if (!ir)
		return (FAILURE);
	if (ir->type == IR_DEFAULT)
		fprintf(stderr, "%s", "<");
	else
		fprintf(stderr, "%s", "<<");
	fprintf(stderr, "%s\n", ir->name);
	return (SUCCESS);
	#endif
}

int	print_ir_list(t_list *ir)
{
	while (ir)
	{
		print_in_redir(ir->content);
		ir = ir->next;
	}
	return (SUCCESS);
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

int	print_out_redir(t_out_redir *or)
{
	#ifdef DEBUG
	if (!or)
		return (FAILURE);
	if (or->type == OR_DEFAULT)
		fprintf(stderr, "%s", ">");
	else
		fprintf(stderr, "%s", ">>");
	fprintf(stderr, "%s\n", or->name);
	return (SUCCESS);
	#endif
}

int	print_or_list(t_list *or)
{
	while (or)
	{
		print_out_redir(or->content);
		or = or->next;
	}
	return (SUCCESS);
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

int	print_argv(char **argv)
{
	#ifdef DEBUG
	if (!argv)
		return (FAILURE);
	for (char **it = argv; *it; ++it)
		fprintf(stderr, "argv[%zu]: %s\n", it - argv, *it);
	return (SUCCESS);
	#endif
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

t_ceu	*create_ceu(t_token *iter_begin, t_token *iter_end)
{
	t_ceu	*ceu;
	t_list	*argv_list;
	void	*temp;

	if (iter_begin == iter_end)
	{
		print_error_unexpected_token(iter_begin->type);
		return (NULL);
	}
	ceu = ft_calloc(1, sizeof(t_ceu));
	if (!ceu)
		return (NULL);
	argv_list = NULL;
	while (iter_begin < iter_end)
	{
		if (iter_begin->type == TOKEN_INPUT_REDIRECT)
		{
			if ((++iter_begin)->type != TOKEN_LITERAL)
			{
				print_error_unexpected_token(iter_begin->type);
				destroy_ceu(ceu);
				ft_lstclear(&argv_list, free);
				return (NULL);
			}
			temp = create_in_redir(IR_DEFAULT, iter_begin->data);
			if (!temp || ft_lstpush_back(&ceu->ir_list, temp))
			{
				destroy_ceu(ceu);
				ft_lstclear(&argv_list, free);
				return (NULL);
			}
		}
		else if (iter_begin->type == TOKEN_HERE_DOC)
		{
			if ((++iter_begin)->type != TOKEN_LITERAL)
			{
				print_error_unexpected_token(iter_begin->type);
				destroy_ceu(ceu);
				ft_lstclear(&argv_list, free);
				return (NULL);
			}
			temp = create_in_redir(IR_HERE_DOC, iter_begin->data);
			if (!temp || ft_lstpush_back(&ceu->ir_list, temp))
			{
				destroy_ceu(ceu);
				ft_lstclear(&argv_list, free);
				return (NULL);
			}
		}
		else if (iter_begin->type == TOKEN_OUTPUT_REDIRECT)
		{
			if ((++iter_begin)->type != TOKEN_LITERAL)
			{
				print_error_unexpected_token(iter_begin->type);
				destroy_ceu(ceu);
				ft_lstclear(&argv_list, free);
				return (NULL);
			}
			temp = create_out_redir(OR_DEFAULT, iter_begin->data);
			if (!temp || ft_lstpush_back(&ceu->or_list, temp))
			{
				destroy_ceu(ceu);
				ft_lstclear(&argv_list, free);
				return (NULL);
			}
		}
		else if (iter_begin->type == TOKEN_APPEND_REDIRECT)
		{
			if ((++iter_begin)->type != TOKEN_LITERAL)
			{
				print_error_unexpected_token(iter_begin->type);
				destroy_ceu(ceu);
				ft_lstclear(&argv_list, free);
				return (NULL);
			}
			temp = create_out_redir(OR_APPEND, iter_begin->data);
			if (!temp || ft_lstpush_back(&ceu->or_list, temp))
			{
				destroy_ceu(ceu);
				ft_lstclear(&argv_list, free);
				return (NULL);
			}
		}
		else if (iter_begin->type == TOKEN_LITERAL)
		{
			temp = ft_strdup(iter_begin->data);
			if (!temp || ft_lstpush_back(&argv_list, temp))
			{
				destroy_ceu(ceu);
				ft_lstclear(&argv_list, free);
				return (NULL);
			}
		}
		else
		{
			print_error_unexpected_token(iter_begin->type);
			destroy_ceu(ceu);
			ft_lstclear(&argv_list, free);
			return (NULL);
		}
		++iter_begin;
	}
	ceu->argv = (char **)list_to_arr(argv_list, (void *)ft_strdup);
	if (!ceu->argv)
	{
		destroy_ceu(ceu);
		ft_lstclear(&argv_list, free);
		return (NULL);
	}
	ft_lstclear(&argv_list, free);
	return (ceu);
}

int	print_ceu(t_ceu *ceu)
{
	#ifdef DEBUG
	if (!ceu)
		return (FAILURE);
	if (print_ir_list(ceu->ir_list))
		return (FAILURE);
	if (print_or_list(ceu->or_list))
		return (FAILURE);
	if (print_argv(ceu->argv))
		return (FAILURE);
	return (SUCCESS);
	#endif
}

void	destroy_ceu(void *ceu)
{
	if (!ceu)
		return ;
	ft_lstclear(&((t_ceu *)ceu)->ir_list, destroy_in_redir);
	ft_lstclear(&((t_ceu *)ceu)->or_list, destroy_out_redir);
	destroy_argv(((t_ceu *)ceu)->argv);
	free(ceu);
}
