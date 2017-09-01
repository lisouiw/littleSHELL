/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:13:45 by ltran             #+#    #+#             */
/*   Updated: 2017/09/01 16:11:33 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_env(char *environ, t_env *env, size_t one, size_t all)
{
	t_env	*new;
	t_env	*tmp;

	new = (t_env*)malloc(sizeof(t_env));
	new->name = ft_strsub(environ, 0, all - one + 1);
	new->ctn = ft_strsub(environ, all - one + 1, one -1);
	new->next = NULL;
	if (!(env))
		return (new);
	tmp = env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (env);
}

t_env	*give_env(t_env *env)
{
	int				i;
	extern char		**environ;

	i = -1;
	while (environ[++i])
	{
		env = add_env(environ[i], env, ft_strlen(ft_strchr(environ[i], '=')),
				ft_strlen(environ[i]));
	}
	return (env);
}
