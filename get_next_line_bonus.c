/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagonzal <cagonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:20:52 by cagonzal          #+#    #+#             */
/*   Updated: 2022/04/19 15:50:40 by cagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// The buffer can't be 10000000 because the stack size is 8MB

/*
	Take the buffer string and join it with the buff one 
	Finally free the memory allocated on the buffer pointer.
*/
char	*ft_joinfree(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

/*
	Ft_nextline Function
		Find len of the first line
		Handle the end of line = \0 returning NULL
		Then allocate the memory needed for the line variable
			(len of file - len of firstline + 1)
		Finally overturn the buffer on the line variable to return it.
*/
char	*ft_nextline(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

/*
	Ft_Line
		Take the buffer, and going to the end of line we get the size
		Use the size to allocate the neded memory for thhe line
		And overturn the buffer content on the line.
		Finally if the end of line is \n or \0, replace with \n
*/
char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

/*
	Read_file function

		If *res doesn't exists then we malloc a 1x1
		After that we malloc the buffer with size of char
		Finally while the file doesn't end
			Read the buffer using BUFFER_SIZE as a the bytes_read size
				If the bytes read are -1 then we free the buffer and return a NULL
			we make the byte_read position (or final) 0, so we prevent memory leaks
			finally we join the res with the buffer
				if \n is find we quit the while
*/
char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = 0;
		res = ft_joinfree(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

/*
	Base Funcion Get_Next_Line

		Using the limit var OPEN_MAX the various posible instances got by multiple fd
			are correctly hndle avoiding conflicts between them
		We handle the error asking for a negative fd / empty or negative BUFFER_SIZE
		If everything correct then we use the read_file function passing the return
			to the buffer variable, handling possible empty buffer errors
		Finally we use the ft_line function to get the line to return
		Together with the ft_nextline function to get the next line
*/
char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_nextline(buffer[fd]);
	return (line);
}
