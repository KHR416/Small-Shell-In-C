/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:05:11 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 23:32:19 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H
# include <unistd.h>
# include "ceu.h"

typedef struct s_ast_node	t_ast;
typedef enum e_node_type
{
	NODE_NONE = 0,
	NODE_CEU = (1 << 0),
	NODE_PIPE = (1 << 1),
	NODE_OR = (1 << 2),
	NODE_AND = (1 << 3),
	NODE_PARANTHESIS_OPEN = (1 << 4),
}	t_node_type;

typedef union u_ast_node_data
{
	t_ast	*ast;
	t_ceu	*ceu;
}	t_ast_node_data;
typedef struct s_ast_node
{
	t_node_type		type;
	t_ast_node_data	data[2];
}	t_ast;

t_ast		*create_ast_node(void);
void		destroy_ast_node(t_ast *node);
void		destroy_ast(t_ast *root);
t_ast		*ast_analyzer(t_token_stream *ts);
int			ast_traversal(t_ast *node, t_msvar *msvar, int pipe_flag);
int			is_operator_node(t_node_type type);
int			op_cmp(t_node_type type1, t_node_type type2);
int			cmp_not_same(t_node_type type, t_node_type type_open);
int			execute_ceu(t_ast *node, t_msvar *msvar, int pipe_flag);
int			create_pipe(int pipefd[2]);
pid_t		create_child(void);

#endif