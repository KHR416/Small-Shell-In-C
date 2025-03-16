/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:05:11 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/15 20:49:30 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H
# include <unistd.h>
# include "ceu.h"
# include "pipe_seg.h"

typedef struct s_ast_node	t_ast;
// typedef enum e_logical_operator_type
// {
// 	LO_NONE = 0,
// 	LO_AND = 1 << 0,
// 	LO_OR = 1 << 1,
// }	t_logic_op_type;

// typedef struct s_logical_expression
// {
// 	t_logic_op_type	type;
// 	t_ast			*left;
// 	t_ast			*right;
// }	t_logic_expr;

typedef enum e_node_type
{
	NODE_NONE = 0,
	NODE_CEU = (1 << 0),
	NODE_PIPE = (1 << 1),
	NODE_OR = (1 << 2),
	NODE_AND = (1 << 3),
	NODE_PARANTHESIS_OPEN = (1 << 4),
}	t_node_type;

// typedef struct s_op_data
// {
// 	t_ceu	*left;
// 	t_ceu	*right;
// }	t_op_data;

typedef union u_ast_node_data
{
	t_ast	*ast;
	t_ceu	*ceu;
}	t_ast_node_data;
typedef struct s_ast_node
{
	t_node_type		type;
	t_ast_node_data	data[2];	// data[0] <- left; data[1] <- right
}	t_ast;

t_ast	*create_ast_node(void);
void	destroy_ast_node(t_ast *node);
void	destroy_ast(t_ast *root);
t_ast	*analyzer(t_token_stream *ts);
int		ast_traversal(t_ast *node, t_msvar *msvar, int pipe_flag);

t_node_type	ast_node_type(t_ast *node);
void 		ast_attach_binary_branch (t_ast *root , t_ast *left_node , t_ast *right_node);
void 		ast_set_type (t_ast *node , t_node_type node_type);
void 		ast_set_data (t_ast *node , char *data );
void 		ast_delete (t_ast *node );
#endif