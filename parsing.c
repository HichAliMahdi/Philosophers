/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:58:45 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/06 18:25:19 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= 9);
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		ft_error("Only positives numbers");
	if (!is_digit(*str))
		ft_error("The input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		ft_error("The value is bigger than INT_MAX");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	nbr;

	nbr = 0;
	str = valid_input(str);
	while (is_digit(*str))
		nbr = (nbr * 10) + (*str - 48);
	if (nbr > INT_MAX)
		ft_error("The value is bigger than INT_MAX");
	return (nbr);
}

void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atoi(argv[1]);
}
