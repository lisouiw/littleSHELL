/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 18:01:20 by ltran             #+#    #+#             */
/*   Updated: 2017/09/03 20:25:43 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_prev(t_env **env, char *buf)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp && tmp->next != NULL && ft_strcmp(tmp->name, "OLDPWD=") != 0)
		tmp = tmp->next;
	if (tmp && ft_strcmp(tmp->name, "OLDPWD=") == 0)
	{
		if (chdir(tmp->ctn) == 0)
		{
			b_export(ft_strjoin("OLDPWD=", buf), &(*env));
			getcwd(buf, PATH_MAX);
			b_export(ft_strjoin("PWD=", buf), &(*env));
			ft_putendl(buf);
		}
		else
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(tmp->ctn);
		}
	}
	else
		ft_putendl("sh: cd: OLDPWD not set");
}

void	cd_home(t_env **env, char *buf)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp && tmp->next != NULL && ft_strcmp(tmp->name, "HOME=") != 0)
		tmp = tmp->next;
	if (tmp && ft_strcmp(tmp->name, "HOME=") == 0)
	{
		if (chdir(tmp->ctn) == 0)
		{
			b_export(ft_strjoin("OLDPWD=", buf), &(*env));
			getcwd(buf, PATH_MAX);
			b_export(ft_strjoin("PWD=", buf), &(*env));
		}
		else
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(tmp->ctn);
		}
	}
	else
		ft_putendl("sh: cd: HOME not set");
}

void	cd_name(t_env **env, char *cd, char *user, char *buf)
{
	user = ft_strjoin("/Users/", &cd[1]);
	if (chdir(user) == 0)
	{
		b_export(ft_strjoin("OLDPWD=", buf), &(*env));
		getcwd(buf, PATH_MAX);
		b_export(ft_strjoin("PWD=", buf), &(*env));
	}
	else
		printf("EROOOOOOOOOOR\n");
}

void	cd_slash(t_env **env, char *cd, char *buf)
{
	if (chdir(cd) == 0)
	{
		b_export(ft_strjoin("OLDPWD=", buf), &(*env));
		getcwd(buf, 127);
		b_export(ft_strjoin("PWD=", buf), &(*env));
	}
	else
		printf("EROOOOOOOOOOR\n");
}

