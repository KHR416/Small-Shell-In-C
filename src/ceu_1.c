/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 18:51:34 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ceu.h"
#include "generic_array.h"
#include "wrapper.h"

t_ceu	*create_ceu(void)
{
	return (ft_calloc(1, sizeof(t_ceu)));
}

void	destroy_ceu(t_ceu *ceu)
{
	if (!ceu)
		return ;
	destroy_void_arr((void **)ceu->ir_arr, destroy_in_redir_wrap);
	destroy_void_arr((void **)ceu->or_arr, destroy_out_redir_wrap);
	destroy_void_arr((void **)ceu->argv, free);
	free(ceu);
}
