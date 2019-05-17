/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atropnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 04:59:34 by atropnik          #+#    #+#             */
/*   Updated: 2019/05/17 04:10:55 by atropnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_glst	*start_list(int fd)
{
	t_glst			*new_list;

	if (!(new_list = (t_glst*)malloc(sizeof(t_glst))))
			return (NULL);
	new_list->buff = ft_strnew(0);
	new_list->fd = fd;
	return (new_list);
}

t_glst	*current_file(const int fd, t_glst **fds)
{
	t_glst			*temp_list;

	temp_list = *fds;
	while (temp_list)
	{
		if (temp_list->fd == fd)
			return (temp_list);
		temp_list = temp_list->next;
	}
	temp_list = start_list(fd);
	temp_list->next = *fds;
	*fds = temp_list;
	return (temp_list);
}

int		line_return(t_glst *node, int size, char **line)
{
	char			*temp;
	int				fd;
	char			*str;

	fd = node->fd;
	str = node->buff;
	if (str[size] == '\0')
	{
		if (size == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(str);
		ft_strdel(&str);
	}
	else if (str[size] == '\n')
	{
		*line = ft_strsub(str, 0, size);
		temp = ft_strdup(str + size + 1);
		free(str);
		str = temp;
		if (str[size] == '\0')
			ft_strdel(&str);
	}
	else
		ft_puterror("Something went wrong");
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static  t_glst	*node;
	static	t_glst	*fds;
	int				bytesread;
	int				size;

	if (!line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	node = current_file(fd, &fds);
	while ((bytesread = read(fd, buf, BUFF_SIZE)))
	{
		buf[bytesread] = '\0';
		node->buff = ft_strjoin(node->buff, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if ((bytesread < BUFF_SIZE) && !(ft_strchr(buf, '\n')))
		return (0);
	size = ft_strchr(node->buff, '\n') - node->buff;
	// *line = ft_strnew(size);
	return line_return(node, size, line);
	// ft_strncpy(*line, node->buff, size);
	// return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*buf;

	if (argc == 1)
		fd = 0;
	else if (argc > 3)
		return (0);
	else
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &buf) == 1)
		{
			ft_putendl(buf);
			free(buf);
		}
		fd = open(argv[2], O_RDONLY);
		while (get_next_line(fd, &buf) == 1)
		{
			ft_putendl(buf);
			free(buf);
		}
	}
} 
