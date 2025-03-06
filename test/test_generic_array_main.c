#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic_array.h"

void	*my_strdup(void *str)
{
	return (strdup(str));
}

int	main(void)
{
	t_gen_arr	*arr;
	char		**strs;

	arr = create_gen_arr();
	append_gen_arr(arr, "Hello World!\n", NULL);
	append_gen_arr(arr, "From Uhe Ojisan\n", NULL);
	strs = (char **)arr->data;
	printf("%s%s%s\n", strs[0], strs[1], strs[2]);
	destroy_gen_arr(arr, NULL);

	arr = create_gen_arr();
	append_gen_arr(arr, "Hello World!\n", my_strdup);
	append_gen_arr(arr, "From Uhe Ojisan\n", my_strdup);
	strs = (char **)arr->data;
	printf("%s%s%s\n", strs[0], strs[1], strs[2]);
	destroy_gen_arr(arr, free);

	char	*test_strs[] = {
		"Hi\n",
		"Bye\n",
		NULL
	};
	arr = create_gen_arr();
	cat_gen_arr(arr, (void **)test_strs, NULL);
	append_gen_arr(arr, "NagiNagi\n", NULL);
	strs = (char **)arr->data;
	printf("%s%s%s%s\n", strs[0], strs[1], strs[2], strs[3]);
	destroy_gen_arr(arr, NULL);

	arr = create_gen_arr();
	cat_gen_arr(arr, (void **)test_strs, my_strdup);
	append_gen_arr(arr, "NagiNagi\n", my_strdup);
	strs = (char **)arr->data;
	printf("%s%s%s%s\n", strs[0], strs[1], strs[2], strs[3]);
	destroy_gen_arr(arr, free);
	return (EXIT_SUCCESS);
}
