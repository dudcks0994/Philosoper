/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:34:04 by youngcki          #+#    #+#             */
/*   Updated: 2023/08/31 14:36:14 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ms(struct timeval *a, struct timeval *b)
{
	int	sec;
	int	usec;

	sec = a->tv_sec - b->tv_sec;
	usec = a->tv_usec - b->tv_usec;
	return (sec * 1000 + usec / 1000);
}

int	check_valid(int c, char **v)
{
	int	i;
	int	j;

	i = 1;
	while (i < c)
	{
		j = 0;
		while (v[i][j] != 0)
		{
			if (v[i][j] == ' ' || (8 < v[i][j] && v[i][j] < 14))
				j++;
			else if (47 < v[i][j] && v[i][j] < 58)
				j++;
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *s)
{
	int	sum;
	int	sign;

	sum = 0;
	sign = 1;
	while ((8 < *s && *s < 14) || *s == ' ')
		s++;
	while (47 < *s && *s < 58)
	{
		sum = sum * 10 + (*s - 48);
		if (sum < 0)
			return (-1);
		s++;
	}
	return (sign * sum);
}

int	intlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	int		i;

	i = 0;
	len = intlen(n) + 1;
	s = (char *)malloc(sizeof(char) * (len + 2));
	if (n > 0)
		s[0] = 'A';
	else
		s[0] = 'B';
	while (i < len)
	{
		s[len - i - 1] = "0123456789"[n % 10];
		n /= 10;
		i++;
	}
	s[i] = '\0';
	return (s);
}
