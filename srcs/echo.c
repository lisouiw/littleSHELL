/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:29:27 by ltran             #+#    #+#             */
/*   Updated: 2017/09/14 16:24:49 by ltran            ###   ########.fr       */
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

/*
void	give_chg(char *rd, int *a, t_env **var, char **join, int *i)
{
	if ((*var)->ctn != NULL)
	{
		*join = cpy(*join, (*var)->ctn);
	//	printf("join=|%s|\n", *join);
		printf("A = %i\n",*a);
		while (rd[++(*a)] && rd[*a] != ' ' && rd[*a] != '\t' && rd[*a] != '$'
			&& rd[*a] != 39 && rd[*a] != '"')
				printf("rd|%c| && |%c|\n", rd[*a - 1], rd[*a]);
		*a = *a - 1;
		printf("A=$%i\n", *a);
		*i = *i + ft_strlen((*var)->ctn);
	}
	*var = (*var)->next;
}

char	*give_echo(char *join2, int *o, char *rd, int i, t_env *env, char **cut)
{
	int		a;
	t_env	*var;
	int		x;

	x = 0;
	var = NULL;
	while (cut[++x])
		var = give_var(cut[x], env, var);
	a = -1;
	if (!(join2 = (char*)malloc((ft_strlen(rd) + 1000) * sizeof(char))))
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
		else if ((rd[a] == ' ' || rd[a] == '\t') && *o != 0)
			join2[i++] = rd[a];
		else if ((rd[a] == '"' && *o == 1) || (rd[a] == 39 && *o == 2))
			join2[i++] = rd[a];
		else if ((rd[a] == ' ' || rd[a] == '\t') && join2[i - 1] != ' '
				&& *o == 0)
			join2[i++] = ' ';
	}
	join2[i] = '\n';
	join2[i + 1] = '\0';
	printf("$%s\n", join2);
	return (join2);
}
*/


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

t_env	*give_var(char *cut, t_env *env, t_env *var, int i)
{
	t_env	*tmp;
	int		n;

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
			n = (ft_strchr(&cut[i + 1], '$')) == NULL ? ft_strlen(&cut[i + 1]) :
				ft_strlen(&cut[i + 1]) - ft_strlen(ft_strchr(&cut[i + 1], '$'));
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

t_env	*var_and_len(char **cut, t_env *env, int *len)
{
	int		i;
	t_env	*var;
	t_env	*tmp;

	i = 0;
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
/*
char	*give_echo(char *join2, int *o, char *rd, int i, t_env *var)
{
	int		a;

	a = -1;
	if (!(join2 = (char*)malloc((ft_strlen(rd) + 1000) * sizeof(char))))
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
		else if ((rd[a] == ' ' || rd[a] == '\t') && *o != 0)
			join2[i++] = rd[a];
		else if ((rd[a] == '"' && *o == 1) || (rd[a] == 39 && *o == 2))
			join2[i++] = rd[a];
		else if ((rd[a] == ' ' || rd[a] == '\t') && join2[i - 1] != ' '
				&& *o == 0)
			join2[i++] = ' ';
	}
	join2[i] = '\n';
	join2[i + 1] = '\0';
//	printf("$%s\n", join2);
	return (join2);
}*/

/*
void	rec_echo(char *join, int o, char *rd, t_env *env, char **cut)
{
	char		*line;
	char		*tmp;
	char		*join2;

	line = "\0";
	join2 = NULL;
	if ((join2 = give_echo(join2, &o, rd, 0, env, cut)) == NULL)
		return ;
//	printf("O = %s\n", join2);
	tmp = ft_strjoin(join, join2);
	if (o == 0)
	{
		tmp == NULL ? ft_putstr(join2) : ft_putstr(tmp);
		ft_strdel(&join2);
		ft_strdel(&tmp);
	}
	else
	{
		o == 1 ? ft_putstr("quote> ") : ft_putstr("dquote> ");
		get_next_line(0, &line);
		cut = strsplit_two_c(line, ' ', '\t');
		b_echo_w((tmp == NULL ? join2 : tmp), o, line, env, cut);
		ft_strdel(&join2);
		ft_strdel(&tmp);
		if (ft_strcmp(line, "\0") != 0)
			ft_strdel(&line);
	}
}
*/

void	b_echo_w(char *rd, t_env *env, char **cut)
{
	t_env	*var;
	int		len;
	int		o;
	char	*line;

	len = 0;
	cut = strsplit_two_c((cut == NULL ? rd : line), '\t', ' ');
	var = var_and_len(cut, env, &len);
		give_echo();
		if (o == 1 || o == 2)
		{
			o == 1 ? ft_putstr("quote> ") : ft_putstr("dquote> ");
			get_next_line(0, &line);
		}
		//free
	}
/*	while (var != NULL)
	{
		if (var->ctn == NULL)
			printf("INVALIDE\n");
		else
			printf("%s\n", var->ctn);
		var = var->next;
	}*/
//	give_echo();
}
/*
void	b_echo(char **cut, t_env *env)
{
	t_env	*var;
	int		i;
	int		y;
	int		a;

	i = 0;
	var = NULL;
	while (cut[++i])
		var = give_var(cut[i], env, var, -1);
	i = 0;
	while (cut[++i] && (y = -1))
	{
		while (cut[i][++y])
		{
			if (a == 2)
			{
				write (1, " " , 1);
				a = 0;
			}
			if (cut[i][y] != '$')
			{
				a = 1;
				write (1, &cut[i][y] , 1);
			}
			else
			{
				var->ctn == NULL ? 0 : ft_putstr(var->ctn);
				a = (var->ctn == NULL) ? a : 1;
				while (cut[i][y + 1] && cut[i][y + 1] != '$')
					++y;
				var = var->next;
			}
		}
		a = (a == 1) ? 2 : 0;
	}
	write (1, "\n", 1);
//	free_list(&var);
}
*/
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
