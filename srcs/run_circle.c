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

void	read_op(t_cursor *cursor)
{
	int		shift;
	int		arg;

	if (cursor->delay-- > 0)
		return ;
	shift = 0;
	if (cursor->op == cursor->place)
	{
		arg = 0x80;
		if (g_op_tab[cursor->op - 1].flag)
			arg = g_arena[cursor->place++];
		//tern on op func (cursor, shift, &shift)
		cursor->place += shift;
	}
	else
			cursor->place++;
	cursor->op = cursor->place;
	cursor->delay = g_op_tab_time[cursor->op - 1];
}
