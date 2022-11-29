/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 00:43:16 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/29 10:49:43 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	int		count;
	
	count = n;
	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	while (count >= 0)
	{
		// printf("i = %ld | j = %ld\n", i, j);
		// if (s1[i] == -1)
		// 	return (s2[j]);
		// if (!s2[j == -1])
		// 	return (s1[i]);
		if (s1[i] != s2[j])
			return (s1[i] - s2[j]);
		else if (i == 0 && count != 0)
			return (s2[j]);
		else if (j == 0 && count != 0)
			return (s1[i]);
		i--;
		j--;
		count--;
	}
	return (0);
}

// int main()
// {
// 	printf("result = %d\n", ft_strrncmp("b", "JS ERROR;JS LOG", 15));
// 	return 0;
// }