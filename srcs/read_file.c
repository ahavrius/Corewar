/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:50:24 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/04 13:50:25 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

//check .cor
static void	read_file(char *file_name, int player_number)
{
	t_player	*cur_player;
	int			file;
	if (ft_strcmp(file_name + ft_strlen(file_name) - 4, ".cor") != 0)
		drop_error(ERROR_FILECOR);
	file = open(file_name, O_RDONLY);
	if (file == -1)
		drop_error(ERROR_OPENFILE);
	cur_player = parce_bytecode(file, player_number);
	g_array_players[cur_player->header->magic - 1] = cur_player;
	close(file);
}

static void	help(char *name)
{
	ft_printf("Usage: %s [-v | - d N] [-n N ]  <champion1.cor> <...>\n", name);
	ft_printf("###########################################################\n");
	ft_printf("    -dump N   : Dumps memory after N cycles then exits\n");
	ft_printf("    -v        : Ncurses output mode\n");
	ft_printf("    -n        : force define number of player\n");
	exit(0);
}

static void	intro(int amount_players)
{
	int		i;
	int		j;

	i = -1;
	j = 1;
	ft_printf("Introducing contestants...\n");
	while (++i < MAX_PLAYERS)
		if (g_array_players[i] != NULL)
		{
			ft_printf("* Player %d, weighing %d bytes, %s (%s) !\n",
				PLAY_ID(i), PLAY_SIZE(i), PLAY_NAME(i), PLAY_COMMENT(i));
			ft_lstadd(&g_all_cursor, ft_lstnew_link(init_cursor(j * MEM_SIZE / amount_players, i), 8));
			init_map(j * MEM_SIZE / amount_players, i);
			j++;
		}
}

void	read_flags(int argc, char **argv)
{
	int			i;
	int			player_number;
	int			amount_players;

	i = 0;
	amount_players = 0;
	if (argc == 1)
		help(argv[0]);
	if (ft_strcmp(argv[i + 1], "-dump") == 0)
	{
		if (i + 2 >= argc)
			drop_error(ERROR_FLAGFORMAT);
		g_dump = ft_atoi(argv[i + 2]);
		i += 2;
	}
	while (++i < argc)
	{
		player_number = 0;
		if (ft_strcmp(argv[i], "-n") == 0)
		{
			if (i + 2 >= argc)
				drop_error(ERROR_FLAGFORMAT);
			player_number = ft_atoi(argv[i + 1]);
			i += 2;
		}
		read_file(argv[i], player_number);
		amount_players++;
	}

	intro(amount_players);
}
