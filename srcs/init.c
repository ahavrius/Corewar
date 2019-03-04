/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:29:39 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/04 13:30:04 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_header	*init_header(uint_t magic, char *prog_name, uint_t prog_size, char *comment)
{
	t_header	*header;

	header = (t_header *)malloc(sizeof(t_header));
	header->magic = magic;
	header->prog_size = prog_size;
	header->prog_name = prog_name;
	header->comment = comment;
	return (header);
}

t_player	*init_player(t_header *header, char *code)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	player->header = header;
	player->code = code;
	return (player);
}

t_cursor	*init_cursor(uint_t place, int whom)
{
	static	uint_t	id;
	t_cursor		*new_cursor;
	int				i;

	id++;
	new_cursor = (t_cursor *)malloc(sizeof(t_cursor));
	new_cursor->id = id;
	new_cursor->carry = 0;
	new_cursor->place = place;
	new_cursor->last_live = 0;
	new_cursor->delay = 0;
	i = 0;
	new_cursor->reg[i] = -whom;
	while (++i < REG_NUMBER)
		new_cursor->reg[i] = 0;
	return (new_cursor);
}

void		init_map(uint_t place, int whom)
{
	int		i; 

	i = -1;
	while (PLAY_CODE(whom)[++i])
	{
		g_arena[(place + i) % MEM_SIZE] = PLAY_CODE(whom)[i];
		g_arena_color[(place + i) % MEM_SIZE] = whom;
	}

}