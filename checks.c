/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamy <alamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:41:15 by alamy             #+#    #+#             */
/*   Updated: 2018/02/12 14:56:17 by alamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_check_name_file(char *str)
{
	char *str1;
	int i;
	int j;

	i = 0;
	j = 0;
	str1 = ".fdf";
	
	while (str1[i] != '\0' && str[j] != '\0')
	{
		if (str1[i] == str[j])
			i++;
		if (str[j + 1] == '\0' && str1[i] != '\0')
		{
			ft_putstr("name file is not valid\n");
			return(-1);
		}
		j++;
	}
	return(0);
}

int ft_empty_file(char *str)
{
	int		fd;
	char	*line;
	int 	nb;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("open() failed\n");
		return (-1);
	}
	nb = get_next_line(fd, &line);
	if (nb == -1 || nb == 0)
	{
		ft_putstr("Empty file\n");
		return(-1);
	}
	while (get_next_line(fd, &line) > 0)
	{	
	}
	free(line);
	if (close(fd) == -1)
	{
		ft_putstr("close() failed\n");
		return (-1);
	}
	return(0);
}

int ft_check_map_rec(char *str1, t_env *tmp)
{
	int		fd;
    char	*line;
 	char 	**str;
	int		len;

	fd = open(str1, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("open() failed\n");
		return (-1);
	}
	while (get_next_line(fd, &line))
	{
		str = ft_strsplit(line, ' ');
		len = ft_lenght(str);
		if (tmp->nb_col != len)
		{
			ft_putstr("map not rectangular\n");
			return (-1);
		}
	}
	free(line);
	if (close(fd) == -1)
	{
		ft_putstr("close() failed\n");
		return (-1);
	}
	return (0);
}

int		ft_isxdigit(char *str)
{
	int		i;
	char 	*hex;

	i = 0;
	if (ft_strlen(str) >= 10)
	{
		hex = ft_strsub(str, ft_strlen(str) - 6, 6);
		if (ft_strspn(hex, "0123456789abcdefABCDEF") == 6 && ft_strstr(str, ",0x"))
		return (1);
	}
	return (0);
}

int     ft_check_data(char **argv)
{
    int     i;
	int		fd;
	char 	**str;
    char	*line;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
	{
		ft_putstr("open() failed\n");
		return (-1);
	}
	while (get_next_line(fd, &line))
	{
		i = 0;
		str = ft_strsplit(line, ' ');
		while (str[i] != '\0')
		{
			if (ft_isnumber(str[i]) == 0 && ft_isxdigit(str[i]) == 0)
			{
				ft_putstr("invalid data\n");
				return (-1);
			}
			i++;
		}
	}
	free(line);
	if (close(fd) == -1)
	{
		ft_putstr("close() failed\n");
		return(-1);
	}
    return (0);
}

int ft_checks(char **argv, t_env *tmp)
{
	if ((ft_check_name_file(argv[1])) == -1)
		return (-1);
	if ((ft_empty_file(argv[1])) == -1)
		return (-1);
	if ((ft_check_map_rec(argv[1], tmp)) == -1)
		return (-1);
	if ((ft_check_data(argv)) == -1)
		return (-1);
	return (0);
}