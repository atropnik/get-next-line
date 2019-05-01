/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atropnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:47:25 by atropnik          #+#    #+#             */
/*   Updated: 2019/05/01 06:14:17 by atropnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_malloc_again(char **save)
{
	char	*tmp;

	if (!(tmp = ft_strnew(ft_strlen(*save))))
		return (0);
	ft_strcpy(tmp, *save);
	*save = NULL;
	if (!(*save = ft_strnew(ft_strlen(tmp) + BUFF_SIZE)))
		return (0);
	ft_strcpy(*save, tmp);
	return (1);
}

int		fill_line(int j, char **save, char **line)
{
	int		i;
	int		y;

	y = 0;
	i = 0;
	if (j != 0 || ft_strlen((*save)) != 0)
	{
		while ((*save)[i] != '\n')
		{
			(*line)[i] = (*save)[i];
			i++;
		}
		(*line)[i++] = '\0';
		if ((*save)[0] == '\n')
		{
			while ((*save)[i])
				(*save)[y++] = (*save)[i++];
			(*save)[y] = '\0';
			return (2);
		}
		while ((*save)[i])
			(*save)[y++] = (*save)[i++];
		(*save)[y] = '\0';
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			j;
	static char	*save;

	if (fd < 0 || (!save && !(save = ft_strnew(BUFF_SIZE))))
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char) * BUFF_SIZE)))
		return (-1);
	while ((j = read(fd, *line, BUFF_SIZE)) > 0)
	{
		if (!(ft_malloc_again(&save)))
			return (-1);
		ft_strncat(save, *line, BUFF_SIZE);
		if (ft_memchr(*line, '\n', BUFF_SIZE))
			break ;
	}
	if ((fill_line(j, &save, &(*line))) == 2)
		return (1);
	if (ft_memcmp((*line), save, ft_strlen(*line)) == 0)
	{
		if (!(*line = ft_strdup("")))
			return (1);
		return (0);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
	if (argc == 2)
		close(fd);
}
