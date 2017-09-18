/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:34:13 by ltran             #+#    #+#             */
/*   Updated: 2017/09/18 15:54:36 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env		*add_var(char *ctn, t_env *var)
{
	t_env		*new;
	t_env		*tmp;

	new = (t_env*)malloc(sizeof(t_env));
	new->name = NULL;
	new->ctn = (ctn == NULL) ? NULL : ft_strdup(ctn);
	new->next = NULL;
	if (!(var))
		return (new);
	tmp = var;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (var);
}

size_t		give_len(char *cut, size_t len, int i)
{
	while (cut[++i] && cut[i] != '$' && cut[i] != 39 && cut[i] != '"')
		++len;
	return (len);
}

int			give_i(char *cut, int i, int *c)
{
	while (cut[i] && (cut[i] != '$' || *c == 1))
	{
		if (cut[i] == 39 && *c < 2)
			*c = (*c == 0) ? 1 : 0;
		else if (cut[i] == '"' && (*c == 0 || *c == 2))
			*c = (*c == 0) ? 2 : 0;
		++i;
	}
	return (i);
}

t_env		*give_var(char *cut, t_env *env, t_env *var, int i)
{
	t_env		*tmp;
	int			n;
	int			c;

	c = 0;
	while (cut[++i] && (tmp = env))
	{
		i = give_i(cut, i, &c);
		if (cut[i] == '$' && (cut[i + 1] == '\0' || cut[i + 1] == '\t' ||
				cut[i + 1] == ' ' || cut[i + 1] == '"'))
			var = (i == 0 || cut[i - 1] != '$') ? add_var("$", var) :
				add_var(NULL, var);
		else if (cut[i] == '$' && cut[i + 1] != '$')
		{
			n = give_len(&cut[i + 1], 0, -1);
			while (tmp != NULL && (ft_strncmp(&cut[i + 1], tmp->name, n) != 0
						|| (tmp->name[n] && tmp->name[n] != '=')))
				tmp = tmp->next;
			var = (tmp == NULL) ? add_var(NULL, var) : add_var(tmp->ctn, var);
		}
		else if (cut[i] == '$')
			var = add_var(NULL, var);
	}
	return (var);
}

t_env		*var_and_len(char **cut, t_env *env, size_t *len)
{
	int			i;
	t_env		*var;
	t_env		*tmp;

	i = -1;
	var = NULL;
	while (cut[++i])
		var = give_var(cut[i], env, var, -1);
	tmp = var;
	while (tmp != NULL)
	{
		if (tmp->ctn != NULL)
			*len = *len + ft_strlen(tmp->ctn);
		tmp = tmp->next;
	}
	return (var);
}
