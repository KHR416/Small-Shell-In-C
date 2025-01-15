/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:05:11 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/14 00:01:46 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

typedef enum e_input_redirection_type
{
	NONE = 0,
	DEFAULT = (1 << 0),
	HERE_DOC = (1 << 1),
}	t_in_redir_type;

typedef struct s_input_redirection
{
	t_in_redir_type	type;
	char			*name;
}	t_in_redir;

typedef enum e_output_redirection_type
{
	NONE = 0,
	DEFAULT = (1 << 0),
	APPEND = (1 << 1),
}	t_out_redir_type;

typedef struct s_output_redirection
{
	t_out_redir_type	type;
	char				*name;
}	t_out_redir;

// Command excution unit
// `ir_arr` and `or_arr` is none-type terminated
// If there are no commands, like `<infile >outfile`, argv will be set to `NULL`
typedef struct s_commaned_excution_unit
{
	t_in_redir	*ir_arr;
	t_out_redir	*or_arr;
	char		**argv;
}	t_ceu;

typedef struct s_pipeline_segment
{
	t_ceu	*ceu_arr;
	size_t	n_ceu;
}	t_pipe_seg;

typedef struct s_ast_node	t_ast;

/*
typedef enum e_logical_operator_type
{
	NONE = 0,
	AND = 1 << 0,
	OR = 1 << 1,
}	t_logic_op_type;

typedef struct s_logical_expression
{
	t_logic_op_type	type;
	t_ast			*term[2];
}	t_logic_expr;
*/

typedef enum e_node_type
{
	NONE					= 0,
	COMMAND_EXCUTION_UNIT	= (1 << 0),
	PIPE_SEGMENT			= (1 << 1),
	// LOGICAL_EXPRESSION 	= (1 << 2),
}	t_node_type;

typedef union u_ast_node_data
{
	t_ceu		*ceu;
	t_pipe_seg	*pipe_seg;
	// t_logic_expr	*logic_expr;
}	t_ast_node_data;

struct s_ast_node
{
	t_node_type		type;
	t_ast_node_data	*data;
};

typedef enum e_quote_mode
{
	WITHOUT_QUOTE = 0,
	SINGLE_QUOTE = (1 << 0),
	DOUBLE_QUOTE = (1 << 1),
}	t_quote_mode;

t_node_type	ast_node_type(t_ast *node);
void 		ast_attach_binary_branch (t_ast *root , t_ast *left_node , t_ast *right_node);
void 		ast_set_type (t_ast *node , t_node_type node_type);
void 		ast_set_data (t_ast *node , char *data );
void 		ast_delete (t_ast *node );
#endif