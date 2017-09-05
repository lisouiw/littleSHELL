/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:12:51 by ltran             #+#    #+#             */
/*   Updated: 2017/09/05 18:23:21 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	b_cd(char *cd, t_env **env)
{
	char	buf[PATH_MAX - 1];
	char	*way;
	int		i;

	i = 0;
	getcwd(buf, PATH_MAX);
	way = t_strjoin(buf, "/", cd);
	if (cd && ft_strcmp(cd, "-") == 0)
		cd_prev(env, buf);
	else if ((!(cd) || ft_strcmp(cd, "~") == 0))
		cd_home(env, buf);
	else if (cd[0] == '~')
		cd_name(env, cd, NULL, buf);
	else
		cd_slash(env, cd[0] == '/' ? cd : way, buf, cd);
	free(way);
}

int		give_path(t_env *env, char **cut, int i, int a)
{
	char	**path;
	char	*cmd;
	pid_t	father;
	int		w;

	while (env && env->next != NULL && ft_strcmp("PATH=", env->name) != 0)
		env = env->next;
	if (env && ft_strcmp("PATH=", env->name) == 0 &&
			(path = ft_strsplit(env->ctn, ':')))
	{
		while (path[++i] && a == -1)
		{
			cmd = t_strjoin(path[i], "/", cut[0]);
			if ((a = access(cmd, F_OK)) == 0)
			{
				father = fork();
				waitpid(father, &w, 0);
				if (father == 0)
					execve(cmd, cut, NULL);
			}
			free(cmd);
		}
		free_tab(path);
	}
	return (a);
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
	{
		if (give_path(env, cut, -1, -1) == -1)
		{
			ft_putstr("sh : command not found: ");
			ft_putendl(cut[0]);
		}
	}
}

t_env	*exec_cmd(char *line, t_env *env, char **cut, int i)
{
	if (!(cut = strsplit_two_c(line, '\t', ' ')) || !cut[0])
		return (env);
	if (ft_strcmp("echo", cut[0]) == 0)
	{
		if (ft_strchr(line, '"') == NULL && ft_strchr(line, 39) == NULL)
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
		b_unset(cut, &env, 0);
	else if (ft_strcmp("cd", cut[0]) == 0)
		b_cd(cut[1], &env);
	else
		b_other(cut, env);
	free_tab(cut);
	return (env);
}

int		main(void)
{
	char	*line;
	t_env	*envs;

	line = NULL;
	envs = give_env(NULL);
	while (42)
	{
		ft_putstr("(. Y .)> ");
		if (get_next_line(0, &line) && ft_strcmp(line, "exit") == 0)
		{
			free(line);
			free_list(&envs);
			exit(0);
		}
		else if (line && ft_strlen(line) > 0 &&
				(envs = exec_cmd(line, envs, NULL, 0)))
			free(line);
		else if (!(line))
		{
			ft_putchar(0);
			exit(0);
		}
	}
	return (0);
}
