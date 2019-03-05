/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 20:33:43 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/03 20:34:26 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
#include "vm_error.h"
# include "op.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
/*
#include <sys/types.h>
#include <sys/stat.h>
*/

# define uchar			unsigned char
# define bool			char
# define uint_t			unsigned int

# define PLAY_NAME(i)		(g_array_players[(i)]->header->prog_name)
# define PLAY_ID(i)			(g_array_players[(i)]->header->magic)
# define PLAY_SIZE(i)		(g_array_players[(i)]->header->prog_size)
# define PLAY_COMMENT(i)	(g_array_players[(i)]->header->comment)
# define PLAY_CODE(i)		(g_array_players[(i)]->code)



typedef struct			s_header
{
	uint_t				magic;
	char				*prog_name;
	uint_t				prog_size;
	char				*comment;
}						t_header;

typedef struct			s_player
{
	t_header			*header;
	char				*code;
}						t_player;

typedef struct			s_cursor
{
	uint_t				id;
	uchar				op;
	bool				carry;
	uint_t				place;
	uint_t				last_live;
	uint_t				delay;
	int32_t				reg[REG_NUMBER]; //int?
}						t_cursor;

uchar		g_arena[MEM_SIZE];
char		g_arena_color[MEM_SIZE];
t_player	*g_array_players[MAX_PLAYERS];

int			g_dump;
t_list		*g_all_cursor;


t_header	*init_header(uint_t magic, char *prog_name, uint_t prog_size, char *comment);
t_player	*init_player(t_header *header, char *code);
t_cursor	*init_cursor(uint_t place, int whom);
void		init_map(uint_t place, int whom);


t_player	*parce_bytecode(int file, uint_t number);
void		read_flags(int argc, char **argv);

#endif
