/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:54:52 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/21 17:01:57 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include "generic_array.h"

typedef struct s_generic_array	t_stack;

t_stack	*create_stack(void);
void	destroy_stack(t_stack *s, void (del_func)(void *));
int		stack_push(t_stack *s, void *entry);
void	*stack_top(t_stack *s);
int		stack_pop(t_stack *s, void (*destroy_func)(void *));
#endif
