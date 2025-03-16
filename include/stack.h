#ifndef STACK_H
# define STACK_H
# include "generic_array.h"

typedef struct s_generic_array	t_stack;

t_stack	*create_stack(void);
void	destroy_stack(t_stack *s, void (del_func)(void *));
int		stack_push(t_stack *s, void *entry, void *(*dup_func)(void *));
void	*stack_top(t_stack *s);
int		stack_pop(t_stack *s, void (*destroy_func)(void *));
#endif
