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

static void	read_file(char *file_name, int player_number)
{
	char		c;
	t_player	*cur_player;
	int			file;

	if (ft_strcmp(file_name + ft_strlen(file_name) - 4, ".cor") != 0)
		drop_error(ERROR_FILECOR);
	file = open(file_name, O_RDONLY);
	if (file == -1)
		drop_error(ERROR_OPENFILE);
	cur_player = parce_bytecode(file, player_number);
	g_array_players[cur_player->header->magic - 1] = cur_player;
	if (read(file, &c, 1) > 0)
		drop_error(ERROR_TOOLONG);
	close(file);
}

static int	read_players(int argc, char **argv)
{
	int			i;
	int			player_number;
	int			amount_players;

	i = -1;
	amount_players = 0;
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
	return (amount_players);
}

static int	read_flags(int argc, char **argv)
{
	int		i;

	i = 1;
	g_dump = -1;
	while (i < argc && (ft_strcmp(argv[i], "-dump") == 0 || ft_strcmp(argv[i], "-v") == 0))
	{
		if (ft_strcmp(argv[i], "-dump") == 0)
		{
			if (i + 1 >= argc || ft_strlen(argv[i + 1]) != ft_striter_bool(argv[i + 1], ft_isdigit))
				drop_error(ERROR_FLAGFORMAT);
			g_dump = ft_atoi(argv[i + 1]);
			i += 2;
		}
		if (ft_strcmp(argv[i], "-v") == 0)
		{
			g_vizo = 1;
			i++;
		}
	}
	return (i);
}

void		main_read(int argc, char **argv)
{
	int		shift;
	int		amount_players;

	if (argc == 1)
	{
		help(argv[0]);
		exit(0);
	}
	shift = read_flags(argc, argv);
	if (shift == argc)
		drop_error(ERROR_NOFILE);
	amount_players = read_players(argc - shift, &argv[shift]);

	intro(amount_players);
}
