/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/08/09 13:13:09 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int							g_fd;


void				ft_write_botsize(t_my *inf)
{
	t_comm			*all;

	all = inf->command_s;
	while (all != NULL)
	{
		inf->botsize += all->size;
		all = all->next;
	}
	lseek(g_fd, 136, SEEK_SET);
	inf->botsize = convert_end(inf->botsize, 4);
	write(g_fd, &inf->botsize, 4);
}

void				ft_read_all(t_my *inf)
{
	t_text			*new_t;
	int				i;

	i = 1;
	new_t = (t_text *)malloc(sizeof(t_text));
	new_t->next = NULL;
	while (ft_gnl_without_com(inf->fd, &(new_t->line)) > 0)
	{
		ft_push_t_back(inf, new_t, i++);
		new_t = (t_text *)malloc(sizeof(t_text));
		new_t->next = NULL;
	}
	free(new_t->line);
	free(new_t);
	ft_print_txt(inf->head);
}

int					main(int ac, char **av)
{
	t_my			inf;
	t_use_label		*p_use_l;
	char			command_name[6];

	if (ac < 2 || ac > 3 || !ft_check_format(av[1]))
		return (ft_printf("Not valid arguement\n"));
	else
		inf.file_name = ft_get_name(av[1]);
	ft_obnul(&inf, av[1]);
	ft_read_all(&inf);
	ft_read_head(&inf);
	ft_read_body(&inf, command_name, 0);
	ft_check_end(&inf);
	if ((p_use_l = ft_check_correct_labels(&inf)) && p_use_l != NULL)
	{
		SE1;
		ft_free(&inf);
		exit(1);
	}
	ft_pliz_write_to_file(&inf);
	ft_write_commands(&inf, 0, 0);
	ft_write_botsize(&inf);
	ft_free(&inf);
	ft_printf("Writing output program to %s", inf.file_name);
	return (0);
}
