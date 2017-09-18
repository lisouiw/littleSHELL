/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:45:56 by ltran             #+#    #+#             */
/*   Updated: 2017/09/18 15:14:25 by ltran            ###   ########.fr       */
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
	else if (array == NULL)
		free(array);
}

int		free_for_exit(char *line, char **cut, t_env *env)
{
	ft_strdel(&line);
	free_tab(cut);
	free_list(&env);
	return (1);
}
