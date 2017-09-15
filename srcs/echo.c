/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:29:27 by ltran             #+#    #+#             */
/*   Updated: 2017/09/15 16:52:42 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ecriture_info(t_env *lst)
{
	if (!(lst))
		return ;
	while (lst->next != NULL)
	{
		ft_putstr(lst->name);
		ft_putendl(lst->ctn);
		lst = lst->next;
	}
	ft_putstr(lst->name);
	ft_putendl(lst->ctn);
}

t_env	*add_var(char *ctn, t_env *var)
{
	t_env	*new;
	t_env	*tmp;

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
int		exist(char c)
{
	if (c == '=')
		return (1);
	return (0);
}


size_t	give_len(char *cut, size_t len, int i)
{
	while (cut[++i] && cut[i] != '$' && cut[i] != 39 && cut[i] != '"')
		++len;
	return (len);
}

t_env	*give_var(char *cut, t_env *env, t_env *var, int i)
{
	t_env	*tmp;
	int		n;
	int		c;

	c = 0;
	while (cut[++i] && (tmp = env))
	{
		while(cut[i] && cut[i] != '$')
			++i;
		if (cut[i] != '$')
			return (var);
		if (cut[i + 1] == '\0' || cut[i + 1] == '\t' || cut[i + 1] == ' ')
			var = (i == 0 || cut[i - 1] != '$') ? add_var("$", var) : add_var(NULL, var);
		else if (cut[i + 1] != '$')
		{
			n = give_len(&cut[i + 1], 0, -1);
			while (tmp != NULL && (ft_strncmp(&cut[i + 1], tmp->name, n) != 0
						|| (tmp->name[n] && exist(tmp->name[n]) == 0)))
				tmp = tmp->next;
			var = (tmp == NULL) ? add_var(NULL, var) : add_var(tmp->ctn, var);
		}
		else
			var = add_var(NULL, var);
	}
	return (var);
}

t_env	*var_and_len(char **cut, t_env *env, size_t *len)
{
	int		i;
	t_env	*var;
	t_env	*tmp;

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


void	give_chg(char *rd, int *a, t_env **var, char **join, int *i)
{
	if ((*var)->ctn != NULL)
	{
		*join = cpy(*join, (*var)->ctn);
		*i = *i + ft_strlen((*var)->ctn);
	}
	while (rd[++(*a)] && rd[*a] != ' ' && rd[*a] != '\t' && rd[*a] != '$'
			&& rd[*a] != 39 && rd[*a] != '"')
		;
	*a = *a - 1;
	*var = (*var)->next;
}


char	*give_echo(char *join2, int *o, char *rd, size_t len, t_env *var)
{
	int		a;
	int		i;

	i = 0;
	a = -1;
	if (!(join2 = (char*)malloc((ft_strlen(rd) + len + 2) * sizeof(char))))
		return (NULL);
	while (rd[++a])
	{
		if (rd[a] == 39 && *o < 2)
			*o = (*o == 0) ? 1 : 0;
		else if (rd[a] == '"' && (*o == 0 || *o == 2))
			*o = (*o == 0) ? 2 : 0;
		else if (rd[a] == '$')
		{
			join2[i] = '\0';
			give_chg(rd, &a, &var, &join2, &i);
		}
		else if (rd[a] != '"' && rd[a] != 39 && rd[a] != ' ' && rd[a] != '\t')
			join2[i++] = rd[a];
		else if ((rd[a] == ' ' || rd[a] == '\t') && *o != 0 && *o != 3)
			join2[i++] = rd[a];
		else if ((rd[a] == '"' && *o == 1) || (rd[a] == 39 && *o == 2))
			join2[i++] = rd[a];
		else if ((rd[a] == ' ' || rd[a] == '\t') && i > 0 && join2[i - 1] != ' '
				&& (*o == 0 || *o == 3))
			join2[i++] = ' ';
	}
	join2[i] = '\n';
	join2[i + 1] = '\0';
	return (join2);
}

void	b_echo_w(char *rd, t_env *env, char *keep, int o)
{
	t_env	*var;
	size_t	len;
	char	*add;
	char	*line;
	char	**cut;
	char	*tmp;

	line = "\0";
	len = 0;
	add = NULL;
	cut = strsplit_two_c(rd, '\t', ' ');
	var = var_and_len(cut, env, &len);
	if ((add = give_echo(add, &o, rd, len, var)) == NULL)
		return ;
	tmp = ft_strjoin(keep, add);
	if (o == 0)
	{
		tmp == NULL ? ft_putstr(add) : ft_putstr(tmp);
	//	ft_strdel(&add);
	//	ft_strdel(&tmp);
	//	free_tab(cut);
	}
	else
	{
		o == 1 ? ft_putstr("quote> ") : ft_putstr("dquote> ");
		get_next_line(0, &line);
	//	free_tab(cut);
		b_echo_w(line, env, (tmp == NULL ? add : tmp), o);
	//	ft_strdel(&add);
	//	ft_strdel(&tmp);
	//	if (ft_strcmp(line, "\0") != 0)
	//		ft_strdel(&line);
	}
}

/*	while (var != NULL)
	{
		if (var->ctn != NULL)
			ft_putendl(var->ctn);
		else
			ft_putendl("INVALIDE");
		var = var->next;
	}
	exit(0);*/

void	*no_b_spc(char *s)
{
	int		i;
	char	*b;

	i = 0;
	b = (char*)s;
	while ((b[i] == ' ' || b[i] == '\t') && b[i] != '\0')
		++i;
	i += 4;
	while ((b[i] == ' ' || b[i] == '\t') && b[i] != '\0')
		++i;
	return (&b[i]);
}
