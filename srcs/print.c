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

void	cursor_move(t_cursor *cursor, int shift)
{
	int		old_place;
	int		i;

	old_place = cursor->place;
	ft_printf("ADV %d (%06p -> %06p) ", shift, old_place, old_place + shift);
	i = -1;
	while (++i < shift)
		ft_printf("%02x ", g_arena[(old_place + i) % MEM_SIZE]);
	ft_printf("\n");
}

static void	choose_num(int amount_players, t_list **poor_players)
{
	int			i;
	t_list		*head;
	t_player	*cur_player; 

	i = amount_players - 1;
	while (++i < MAX_PLAYERS)
		if (g_array_players[i] != NULL)
			drop_error(ERROR_PLAYERNUMBER);
	head = *poor_players;
	while (head != NULL)
	{
		i = 0;
		while (i < amount_players && g_array_players[i])
			i++;
		cur_player = (t_player *)head->content;
		cur_player->header->magic = i + 1;
		g_array_players[i] = cur_player;
		head = head->next;
	}
	ft_lstdel(poor_players, NULL);
}

void	intro(int amount_players, t_list **poor_players)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	*poor_players = ft_lst_reverse(*poor_players);
	choose_num(amount_players, poor_players);
	ft_printf("Introducing contestants...\n");
	while (++i < MAX_PLAYERS)
		if (g_array_players[i] != NULL)
		{
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
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
			flag = i % 64;
		}
		ft_printf("\n");
	}
}

void	print_players(void)
{
    int		i;
    t_cursor *cursor;

    i = -1;

    while (g_all_cursor->next)
    {
        cursor = (t_cursor *)g_all_cursor->content;
        ft_printf("id - %d value - %02x, %02x %02x %02x %02x, place - %06p d - %d\n", cursor->id,
                  g_arena[cursor->place], g_arena[cursor->place + 1],
                  g_arena[cursor->place + 2], g_arena[cursor->place + 3],
                  g_arena[cursor->place + 4], cursor->place, cursor->delay);
        g_all_cursor = g_all_cursor->next;
    }
    ft_printf("modulo - %hd\n", -32760 % MEM_SIZE);
}
