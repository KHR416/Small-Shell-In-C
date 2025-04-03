/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:32:37 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 18:53:38 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H

void	*ft_strdup_wrap(void *str);
void	destroy_in_redir_wrap(void *in_redir);
void	destroy_out_redir_wrap(void *out_redir);
void	destroy_ceu_wrap(void *ceu);
#endif	// WRAPPER_H