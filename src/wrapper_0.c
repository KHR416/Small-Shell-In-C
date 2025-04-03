/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:30:35 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 18:54:06 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ceu.h"

void	*ft_strdup_wrap(void *str)
{
	return (ft_strdup(str));
}

void	destroy_in_redir_wrap(void *in_redir)
{
	destroy_in_redir(in_redir);
}

void	destroy_out_redir_wrap(void *out_redir)
{
	destroy_out_redir(out_redir);
}

void	destroy_ceu_wrap(void *ceu)
{
	destroy_ceu(ceu);
}
