/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:31:29 by chakim            #+#    #+#             */
/*   Updated: 2025/03/07 17:52:11 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_GLOB_H
# define MS_GLOB_H

# include <stdlib.h>
# include <dirent.h>
# include "libft.h"

char	**ms_glob(char **patterns);
int		ms_fnmatch(char **patterns, char *string);

#endif