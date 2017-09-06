/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:12:51 by ltran             #+#    #+#             */
/*   Updated: 2017/09/06 17:12:59 by ltran            ###   ########.fr       */
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

	if (access(cut[0], F_OK) == 0)
	{
		if ((father = fork()) < 0)
			exit(1);
		if (wait(0) && father == 0)
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
	else if (ft_strcmp(line, "exit") == 0)
		exit(0);
	else
		b_other(cut, env);
	free_tab(cut);
	return (env);
}

int		main(void)
{
	char	*line;
	t_env	*envs;
	int		i;

	line = NULL;
	envs = give_env(NULL);
	while (42)
	{
		ft_putstr("(. Y .)> ");
		if ((i = get_next_line(0, &line)) == 0 )
			exit(0);
		else if (line && ft_strlen(line) > 0 &&
				(envs = exec_cmd(line, envs, NULL, 0)))
			ft_strdel(&line);
		else if (!(line) || line == NULL)
		{
			ft_putchar(0);
			exit(0);
		}
	}
	return (0);
}
