/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:22:44 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/11/21 18:24:02 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **alst, void (*del)(void *))
{
	t_list	*lst;

	if (!(*alst) || !del)
		return ;
	while (*alst)
	{
		lst = *alst;
		*alst = (*alst)->next;
		del(lst->content);
		free(lst);
	}
}
