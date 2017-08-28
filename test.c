/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 21:33:00 by ltran             #+#    #+#             */
/*   Updated: 2017/08/27 20:42:08 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int);

int main()
{
	signal(SIGINT, sighandler);

	while(1) 
	{
		printf("Going to sleep for a second...\n");
		sleep(1); 
	}
	return(0);
}

void sighandler(int signum)
{
	printf("Caught signal %d, coming out...\n", signum);
	exit(1);
}
