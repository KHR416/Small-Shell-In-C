/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:09:08 by chakim            #+#    #+#             */
/*   Updated: 2025/03/30 17:48:02 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H
# include "token.h"
# include "minishell.h"

void	print_banner(void);
void	print_warning_heredoc_eof(char *delimiter);
int		set_temp_file_name(t_buf *buf, size_t n);
int		remove_temp_files(t_msvar *msvar);
int		process_here_doc(t_token_stream *stream, t_msvar *msvar);
int		process_here_doc_redirec(t_msvar *msvar, char **delimeter);

#endif