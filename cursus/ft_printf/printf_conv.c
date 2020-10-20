/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 10:03:38 by yekim             #+#    #+#             */
/*   Updated: 2020/10/20 10:09:16 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_char(char c, const t_info *info)
{
	int	ret;

	if (c == '\0')
	{
		write(STD_OUT, "\0", 1);
		return (1);
	}
	if (info->flag.minus)
		ret = write_prec_pad(&c, info);
	else
		ret = write_pad_prec(&c, info);
	return (ret);
}

int	printf_str(const char *str, const t_info *info)
{
	int	ret;

	if (str == NULL)
	{
		write(STD_OUT, "(null)", 6);
		return (6);
	}
	if (info->flag.minus)
		ret = write_prec_pad(str, info);
	else
		ret = write_pad_prec(str, info);
	return (ret);
}

int	printf_addr(const void *addr, const t_info *info)
{
	int		ret;
	char	*hex_str;

	ret = get_hex_len((unsigned long)addr, 1);
	if (!(hex_str = (char *)malloc(sizeof(char) * (ret + 1))))
		return (MALLOC_ERR);
	hex_str[ret] = '\0';
	get_hex_str((unsigned long)addr, hex_str, ret - 1, 1);
	hex_str = add_prefix("0x", hex_str);
	if (info->flag.minus)
		ret = write_prec_pad(hex_str, info);
	else
		ret = write_pad_prec(hex_str, info);
	free(hex_str);
	return (ret);
}
