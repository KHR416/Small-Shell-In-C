/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/07 23:08:40 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CEU_H
# define CEU_H
# include "token.h"
# include "minishell.h"
# include "libft.h"

typedef enum e_input_redirection_type
{
	IR_NONE = 0,
	IR_DEFAULT = (1 << 0),
	IR_HERE_DOC = (1 << 1),
}	t_in_redir_type;

typedef struct s_input_redirection
{
	t_in_redir_type	type;
	char			*name;
}	t_in_redir;

typedef enum e_output_redirection_type
{
	OR_NONE = 0,
	OR_DEFAULT = (1 << 0),
	OR_APPEND = (1 << 1),
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
	t_in_redir	**ir_arr;
	t_out_redir	**or_arr;
	char	**argv;
}	t_ceu;

t_in_redir	*create_in_redir(t_in_redir_type type, char *data);
t_out_redir	*create_out_redir(t_out_redir_type type, char *data);
void		**list_to_arr(t_list *lst, void *(*copy)());
void		destroy_in_redir(void *ir_arr);
void		destroy_out_redir(void *or_arr);
void		destroy_argv(char **argv);
void		destroy_ceu(void *ceu);
t_ceu		*create_ceu(t_token *iter_begin, t_token *iter_end);
int			ceu_exec(t_ceu *ceu, t_msvar *msvar, int flag_pipe_seg);

# ifdef DEBUG

int			print_in_redir(t_in_redir *ir);
int			print_out_redir(t_out_redir *or);
int			print_ir_arr(t_in_redir **ir_arr);
int			print_or_arr(t_out_redir **or_arr);
int			print_argv(char **argv);
int			print_ceu(t_ceu *ceu);
# endif	// DEBUG
#endif	// CEU_H
