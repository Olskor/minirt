/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:18:17 by jauffret          #+#    #+#             */
/*   Updated: 2024/01/10 11:09:23 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int kc, t_data *data)
{
	if (kc == XK_Escape)
	{
		close_window(data);
	}
	return (0);
}

void	hook_setup(t_data *data)
{
	mlx_loop_hook(data->mlx, &loop, data);
	mlx_hook(data->win, 4, 1L << 2, &mouse_handle, data);
	mlx_hook(data->win, 17, 1L << 2, &close_window, data);
	mlx_key_hook(data->win, key_hook, data);
}

int	mouse_handle(int button, int x, int y, t_data *data)
{
	if (button && x && y && data)
		return (0);
	return (0);
}

int	input_next(int keysym, t_data *data)
{
	if (data && keysym)
		return (0);
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym && data)
		return (0);
	return (input_next(keysym, data));
}
