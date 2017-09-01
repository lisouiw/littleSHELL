/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 21:33:00 by ltran             #+#    #+#             */
/*   Updated: 2017/09/01 13:32:52 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

t_env	*add(t_env *env, char *name, char *ctn)
{
	while (env != NULL)
		;
	return (env);
}

int		main(int ac, char **av)
{
	t_env	*env;
	if (!(env))
		printf("Non\n");
//	env = add(env, "name", "ctn");
	env = (t_env*)malloc(sizeof(t_env));
	env->name = ft_strnew(0);
	env->ctn = ft_strnew(0);
	if (!(env))
		printf("Toujours Non\n");
	free(env->name);
	free(env->ctn);
//	free(env);
	env = NULL;
	if (!(env))
		printf("AHHHHHHHHHHHHHHHH Non\n");
//	env = (t_env*)malloc(sizeof(t_env));
	env->name = ft_strnew(0);
	return(0);
}
