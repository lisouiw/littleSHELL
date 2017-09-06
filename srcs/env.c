/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:13:45 by ltran             #+#    #+#             */
/*   Updated: 2017/09/06 18:41:31 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_elem(t_env *tmp)
{
	ft_strdel(&tmp->name);
	ft_strdel(&tmp->ctn);
	free(tmp);
}

void	b_export(char *cut, t_env **env)
{
	t_env	*tmp;
	t_env	*kp;

	tmp = NULL;
	kp = *env;
	if (ft_strchr(cut, '='))
	{
		tmp = add_env(cut, NULL, ft_strlen(ft_strchr(cut, '=')),
				ft_strlen(cut));
		while (kp && kp->next != NULL && ft_strcmp(kp->name, tmp->name) != 0)
			kp = kp->next;
		if (kp && ft_strcmp(kp->name, tmp->name) == 0)
		{
			free(kp->name);
			kp->name = ft_strdup(tmp->name);
			free(kp->ctn);
			kp->ctn = ft_strdup(tmp->ctn);
		}
		else
		{
			*env = add_env(cut, *env, ft_strlen(ft_strchr(cut, '=')),
					ft_strlen(cut));
		}
		free_elem(tmp);
	}
}

void	b_unset(char **cut, t_env **env, int i)
{
	t_env	*kp;
	t_env	*sup;

	while (cut[++i] && (kp = *env))
	{
		if (ft_strcmp(kp->name, cut[i]) == 61)
		{
			free_elem(kp);
			(*env) = (*env)->next;
		}
		else
		{
			while (kp && kp->next != NULL)
			{
				if (ft_strcmp(kp->next->name, cut[i]) == 61)
				{
					sup = kp->next;
					kp->next = kp->next->next;
					free_elem(sup);
					break ;
				}
				kp = kp->next;
			}
		}
	}
}

t_env	*add_env(char *environ, t_env *env, size_t one, size_t all)
{
	t_env	*new;
	t_env	*tmp;

	new = (t_env*)malloc(sizeof(t_env));
	new->name = ft_strsub(environ, 0, all - one + 1);
	new->ctn = ft_strsub(environ, all - one + 1, one - 1);
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
