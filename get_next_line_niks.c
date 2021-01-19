/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_niks.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/19 17:08:17 by nhariman      #+#    #+#                 */
/*   Updated: 2021/01/19 19:21:37 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

static size_t	ft_strlen(char *s)
{
	size_t length;

	length = 0;
	while (s && s[length] != '\0')
		length++;
	return (length);
}


static char	*ft_strdup(char *s1)
{
	int		len;
	int		i;
	char	*str;

	len = ft_strlen(s1);
	i = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;
	size_t	length;

	if (!s)
		return (0);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	length = ft_strlen(s) - start;
	substring = NULL;
	if (length < len)
		substring = (char *)malloc((length + 1) * sizeof(char));
	else
		substring = (char *)malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substring[i] = (char)s[i + start];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char		*strduo;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	strduo = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!strduo)
	{
		free(s1);
		return (NULL);
	}
	while (s1 && i < ft_strlen(s1))
	{
		strduo[i] = s1[i];
		i++;
	}
	while (s2 && j < ft_strlen(s2))
	{
		strduo[i + j] = s2[j];
		j++;
	}
	strduo[i + j] = '\0';
	free(s1);
	return (strduo);
}

static int				find_newline(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char				*read_line(char *line_read)
{
	char		buf[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(0, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buf[bytes_read] = '\0';
		if (!line_read)
			line_read = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(line_read, buf);
			line_read = (!tmp ? NULL : ft_strdup(tmp));
			free(tmp);
		}
		if (!line_read)
			return (NULL);
		if (find_newline(buf) > -1)
			break ;
	}
	return (line_read);
}

static int				fill_line(char *line_read, char **line)
{
	int		newline;
	size_t	remainder;

	newline = find_newline(line_read);
	remainder = 0;
	if (newline != -1)
	{
		if (newline != 0)
			*line = ft_substr(line_read, 0, newline);
		else
			*line = ft_strdup("");
		remainder = 1;
	}
	else
		*line = ft_strdup(line_read);
	if (!*line)
		return (-1);
	return (newline != -1 && remainder ? 1 : 0);
}

static char				*fill_leftover(char *str)
{
	int		newline;
	char	*leftover;

	newline = find_newline(str);
	if (newline != -1)
	{
		leftover = ft_substr(str, newline + 1, ft_strlen(str) - newline - 1);
		if (!leftover)
			return (NULL);
	}
	else
		return (NULL);
	return (leftover);
}

int						get_next_line(char **line)
{
	static char		*leftover;
	char			*line_read;
	int				newline;
	int				ret;

	if (line == NULL || BUFFER_SIZE == 0)
		return (-1);
	line_read = NULL;
	*line = line_read;
	if (leftover)
	{
		line_read = ft_strdup(leftover);
		free(leftover);
		leftover = NULL;
	}
	if (find_newline(line_read) == -1)
		line_read = read_line(line_read);
	if (!line_read)
		return (-1);
	ret = fill_line(line_read, line);
	newline = find_newline(line_read);
	if (newline != -1)
		leftover = fill_leftover(line_read);
	free(line_read);
	return ((newline != -1 && !leftover) ? -1 : ret);
}
