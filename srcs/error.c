/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:15:52 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/04 14:16:39 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	drop_error(char *text_error)
{
	ft_printf("%s\n", text_error);

	main_free();
	//system("leaks corewar");
	exit(0);
}
