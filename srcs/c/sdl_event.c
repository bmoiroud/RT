/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:25:40 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/08 15:24:30 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_move(t_key *keys, t_eye *eye, t_vector *m)
{
	int		i;

	i = ((keys->shift) ? 2.0 : 1.0);
	if (keys->w)
		eye->pos = ft_add_vector(eye->pos, ft_scale_vector(m[0], SPEED_V * i));
	else if (keys->s)
		eye->pos = ft_sub_vector(eye->pos, ft_scale_vector(m[0], SPEED_V * i));
	if (keys->a)
		eye->pos = ft_add_vector(eye->pos, ft_scale_vector(m[1], SPEED_V * i));
	else if (keys->d)
		eye->pos = ft_sub_vector(eye->pos, ft_scale_vector(m[1], SPEED_V * i));
	if (keys->lctrl)
		eye->pos = ft_sub_vector(eye->pos, ft_scale_vector(m[2], SPEED_H * i));
	else if (keys->space)
		eye->pos = ft_add_vector(eye->pos, ft_scale_vector(m[2], SPEED_H * i));
	if (keys->e)
		ft_rotate_y(eye, m, 1);
	else if (keys->q)
		ft_rotate_y(eye, m, -1);
	if (keys->down)
		ft_rotate_z(eye, m, 1);
	else if (keys->up)
		ft_rotate_z(eye, m, -1);
}

static int	sdl_keyboard(t_key *keys, t_eye *eye, t_vector *m, t_rt *rt)
{
	const Uint8		*state = SDL_GetKeyboardState(NULL);

	ft_bzero(keys, sizeof(t_key));
	keys->w = (state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S]);
	keys->s = (state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_W]);
	keys->a = (state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]);
	keys->d = (state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_A]);
	keys->lctrl = (state[SDL_SCANCODE_LCTRL] && !state[SDL_SCANCODE_SPACE]);
	keys->space = (state[SDL_SCANCODE_SPACE] && !state[SDL_SCANCODE_LCTRL]);
	keys->e = (state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_Q]);
	keys->q = (state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_E]);
	keys->down = (state[SDL_SCANCODE_DOWN] && !state[SDL_SCANCODE_UP]);
	keys->up = (state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN]);
	keys->shift = state[SDL_SCANCODE_LSHIFT];
	if (state[SDL_SCANCODE_1])
		rt->effects = (rt->effects) ? 0 : 1;
	ft_move(keys, eye, m);
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_W] || \
		state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D] || \
		state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_LCTRL] || \
		state[SDL_SCANCODE_E] || state[SDL_SCANCODE_Q] || \
		state[SDL_SCANCODE_1] || state[SDL_SCANCODE_UP] || \
		state[SDL_SCANCODE_DOWN])
		return (1);
	return (0);
}

int			sdl_events(t_sdl *sdl, t_key *keys, t_rt *rt)
{
	if (SDL_PollEvent(&sdl->event))
	{
		if (sdl->event.key.keysym.sym == SDLK_ESCAPE || \
			sdl->event.window.type == SDL_WINDOWEVENT_CLOSE || \
			sdl->event.type == SDL_QUIT)
			exit(EXIT_SUCCESS);
		if (sdl->event.type == SDL_WINDOWEVENT &&
			sdl->event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			sdl_init_window(sdl);
			rt->eye.aspect = sdl->size.x / (double)sdl->size.y;
			return (EVENT_UPDATE);
		}
		if (sdl_keyboard(keys, &rt->eye, rt->m, rt))
			return (EVENT_UPDATE);
	}
	return (EVENT_IDLE);
}

// SDL_GetMouseState(&x, &y);
// SDL_WarpMouseInWindow(env->win, env->ar.win_w >> 1, env->ar.win_h >> 1);
// SDL_ShowCursor(SDL_DISABLE);
// SDL_ShowCursor(SDL_ENABLE);