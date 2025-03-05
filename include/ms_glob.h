/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:31:29 by chakim            #+#    #+#             */
/*   Updated: 2025/03/05 13:17:59 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_GLOB_H
# define MS_GLOB_H

# include <stdlib.h>
# include <dirent.h>
# include "libft.h"

int		ms_fnmatch(char **pattern, char *string);
char	**ms_glob(char **pattern);

#endif