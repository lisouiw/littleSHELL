/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:29:27 by ltran             #+#    #+#             */
/*   Updated: 2017/09/18 14:49:09 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_echo(char **add, char **tmp, char ***cut, t_env **var)
{
	ft_strdel(&(*add));
	ft_strdel(&(*tmp));
	free_tab(&(**cut));
	free_list(&(*var));
}

void		give_chg(char *rd, int *a, t_env **var, int *i)
{
	if ((*var)->ctn != NULL)
		*i = *i + ft_strlen((*var)->ctn);
	while (rd[++(*a)] && rd[*a] != ' ' && rd[*a] != '\t' && rd[*a] != '$'
			&& rd[*a] != 39 && rd[*a] != '"')
		;
	*a = *a - 1;
	*var = (*var)->next;
}

char	*give_end(char *join2, int i)
{
	join2[i] = '\n';
	join2[i + 1] = '\0';
	return (join2);
}

char		*give_echo(t_ec e, int *o, char *rd, t_env *var)
{
	t_ec	s;

	s.i = 0;
	s.a = -1;
	if (!(e.add = (char*)malloc((ft_strlen(rd) + e.len + 2) * sizeof(char))))
		return (NULL);
	while (rd[++s.a])
	{
		if (rd[s.a] == 39 && *o < 2)
			*o = (*o == 0) ? 1 : 0;
		else if (rd[s.a] == '"' && (*o == 0 || *o == 2))
			*o = (*o == 0) ? 2 : 0;
		else if (rd[s.a] == '$' && *o != 1)
		{
			e.add[s.i] = '\0';
			e.add = (var->ctn != NULL) ? cpy(e.add, var->ctn) : e.add;
			give_chg(rd, &s.a, &var, &s.i);
		}
		else if (*o == 0 && (rd[s.a] == ' ' || rd[s.a] == '\t') && s.i > 0 &&
			e.add[s.i - 1] != ' ')
			e.add[s.i++] = ' ';
		else if (*o != 0 || (rd[s.a] != ' ' && rd[s.a] != '\t'))
			e.add[s.i++] = rd[s.a];
	}
	return (give_end(e.add, s.i));
}

void		b_echo_w(char *rd, t_env *env, char *keep, int o)
{
	t_env		*var;
	t_ec		e;

	e.line = "\0";
	e.len = 0;
	e.add = NULL;
	e.cut = strsplit_two_c(rd, '\t', ' ');
	var = var_and_len(e.cut, env, &e.len);
	if ((e.add = give_echo(e, &o, rd, var)) == NULL)
		return ;
	e.tmp = ft_strjoin(keep, e.add);
	if (o == 0)
	{
		e.tmp == NULL ? ft_putstr(e.add) : ft_putstr(e.tmp);
		free_echo(&e.add, &e.tmp, &e.cut, &var);
	}
	else
	{
		o == 1 ? ft_putstr("quote> ") : ft_putstr("dquote> ");
		get_next_line(0, &e.line);
		b_echo_w(e.line, env, (e.tmp == NULL ? e.add : e.tmp), o);
		free_echo(&e.add, &e.tmp, &e.cut, &var);
		if (ft_strcmp(e.line, "\0") != 0)
			ft_strdel(&e.line);
	}
}
