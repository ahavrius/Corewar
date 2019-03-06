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
	int			arg;
	t_cursor	*cursor;

	cursor = (t_cursor *)l_cursor->content;
	if (cursor->delay-- > 0)
		return ;
	if (cursor->op == g_arena[cursor->place])
	{
		arg = 0x80;
		if (g_op_tab[cursor->op - 1].flag)
			arg = g_arena[++cursor->place];
		//tern on op func (cursor, arg, &shift) - change last_live and so on
		//cursor->place += shift;
	}
	else
			cursor->place++;
	cursor->op = g_arena[cursor->place];
	cursor->delay = g_op_tab_time[cursor->op - 1];
}

static t_list	*kill_when(t_list *l_cursor)
{
	t_cursor	*cursor;
	t_list		*new;

	cursor = (t_cursor *)l_cursor->content;
	new = NULL;
	if (cursor->last_live < g_cycles_to_die)
		new = ft_lstnew(cursor, 8);
	else
		free(cursor);
	l_cursor->content = NULL;
	return (new);
}


static void	kill_cursors(void)
{
	t_list	*new_list;

	new_list = ft_lstmap_link(g_all_cursor, kill_when);
	new_list = ft_lst_reverse(new_list);
	ft_lstdel(&g_all_cursor, NULL);
	g_all_cursor = new_list;
}

void		run_one_circle(void)
{
	int		rounds;

	rounds = -1;
	g_live_per_cyrcle = 0;
	while (++rounds < g_cycles_to_die + (g_cycles_to_die <= 0))
	{
		ft_lstiter(g_all_cursor, run_one_cursor);
		g_current_cyrcle++;
	}
	//clean cursor
	if (g_live_per_cyrcle >= NBR_LIVE || ++g_check_amount == MAX_CHECKS)
	{
		g_cycles_to_die =- CYCLE_DELTA * (g_cycles_to_die > 0);
		g_check_amount = 0;		
	}

}