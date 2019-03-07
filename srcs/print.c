/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:23:23 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/07 17:23:24 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	help(char *name)
{
	ft_printf("Usage: %s [-v | - d N] [-n N ]  <champion1.cor> <...>\n", name);
	ft_printf("###########################################################\n");
	ft_printf("    -dump N   : Dumps memory after N cycles then exits\n");
	ft_printf("    -v        : Ncurses output mode\n");
	ft_printf("    -n        : force define number of player\n");
	exit(0);
}

void	intro(int amount_players)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	ft_printf("Introducing contestants...\n");
	while (++i < MAX_PLAYERS)
		if (g_array_players[i] != NULL)
		{
			ft_printf("* Player %d, weighing %d bytes, %s (%s) !\n",
				PLAY_ID(i), PLAY_SIZE(i), PLAY_NAME(i), PLAY_COMMENT(i));
			init_map(j * MEM_SIZE / amount_players, i);
			ft_lstadd(&g_all_cursor, ft_lstnew_link(init_cursor(j * MEM_SIZE / amount_players, i), 8));
			j++;
		}
	init_global();
}

void	print_map(void)
{
	int		i;
	int		flag;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%06p : ", i);
		flag = 1;
		while (i < MEM_SIZE && flag)
		{
			ft_printf("%02x ", g_arena[i]);
			i++;
			flag = i % 32;
		}
		ft_printf("\n");
	}
}
