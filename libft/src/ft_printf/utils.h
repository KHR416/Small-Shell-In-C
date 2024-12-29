/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:56:07 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/14 23:30:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stddef.h>
# include <unistd.h>
# define LOWER_CASE 0
# define UPPER_CASE 1

ssize_t	putstrn(const char *str, size_t n);
ssize_t	my_putchar(unsigned char c);
ssize_t	my_putnbr(int i);
ssize_t	my_putptr(void *ptr);
ssize_t	my_putstr(const char *str);
ssize_t	my_putunbr(unsigned int u);
ssize_t	my_putunbr_hex(size_t x, int case_flag);
#endif