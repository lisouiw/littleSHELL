/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:12:51 by ltran             #+#    #+#             */
/*   Updated: 2017/09/03 22:15:57 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"


int		len_double(char **ar, int i)
{
	int		len;

	len = 0;
	while (ar[++i])
		++len;
	return (len);
}

char	*line_split(char *len, char *str)
{
	int		i;

	i = 0;
	while (len[i] && len[i] == str[i])
		++i;
	if (!len[i])
	{
		while (--i != -1)
			++str;
		return (str);
	}
	return (NULL);
}

void	double_char(char **ar, int i)
{
	while (ar[++i])
		ft_putendl(ar[i]);
}



void	my_strjoin(char **spc, char **line, int a)
{
	char	*tmp;

	if (line[a] && !(line [a + 1]))
		*spc = line[a];
	while (line[a] && line [a + 1])
	{
		if (*spc != NULL)
			tmp = ft_strjoin(*spc, " ");
		else
			tmp = ft_strjoin(line[a], " ");
		*spc = ft_strjoin(tmp, line[a + 1]);
		++a;
	}
}

size_t	all_d_len(char **echo, int a)
{
	int			o;
	size_t		len;

	while (echo[++a])
	{
		o = -1;
		while (echo[a][++o])
			;
		len += o;
	}
	len = len + a + 1;
	return (len);
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

void	b_cd(char *cd, t_env **env)
{
	char	buf[PATH_MAX - 1];
	char	*way;
	int		i;

	getcwd(buf, PATH_MAX);
	way = ft_strjoin(buf , "/");
	way = ft_strjoin(way, cd);
	if (cd && ft_strcmp(cd, "-") == 0)
		cd_prev(env, buf);
	else if ((!(cd) || ft_strcmp(cd, "~") == 0))
		cd_home(env, buf);
	else if (cd[0] == '~')
		cd_name(env, cd, NULL, buf);
	else
		cd_slash(env, cd[0] == '/' ? cd : way, buf);
}

void	give_path(t_env *env, char **cut)
{
	char	**path;
	int		i;
	char	*cmd;
	pid_t	father;
	int		w;
	int		y;
	int		a;

	a = -1;
	i = -1;
	while (env && env->next != NULL && ft_strcmp("PATH=", env->name) != 0)
		env = env->next;
	if (env && ft_strcmp("PATH=", env->name) == 0 && (path = ft_strsplit(env->ctn, ':')))
	{
		father = fork();
		while (path[++i])
		{
			cmd = ft_strjoin(path[i], "/");
			cmd = ft_strjoin(cmd, cut[0]);
			waitpid(father, &w, 0);
			if ((a = access(cmd, F_OK)) == 0 && father == 0)
			{
				execve(cmd, cut, NULL);
				free(cmd);
				break;
			}
		}
		if (a == 0)
			return;
	}
	ft_putstr("sh : command not found: ");
	ft_putendl(cut[0]);
}

void	b_other(char **cut, t_env *env)
{
	pid_t	father;
	int		w;

	if (access(cut[0], F_OK) == 0)
	{
		father = fork();
		if (waitpid(father, &w, 0) && father == 0)
			execve(cut[0], cut, NULL);
	}
	else
			give_path(env, cut);
}

t_env	*exec_cmd(char *line, t_env *env)
{
	char	**cut;
	int		i;

	i = 0;
	if (!(cut = strsplit_two_c(line, '\t', ' ')) || !cut[0])
		return (env);
	if (ft_strcmp("echo", cut[0]) == 0)
	{
		if (!(cut[1]))
			write(1, "\n", 1);
		else if (ft_strchr(line , '"') == NULL && ft_strchr(line , 39) == NULL)
			double_char_c(cut, 0, ' ');
		else
			b_echo(NULL, 0, no_b_spc(line));
	}
	else if (ft_strcmp("env", cut[0]) == 0)
		ecriture_info(env);
	else if (ft_strcmp("export", cut[0]) == 0 && cut[1])
	{
		while (cut[++i])
			b_export(cut[i], &env);
	}
	else if (env && ft_strcmp("unset", cut[0]) == 0)
		b_unset(cut, &env);
	else if (ft_strcmp("cd", cut[0]) == 0)
		b_cd(cut[1], &env);
	else
		b_other(cut, env);
	return (env);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	*envs;

	envs = give_env(NULL);
	while (42)
	{
		ft_putstr("(. Y .)> ");
		if (get_next_line(0, &line) && ft_strcmp(line, "exit") == 0)
			exit(0);
		else if (line && ft_strcmp(line, "") != 0)
		{
			printf("|%s|\n", line);
			envs = exec_cmd(line, envs);
		}
		else if (!(line))
		{
			ft_putchar(0);
			exit(0);
		}
		if (line)
			free(line);
	}
	return (0);
}
