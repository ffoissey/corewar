/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_read_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 14:03:58 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 19:07:03 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t		core_read_exec_code_size(t_champs *champs, int32_t fd)
{
	ssize_t			ret;
	int32_t			size;
	unsigned char	buff[4];

	ret = read(fd, buff, 4);
	if (ret == FAILURE)
		return (core_error(10));
	if (ret != 4)
	{
		if (ft_putstr_fd(champs->name, STDERR_FILENO) == FAILURE)
			return (core_error(8));
		return (core_error(6));
	}
	size = (buff[0] << 24 | buff[1] << 16 | buff[2] << 8 | buff[3]);
	if (size < 0 || size > CHAMP_MAX_SIZE)
	{
		if (ft_putstr_fd(champs->name, STDERR_FILENO) == FAILURE)
			return (core_error(8));
		return (core_error(7));
	}
	champs->exec_code_size = size;
	return (SUCCESS);
}

int8_t		core_read_comment(t_champs *champs, int32_t fd)
{
	ssize_t		ret;

	ret = read(fd, champs->comment, COMMENT_LENGTH);
	if (ret == FAILURE)
		return (core_error(10));
	if (ret != COMMENT_LENGTH)
		return (FAILURE);
	champs->comment[ret] = '\0';
	return (SUCCESS);
}
