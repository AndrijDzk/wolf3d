/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sdl_error_and_return.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 10:46:02 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/15 10:46:02 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"

#include "libft.h"

int				print_sdl_error_and_return(char *where)
{
	ft_printf("%s: %s\n", where, SDL_GetError());
	return (1);
}
