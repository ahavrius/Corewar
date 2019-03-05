/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/03/03 19:40:29 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "vm.h"

#define IND_SIZE			2
#define REG_SIZE			4
#define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

#define MAX_ARGS_NUMBER		4
#define MAX_PLAYERS			4
#define MEM_SIZE			(4 * 1024)
#define IDX_MOD				(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

#define COMMENT_CHAR		'#'
#define LABEL_CHAR			':'
#define DIRECT_CHAR			'%'
#define SEPARATOR_CHAR		','

#define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING		".name"
#define COMMENT_CMD_STRING	".comment"

#define REG_NUMBER			16

#define CYCLE_TO_DIE		1536
#define CYCLE_DELTA			50
#define NBR_LIVE			21
#define MAX_CHECKS			10

#define T_REG				1
#define T_DIR				2
#define T_IND				4
#define T_LAB				8

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

# define uchar            unsigned char
# define bool            char
# define uint_t            unsigned int

//typedef t_func;

typedef struct    s_op
{
    char        *name;
    uchar        args_num;
    uchar        args_types[3];
    bool        flag;
    uchar        t_dir_size;
    //    t_func        func;
}                t_op;


t_op    g_op_tab[16] =
{
	{"live", 1, {T_DIR}, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 1, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 1, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 1, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 1, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"zjmp", 1, {T_DIR}, 0, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
	{"fork", 1, {T_DIR}, 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 1, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{"lfork", 1, {T_DIR}, 0, 2},
	{"aff", 1, {T_REG}, 1, 4}
};


int		g_op_tab_time[16] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

#endif
