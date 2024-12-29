/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:24:49 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/23 16:21:57 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

ssize_t	gnl_get(int msg, int fd, t_buf_vari *buf_va, t_new_line *new_line)
{
	size_t	len;

	if (msg == NEW_BUFFER)
	{
		buf_va->read_bytes = read(fd, buf_va->buf, BUFFER_SIZE);
		if (buf_va->read_bytes < 0)
			return (FAIL);
		if (buf_va->read_bytes == 0)
			return (buf_va->eob = 1, GNL_EOF);
		buf_va->buf[buf_va->read_bytes] = '\0';
		return (buf_va->eob = 0, buf_va->st_idx = 0, SUCCESS);
	}
	else if (msg == LINE_LEN)
	{
		len = 0;
		while (buf_va->st_idx + ++len < (size_t)buf_va->read_bytes)
			if (buf_va->buf[buf_va->st_idx + len - 1] == '\n')
				break ;
		return (len);
	}
	else if (msg == EXTRACTED_NEW_LINE)
		return (gnl_extract_new_line(fd, buf_va, new_line));
	else if (msg == NEW_LINE)
		return (gnl_get_new_line(buf_va, new_line));
	return (FAIL);
}

char	*gnl_alloc_cpy(char *dest, size_t size, const char *src, size_t len)
{
	char	*result;

	if (dest)
		result = dest;
	else
	{
		result = (char *)malloc(size);
		if (!result)
			return (NULL);
	}
	result[len] = '\0';
	while (len--)
		result[len] = src[len];
	return (result);
}

int	gnl_enl_helper(int fd, t_buf_vari *b_v, t_new_line *nl)
{
	char	*temp;
	size_t	len_ad;

	gnl_get(NEW_BUFFER, fd, b_v, NULL);
	if (b_v->read_bytes < 0)
		return (FAIL);
	if (b_v->read_bytes == 0)
		return (GNL_EOF);
	len_ad = (size_t)gnl_get(LINE_LEN, fd, b_v, NULL);
	if (nl->cap < nl->len + len_ad)
	{
		nl->cap <<= 1;
		temp = gnl_alloc_cpy(NULL, nl->cap + 1, nl->str, nl->len);
		if (!temp)
			return (FAIL);
		free(nl->str);
		nl->str = temp;
	}
	gnl_alloc_cpy(nl->str + nl->len, 0, b_v->buf, len_ad);
	nl->len += len_ad;
	b_v->st_idx += len_ad;
	if (b_v->st_idx >= (size_t)b_v->read_bytes)
		b_v->eob = 1;
	return (SUCCESS);
}

int	gnl_extract_new_line(int fd, t_buf_vari *b_v, t_new_line *nl)
{
	char	*temp;
	int		helper_value;

	nl->cap = BUFFER_SIZE << 1;
	nl->str = gnl_alloc_cpy(NULL, nl->cap + 1, b_v->buf + b_v->st_idx, nl->len);
	if (!nl->str)
		return (FAIL);
	b_v->eob = 1;
	while (b_v->eob)
	{
		helper_value = gnl_enl_helper(fd, b_v, nl);
		if (helper_value == FAIL)
			return (FAIL);
		if (helper_value == GNL_EOF || b_v->buf[b_v->st_idx - 1] == '\n')
			break ;
	}
	temp = gnl_alloc_cpy(NULL, nl->len + 1, nl->str, nl->len);
	if (!temp)
		return (FAIL);
	free(nl->str);
	nl->str = temp;
	return (SUCCESS);
}

int	gnl_get_new_line(t_buf_vari *b_v, t_new_line *nl)
{
	nl->str = gnl_alloc_cpy(NULL, nl->len + 1, b_v->buf + b_v->st_idx, nl->len);
	if (!nl->str)
		return (FAIL);
	b_v->st_idx += nl->len;
	if (b_v->st_idx >= (size_t)b_v->read_bytes)
		b_v->eob = 1;
	return (SUCCESS);
}
