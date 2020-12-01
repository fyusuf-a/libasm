/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:35:15 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/12/01 11:40:50 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

t_list		*ft_create_elem(void *data)
{
	t_list	*ret;

	if (!(ret = malloc(sizeof(t_list))))
		return (NULL);
	ret->data = data;
	ret->next = NULL;
	return (ret);
}

size_t		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			elem(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int			check_base(char *base)
{
	int i;
	int j;

	i = 0;
	if (!base[0])
		return (0);
	else if (!base[1])
		return (0);
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		if (base[i] == '+' || base[i] == '-'
			|| !(' ' <= base[i] && base[i] <= '~')
			|| elem(base[i], " \f\n\r\t\v"))
			return (0);
		i++;
	}
	return (1);
}

int			first_index(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}

int			eat_signs(char **str)
{
	int sign;

	sign = 1;
	while (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1 * sign;
		(*str)++;
	}
	return (sign);
}

int			ft_atoi_base(char *str, char *base)
{
	int	sign;
	int	number;
	int	base_size;
	int	i;

	number = 0;
	if (!check_base(base))
		return (0);
	base_size = ft_strlen(base);
	if (base_size)
	{
		while (elem(*str, " \f\n\r\t\v"))
			str++;
		sign = eat_signs(&str);
		while ((i = first_index(*str, base)) != -1)
		{
			number = base_size * number + i;
			str++;
		}
		return (sign * number);
	}
	return (0);
}

void		ft_list_push_front(t_list **begin_list, void *data)
{
	t_list	*ret;

	if (!begin_list)
		return ;
	ret = ft_create_elem(data);
	ret->next = *begin_list;
	*begin_list = ret;
}

int			ft_list_size(t_list *begin_list)
{
	if (!begin_list)
		return (0);
	return (1 + ft_list_size(begin_list->next));
}

int			ft_list_sort_acc(t_list *begin_list, int (*cmp)(), int is_sorted)
{
	void	*data_copy;

	if (begin_list->next == NULL)
		return (is_sorted);
	if (cmp(begin_list->data, begin_list->next->data) > 0)
	{
		data_copy = begin_list->data;
		begin_list->data = begin_list->next->data;
		begin_list->next->data = data_copy;
		is_sorted = 0;
	}
	return (ft_list_sort_acc(begin_list->next, cmp, is_sorted));
}

void		ft_list_sort(t_list **begin_list, int (*cmp)())
{
	if (ft_list_sort_acc(*begin_list, cmp, 1) == 1)
		return ;
	ft_list_sort(begin_list, cmp);
}

t_list		*ft_list_remove_if_acc(t_list *begin_list, void *data_ref,
							int (*cmp)(), void (*free_fct)(void*))
{
	if (begin_list == NULL)
		return (NULL);
	while (cmp(begin_list->data, data_ref) == 0)
	{
		free_fct(begin_list->data);
		begin_list = begin_list->next;
		if (begin_list == NULL)
			return (NULL);
	}
	begin_list->next = ft_list_remove_if_acc(begin_list->next, data_ref, cmp,
															free_fct);
	return (begin_list);
}

void		ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
									void (*free_fct)(void*))
{
	*begin_list = ft_list_remove_if_acc(*begin_list, data_ref, cmp, free_fct);
}
