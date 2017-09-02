/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:12:51 by ltran             #+#    #+#             */
/*   Updated: 2017/09/02 16:12:07 by ltran            ###   ########.fr       */
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

/*
void	b_cd(char **way, char *home, char *pwd)
{
	int		a;
	pid_t	father;
	char	buf[101];
	int		i;
	char	*str;

//need modification du env a chaque desplacement| pwd previous |
//cd: not a directory: [file]
//cd : no such file or directory: [file]
//cd ~(HOME) | cd - (switch previous dir) |cd ~ltran
//no need modifier { cd / |
//cd ~user |cd / Users/login|
	getcwd(buf, 100);
	printf("PWD/BUF = %s HOME %s\n", pwd, home);
	str = ft_strjoin(ft_strjoin(buf, "/"), way[1]);
	if (!opendir(str))
	{
		if (open(str, O_RDONLY) == -1)
			ft_putstr("cd : no such file or directory: [file]\n");
		else
			ft_putstr("cd : not a directory: [file]\n");
	}
	if ((a = len_double(way,0)) == 2)
	{
		printf("A %i\n", a);
		ft_putstr("cd : string not in pwd : ");
		ft_putendl(way[1]);
	}
	printf("A %i\n", a);
	if (a > 2)
		ft_putstr("cd : too many arguments\n");
	if (a == 0 || a == 1 )
	{
		chdir("/");
		if (a == 0 || ft_strcmp(way[1], "~") == 0 || ft_strcmp(way[1], "--") == 0)
		{
			printf("~\n");
			chdir(home);
		}
	//	else if (ft_strcmp(way[1], "/") == 0)
	//		printf("/\n");
		else
		{
			printf("LET IT GO\n");
			chdir(str);
		}
	}
	//modifier le env
}*/

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
	while (env->next != NULL && ft_strcmp("PATH=", env->name) != 0)
		env = env->next;
	if (ft_strcmp("PATH=", env->name) == 0 && (path = ft_strsplit(env->ctn, ':')))
		father = fork();
	while (path[++i] && a == -1)
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, cut[0]);
		waitpid(father, &w, 0);
		if ((a = access(cmd, F_OK)) == 0 && father == 0)
		{
			execve(cmd, cut, NULL);
			free(cmd);
		}
	}
	if (a == -1)
	{
//		kill(father, y);
		ft_putstr("sh : command not found: ");
		ft_putendl(cut[0]);
	}
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



void	cd_home(t_env *env)
{
	char	buf[126];
	t_env	*tmp;
	t_env	*tm;

	tmp = env;
	tm = env;
	while (ft_strcmp(tmp->name, "OLDPWD=") != 0 && tmp->next != NULL)
		tmp = tmp->next;
	if (ft_strcmp(tmp->name, "OLDPWD=") == 0)
	{
		free(tmp->ctn);
		getcwd(buf, 126);
		tmp->ctn = ft_strdup(buf);
	}
	while (ft_strcmp(env->name, "HOME=") != 0 && env->next != NULL)
		env = env->next;
	if (ft_strcmp(env->name, "HOME=") == 0)
		chdir(env->ctn);
	while (ft_strcmp(tm->name, "PWD=") != 0 && tm->next != NULL)
		tm = tm->next;
	if (ft_strcmp(tm->name, "PWD=") == 0)
	{
		getcwd(buf, 127);
		free(tm->ctn);
		tm->ctn = ft_strdup(buf);
	}
}

void	cd_slash(t_env *tmp, char *cd)
{
	t_env	*env;
	char	buf[126]; //test if len sup

	env = tmp;
	while (ft_strcmp(tmp->name, "OLDPWD=") != 0 && tmp->next != NULL)
		tmp = tmp->next;
	if (ft_strcmp(tmp->name, "OLDPWD=") == 0)
	{
		getcwd(buf, 127);
		chdir(cd);
		free(tmp->ctn);
		tmp->ctn = ft_strdup(buf);
		while (ft_strcmp(env->name, "PWD=") != 0 && env->next != NULL)
			env = env->next;
		if (ft_strcmp(env->name, "PWD=") == 0)
		{
			getcwd(buf, 127);
			free(env->ctn);
			env->ctn = ft_strdup(buf);
		}
	}
}

void	cd_name(t_env *tmp, char *cd, char *user)
{
	t_env	*env;
	char	buf[126]; //test if len sup

	user = ft_strjoin("/Users/", &cd[1]);
	env = tmp;
	while (ft_strcmp(tmp->name, "OLDPWD=") != 0 && tmp->next != NULL)
		tmp = tmp->next;
	if (ft_strcmp(tmp->name, "OLDPWD=") == 0)
	{
		getcwd(buf, 127);
		chdir(user);
		free(tmp->ctn);
		tmp->ctn = ft_strdup(buf);
		while (ft_strcmp(env->name, "PWD=") != 0 && env->next != NULL)
			env = env->next;
		if (ft_strcmp(env->name, "PWD=") == 0)
		{
			getcwd(buf, 127);
			free(env->ctn);
			env->ctn = ft_strdup(buf);
		}
	}
}





void	cd_prev(t_env **env)
{
	t_env	*tmp;
	char	buf[126]; //test if len sup

	tmp = *env;
	while (tmp->next != NULL && ft_strcmp(tmp->name, "OLDPWD=") != 0)
		tmp = tmp->next;
	if (ft_strcmp(tmp->name, "OLDPWD=") == 0)
	{
		getcwd(buf, 127);
		chdir(tmp->ctn);
		b_export(ft_strjoin("PWD=", tmp->ctn), &(*env));
		b_export(ft_strjoin("OLDPWD=", buf), &(*env));
	}
	else
		ft_putendl("sh : cd: OLDPWD not set");
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
	char	buf[PATH_MAX]; //test if len sup
	char	*way;
	int		i;

	//need to create pwd  and OldPWd

	getcwd(buf, PATH_MAX + 1);
	way = ft_strjoin(buf , "/");
	way = ft_strjoin(way, cd);
	if (cd && ft_strcmp(cd, "-") == 0)
		cd_prev(env);

	printf("%s\n", way);
/*	else if ((!(cd) || ft_strcmp(cd, "~") == 0))
		cd_home(env);
	else if (cd[0] == '~')
		cd_name(env, cd, NULL);
	else if (cd[0] == '/')
		cd_slash(env, cd);
	else if (chdir(way) == -1)
		printf("ERROR\n");*/
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
/*	else
		b_other(cut, env);*/
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
		else if (line)
			envs = exec_cmd(line, envs);
		else
		{
			ft_putchar(0);
			exit(0);
		}
	}
	return (0);
}
