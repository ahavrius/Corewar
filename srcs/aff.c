/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmerkulo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 17:01:18 by kmerkulo          #+#    #+#             */
/*   Updated: 2019/03/17 17:01:19 by kmerkulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		make_aff(t_cursor *cursor, int arg, int *shift)
{
	char	val;
	int		reg;

	val = 0;
	*shift = 2;
	if (!g_aflag || ((arg & 0xc0) != 0x40) ||
		!valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 1));
	reg = g_arena[(cursor->place + (*shift)++) % MEM_SIZE];
	val = cursor->reg[reg - 1];
	ft_printf("Aff: %c\n", val);
	return (*shift);
}

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

void	print_players(void)
{
	int			i;
	t_cursor	*cursor;

	i = -1;
	while (g_all_cursor->next)
	{
		cursor = (t_cursor *)g_all_cursor->content;
		ft_printf(
			"id - %d value - %02x, %02x %02x %02x %02x, place - %06p d - %d\n",
			cursor->id, g_arena[cursor->place], g_arena[cursor->place + 1],
					g_arena[cursor->place + 2], g_arena[cursor->place + 3],
					g_arena[cursor->place + 4], cursor->place, cursor->delay);
		g_all_cursor = g_all_cursor->next;
	}
	ft_printf("modulo - %hd\n", -32760 % MEM_SIZE);
}