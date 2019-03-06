/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:30:45 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/05 20:30:46 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	run_one_cursor(t_list *l_cursor)
{
	int			shift;
	int			arg;
	t_cursor	*cursor;

	cursor = (t_cursor *)l_cursor->content;
	if (cursor->delay-- > 0)
		return ;
	shift = 0;
	if (cursor->op == cursor->place)
	{
		arg = 0x80;
		if (g_op_tab[cursor->op - 1].flag)
			arg = g_arena[cursor->place++];
		//tern on op func (cursor, arg, &shift) - change last_live and so on
		cursor->place += shift;
	}
	else
			cursor->place++;
	cursor->op = cursor->place;
	cursor->delay = g_op_tab_time[cursor->op - 1];
}

void		run_one_circle()
{
	ft_lstiter(g_all_cursor, run_one_cursor);
//update constant
//live and +++
//kol-vo alive
// kill dead cursor

}