/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:33:13 by plbuet            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/19 19:50:05 by plbuet           ###   ########.fr       */
=======
/*   Updated: 2025/05/19 19:02:50 by cbopp            ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int	ft_size(t_node *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_node	*ft_new(char *content)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

