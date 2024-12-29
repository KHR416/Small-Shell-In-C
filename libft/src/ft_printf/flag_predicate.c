/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_predicate_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:17:32 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:52:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	has_flag_plus(const int *flags)
{
	return (*flags);
}

int	has_flag_space(const int *flags)
{
	return (flags[1]);
}

int	has_flag_hash(const int *flags)
{
	return (flags[2]);
}

int	has_flag_minus(const int *flags)
{
	return (flags[3]);
}

int	has_flag_zero(const int *flags)
{
	return (flags[4]);
}
