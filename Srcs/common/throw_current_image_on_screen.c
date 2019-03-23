/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_current_image_on_screen.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 15:32:17 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/14 15:32:49 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

void	throw_current_image_on_screen(t_sdl *sdl)
{
	SDL_UpdateWindowSurface(sdl->window.window);
}
