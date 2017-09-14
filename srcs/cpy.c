#include "../minishell.h"

void	*cpy(char *dst, char *src)
{
	int		i;
	int		a;

	a = -1;
	i = 0;
	if (dst != NULL)
		while (dst[++a] != '\0')
			;
	while (src[i] != '\0')
	{
		dst[a] = src[i];
		i++;
		++a;
	}
	dst[a] = '\0';
	return (dst);
}
