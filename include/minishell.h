/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:00:14 by wchoe             #+#    #+#             */
/*   Updated: 2024/12/29 23:01:42 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif	// BUFFER_SIZE

char	*ms_getcwd(void);
#endif	// MINISHELL_H