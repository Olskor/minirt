/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:18:17 by jauffret          #+#    #+#             */
/*   Updated: 2023/04/12 14:25:25 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hook_setup(t_data *data)
{
	mlx_loop_hook(data->mlx, &loop, data);
	mlx_hook(data->win, 4, 1L << 2, &mouse_handle, data);
	mlx_hook(data->win, 2, 1L << 0, &handle_input, data);
	mlx_hook(data->win, 17, 1L << 2, &close_window, data);
}

int	mouse_handle(int button, int x, int y, t_data *data)
{
	return (0);
}

int	input_next(int keysym, t_data *data)
{
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	return (input_next(keysym, data));
}
