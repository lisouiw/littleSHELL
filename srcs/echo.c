/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:29:27 by ltran             #+#    #+#             */
/*   Updated: 2017/09/12 19:21:03 by ltran            ###   ########.fr       */
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

char	*give_echo(char *join2, int *o, char *rd, int i)
{
	int		a;

	a = -1;
	if (!(join2 = (char*)malloc((ft_strlen(rd) + 2) * sizeof(char))))
		return (NULL);
	while (rd[++a])
	{
		if (rd[a] == 39 && *o < 2)
			*o = (*o == 0) ? 1 : 0;
		else if (rd[a] == '"' && (*o == 0 || *o == 2))
			*o = (*o == 0) ? 2 : 0;
		else if (rd[a] == '$' && rd[a + 1] != '\t' && rd[a + 1] != ' ')
			;
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
	return (join2);
}

void	b_echo_w(char *join, int o, char *rd)
{
	char		*line;
	char		*tmp;
	char		*join2;

	line = "\0";
	join2 = NULL;
	if ((join2 = give_echo(join2, &o, rd, 0)) == NULL)
		return ;
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
		b_echo_w((tmp == NULL ? join2 : tmp), o, line);
		ft_strdel(&join2);
		ft_strdel(&tmp);
		if (ft_strcmp(line, "\0") != 0)
			ft_strdel(&line);
	}
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

t_env	*give_var(char *cut, t_env *env, t_env *var)
{
	char	*spl;
	char	**dl;

	dl = NULL;
	spl = ft_strchr(cut, '$');
	if (spl == NULL)
		var = add_var(cut, var);
	else if (ft_strlen(cut) != ft_strlen(spl))
	{
		printf("recup\n");
		spl = ft_strsub(cut, 0, ft_strlen(cut) - ft_strlen(spl));
	}
	if (spl != NULL)
		dl = ft_strsplit(spl, '$');
	double_char_c(dl, -1, ' ');
	env = NULL;

	return (var);
}

void	b_echo(char **cut, t_env *env)
{
	t_env	*var;
	int		i;
	int		y;
	int		a;

	i = 0;
	a = 0;
	y = -1;
	var = NULL;
	while (cut[++i])
		var = give_var(cut[i], env, var);
/*	i = 0;
	while (cut[++i] && (y = -1))
	{
		if (a == 1)
		{
			a = 0;
			write (1, " " , 1);
		}
		while (cut[i][++y])
		{
			while ((cut[i][y] == '$' && cut[i][y + 1]))
			{
				if (var->ctn != NULL)
				{
					a = 1;
					ft_putstr(var->ctn);
				}
				while (cut[i][++y] != '$' && cut[i][y] != '\0')
						;
				var = var->next;
			}
			if ((cut[i][y] != '$' && (cut[i][y] != '\0') ) || (cut[i][y] == '$' && !(cut[i][y + 1])))
			{
			//	printf("----%s--->%c|\n",cut[i], cut[i][y]);
				a = 1;
				write (1, &cut[i][y], 1);
			}
		}
	}
	write (1, "\n" , 1);
	free_list(&var);*/
}

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
