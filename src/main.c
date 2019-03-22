/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:09:41 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/04 16:09:42 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	clean_flags_vizo(void)
{
	g_dump = DUMP;
	g_vflag = 0;
	g_aflag = 0;
	g_pflag = 0;
}

static void	cheak_defines(void)
{
	if (IND_SIZE <= 0 || REG_SIZE <= 0 || DIR_SIZE <= 0 ||
		REG_CODE <= 0 || DIR_CODE <= 0 || IND_CODE <= 0 ||
		MAX_ARGS_NUMBER <= 0 || MAX_PLAYERS <= 0 || MEM_SIZE <= 0 ||
		IDX_MOD <= 0 || CHAMP_MAX_SIZE <= 0 || REG_NUMBER <= 0 ||
		CYCLE_DELTA <= 0 || NBR_LIVE <= 0 || MAX_CHECKS <= 0 ||
		PROG_NAME_LENGTH <= 0 || COMMENT_LENGTH <= 0 || T_REG <= 0 ||
		T_DIR <= 0 || T_IND <= 0 || T_LAB <= 0)
		drop_error(ERROR_DEFINE);
}

int			main(int argc, char **argv)
{
	cheak_defines();
	main_read(argc, argv);
	if (g_vizo)
		clean_flags_vizo();
	if (g_dump == 0)
		print_map();
	if (g_vizo == 1)
	{
		init_ncurses();
		print_battle_field();
		print_cursor();
		print_score_board();
	}
	buttle();
	main_free();
	return (0);
}
