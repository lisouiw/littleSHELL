/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 06:28:22 by ltran             #+#    #+#             */
/*   Updated: 2017/09/05 14:33:36 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_env **env)
{
	t_env		*tmp;

	while (*env != NULL)
	{
		tmp = (*env)->next;
		free((*env)->name);
		free((*env)->ctn);
		free(*env);
		*env = tmp;
	}
}

char	*t_strjoin(char *f, char *s, char *t)
{
	char	*way;
	char	*tmp;

	tmp = ft_strjoin(f, s);
	way = ft_strjoin(tmp, t);
	free(tmp);
	return (way);
}

void	double_char(char **ar, int i)
{
	while (ar[++i])
		ft_putendl(ar[i]);
}

void	free_tab(char **array)
{
	int		i;

	if (array)
	{
		i = -1;
		while (array[++i])
		{
			ft_strdel(&array[i]);
			free(array[i]);
		}
		free(array);
	}
}

void	double_char_c(char **ar, int i, char c)
{
	while (ar[++i])
	{
		ft_putstr(ar[i]);
		ft_putchar(c);
	}
	write(1, "\n", 1);
}
