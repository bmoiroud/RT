/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_sdl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 11:55:45 by agrumbac          #+#    #+#             */
/*   Updated: 2018/01/07 19:17:25 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASY_SDL_H
# define EASY_SDL_H

/*
** ********************************** SDL **************************************
** BPP				BytesPerPixel : is 32 for (uint32_t*)sdl->pixels
**
** ********************************** functions ********************************
** void		sdl_init(t_sdl *sdl, const char *window_name);
** 					initialize sdl window
** void		sdl_run(t_sdl *sdl);
** 					draw sdl->pixels to sdl->screen of sdl->window
** void		cl_end(t_cl *cl);
** 					terminate and free all sdl environment
**
** void		sdl_init_window(t_sdl *sdl);
** 					initializes window, use in case of resize event
** *****************************************************************************
*/

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <stdint.h>

# define BPP			32
# define PROGRAM_NAME	"RT"

typedef struct			s_yx
{
	int					y;
	int					x;
}						t_yx;

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Surface			*screen;
	SDL_Surface			*draw_surface;
	SDL_Event			event;
	t_yx				size;
	uint32_t			*pixels;
}						t_sdl;

void					sdl_init(t_sdl *sdl, const char *window_name);
void					sdl_run(t_sdl *sdl);
void					sdl_end(t_sdl *sdl);

void					sdl_init_window(t_sdl *sdl);

#endif
