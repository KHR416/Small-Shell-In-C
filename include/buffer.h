/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:49:22 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/05 19:22:41 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif	// BUFFER_SIZE

typedef struct s_buf
{
	char	*buffer;
	size_t	length;
	size_t	capacity;
}	t_buf;

t_buf	*create_buf(void);
void	destroy_buf(t_buf *buf);
void	clear_buf(t_buf *buf);
int		realloc_buf(t_buf *buf, size_t new_cap);
int		cat_buf(t_buf *buf, char *str);
char	*detach_buf(t_buf *buf);
#endif	// BUFFER_H