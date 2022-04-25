/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagonzal <cagonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:54:54 by cagonzal          #+#    #+#             */
/*   Updated: 2022/04/25 12:42:03 by cagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include "get_next_line_bonus.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// If buffer_size > file_size it repeats

char	*get_next_line(int fd);

void	leaks(void)
{
	system("leaks a.out");
}

void	main_ver(int *fd)
{
	char	*str;
	int		i;

	i = 0;
	printf("Línea %d \n", i);
	str = get_next_line(fd[0]);
	printf("%s", str);
	// if (str)
	// 	free (str);
	close(fd[0]);
	close(fd[1]);
}

void	bonus_ver(int *fd)
{
	char	*str;
	int		i;

	i = 0;
	printf("Línea %d \n", i++);
	str = get_next_line(fd[0]);
	printf("%s", str);
	printf("Línea %d \n", i++);
	str = get_next_line(fd[1]);
	printf("%s", str);
	printf("Línea %d \n", i++);
	str = get_next_line(fd[0]);
	printf("%s", str);
	printf("Línea %d \n", i++);
	str = get_next_line(fd[1]);
	printf("%s", str);
	if (str)
		free (str);
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char *argv[])
{
	int	fd[2];
	int	i;

	i = argc * 0;
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[2], O_RDONLY);
	main_ver(fd);
	// bonus_ver(fd);
	return (0);
}
