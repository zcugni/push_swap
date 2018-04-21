/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:54:44 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/26 19:54:45 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_g_list    *ft_list_lstnew(void const *content, size_t content_size)
{
    t_g_list  *new;

    new = (t_g_list *)malloc(sizeof(t_g_list));
    if (new == NULL)
        return (NULL);
    if (content == NULL)
    {
        new->content = NULL;
        new->content_size = 0;
    }
    else
    {
        new->content = ft_lstcpy((t_list *)content);
        new->content_size = content_size;
	}
    new->next = NULL;
    return (new);
}

t_g_list  *ft_g_lstnew(void const *content, size_t content_size)
{
    t_g_list  *new;

    new = (t_g_list *)malloc(sizeof(t_g_list));
    if (new == NULL)
        return (NULL);
    if (content == NULL)
    {
        new->content = NULL;
        new->content_size = 0;
    }
    else
    {
    	new->content = malloc(content_size);
    	if (new->content == NULL)
            return (NULL);
        ft_memcpy(new->content, content, content_size);
        new->content_size = content_size;
	}
    new->next = NULL;
    return (new);
}

t_g_list  *ft_list_lstcpy(t_g_list *ori)
{
    t_g_list *new;
    t_g_list *first_elem;
    t_g_list *current;

    if (!ori)
        return (NULL);
    new = ft_list_lstnew(ori->content, ori->content_size);
    if (!new)
        return (NULL);
    first_elem = new;
    current = ori->next;
    while (current)
    {
        new->next = ft_list_lstnew(current->content, current->content_size);
        if (!new->next)
            return (NULL);
        new = new->next;
        current = current->next;
    }
    return (first_elem);
}

t_g_list  *ft_g_lstcpy(t_g_list *ori)
{
    t_g_list *new;
    t_g_list *first_elem;
    t_g_list *current;

    if (!ori)
        return (NULL);
    new = ft_g_lstnew(ori->content, ori->content_size);
    if (!new)
        return (NULL);
    first_elem = new;
    current = ori->next;
    while (current)
    {
        new->next = ft_g_lstnew(current->content, current->content_size);
        if (!new->next)
            return (NULL);
        new = new->next;
        current = current->next;
    }
    return (first_elem);
}

void    ft_g_lstappend(t_g_list **alst, t_g_list *new)
{
    t_g_list *tmp;

    if (new)
    {
        if (*alst)
        {
            tmp = *alst;
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = new;
        }
        else
            *alst = new;
    }
}

void    ft_g_lstadd(t_g_list **alst, t_g_list *new)
{
    if (new)
    {
        if (*alst)
        	new->next = *alst;
        *alst = new;
    }
}

void    lst_clr(t_list **lst)
{
    if (lst && *lst)
    {
        if ((*lst)->next)
            lst_clr(&((*lst)->next));
        ft_memdel((void **)lst);
    }
}

void    lst_g_clr(t_g_list **lst)
{
    if (lst && *lst)
    {
        if ((*lst)->next)
            lst_g_clr(&((*lst)->next));
        free((*lst)->content);
        ft_memdel((void **)lst);
    }
}
