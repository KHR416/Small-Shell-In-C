/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:51:50 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/23 19:50:12 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef SUCCESS
#  define SUCCESS 0
# endif
# ifndef FAIL
#  define FAIL 1
# endif
# ifndef GNL_EOF
#  define GNL_EOF -1
# endif
# ifndef NEW_BUFFER
// the message for `get_next_line`
#  define NEW_BUFFER 0
# endif
# ifndef LINE_LEN
// the message for `get_next_line`
#  define LINE_LEN 1
# endif
# ifndef EXTRACTED_NEW_LINE
// the message for `get_next_line`
#  define EXTRACTED_NEW_LINE 2
# endif
# ifndef NEW_LINE
// the message for `get_next_line`
#  define NEW_LINE 3
# endif
# include <unistd.h>

// `s_buf_vari` is the struct that contains variable for buffer.
// `eob` means end of buffer.
// `st_idx` means start index.
// `buf` means the buffer.
typedef struct s_buf_vari
{
	int		eob;
	ssize_t	read_bytes;
	size_t	st_idx;
	char	buf[BUFFER_SIZE + 1];
}	t_buf_vari;
// `s_new_line` is the strcut that contains variable for new line.
// `len` means the length of `str`.
// `cap` means the capacity, the maximum lenght which `str` can hold.
// `str` means the string.
typedef struct s_new_line
{
	size_t	len;
	size_t	cap;
	char	*str;
}	t_new_line;

char	*get_next_line(int fd);
// The generic function for `get_next_line`
// If msg is `NEW_BUFFER`, it will read the `fd` and will set `buf_va`
// and returns SUCCESS or GNL_EOF when meets EOF.
// It returns FAIL when error occured.
ssize_t	gnl_get(int msg, int fd, t_buf_vari *buf_va, t_new_line *new_line);
// The function that copies from src `len` bytes to dest and return `dest`.
// It gurantees dest will be null terminated.
// If `dest` is NULL, it allocates `size` bytes, copies froms src `len` bytes
// and returns first a pointer to the allocated memory.
// If allocation failes, It returns NULL
char	*gnl_alloc_cpy(char *dest, size_t size, const char *src, size_t len);
// The function that reads new buffer and concatenates it.
// It returns SUCCESS or GNL_EOF when meets EOF.
// If error occured, it returns FAIL.
int		gnl_enl_helper(int fd, t_buf_vari *b_v, t_new_line *nl);
// The function that set nl.str to extracted new line.
// It returns SUCCESS or FAIL when error occured.
int		gnl_extract_new_line(int fd, t_buf_vari *b_v, t_new_line *nl);
int		gnl_get_new_line(t_buf_vari *b_v, t_new_line *nl);
#endif