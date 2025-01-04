/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_realloc.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>	   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/03 15:37:24 by wchoe			 #+#	#+#			 */
/*   Updated: 2025/01/03 17:07:53 by wchoe			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
ft_realloc - Reallocate a memory block with a new size.

DESCRIPTION
This function allocates a new memory block of size `new_size` and copies
the data from the existing memory block pointed to by `ptr`, which has a size of
`old_size`, into the newly allocated block. After successfully copying the data,
the original memory block is freed. If `ptr` is `NULL`, `old_size` is ignored
and the function behaves like `malloc(new_size)`.

RETURN
On success, this function returns a pointer to the newly allocated memory block.
On failure, it returns `NULL` and the original memory block remains unchanged
(if `ptr` was not `NULL`).

NOTES
To prevent memory leaks, it is recommended to store the return value in a
temporary variable before assigning it back to the original pointer.
If `ptr` is `NULL`, the function behaves exactly like `malloc(new_size)`.

EXAMPLE
```c
int main(void)
{
	// Initial allocation
	char *str = strdup("Hello world!");
	if (!str)
		return (EXIT_FAILURE);

	// Reallocate memory to a larger size
	char *temp = ft_realloc(str, strlen(str) + 1, 100);
	if (!temp)
	{
		// Handle reallocation failure
		free(str);
		return (EXIT_FAILURE);
	}
	str = temp;

	// Use the reallocated memory
	strcat(str, " This is an extended string.");

	// Cleanup
	free(str);
	return (EXIT_SUCCESS);
}
```
*/
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	new = malloc(new_size);
	if (!new)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			ft_memcpy(new, ptr, old_size);
		else
			ft_memcpy(new, ptr, new_size);
	}
	free(ptr);
	return (new);
}
