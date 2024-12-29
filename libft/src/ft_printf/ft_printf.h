/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:32:57 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:53:18 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define SPECIFIER_SET "cspdiuxX%"
# define FLAG_SET "+ #-0"
# include "libft.h"
# include <unistd.h>

typedef struct s_conversion
{
	int		flags[5];
	int		field;
	int		precision;
	char	specifier;
}	t_conversion;
typedef struct s_conv_len
{
	unsigned int	len;
	unsigned int	prefix_len;
	unsigned int	nzero;
	unsigned int	nspace;
}	t_conv_len;

int				has_flag_plus(const int *flags);
int				has_flag_space(const int *flags);
int				has_flag_hash(const int *flags);
int				has_flag_minus(const int *flags);
int				has_flag_zero(const int *flags);
void			init_lens(t_conv_len *lengths);
void			init_conv(t_conversion *conv);
unsigned int	total_len(const t_conv_len lengths);
char			*parse_conversion(const char *format, t_conversion *conv);
ssize_t			print_conversion_c(const t_conversion conv, unsigned char c);
ssize_t			print_conversion_s(const t_conversion conv, const char *str);
ssize_t			print_conversion_p(const t_conversion conv, void *ptr);
ssize_t			print_conversion_d(const t_conversion conv, int i);
ssize_t			print_conversion_u(const t_conversion c, unsigned int u);
ssize_t			print_conversion_x(const t_conversion conv, unsigned int x, \
	int case_flag);
#endif