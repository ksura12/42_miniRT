/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:24:15 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 05:24:25 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/structs.h"
#include	"../header/minirt.h"

int	close_win(void *param);
int	key_press(int keycode, void *param);
int	printwin(int keycode, t_data *data);
int	escape(int keycode, t_data *data);

//	mlx_key_hook(data->mlx_win, &printwin, &data->img);
//  mlx_hook(data->mlx_win, KEY_PRESS, 0, key_press, data);
void	controls(t_data *data)
{
	mlx_key_hook(data->mlx_win, &escape, &data->img);
	mlx_hook(data->mlx_win, RED_CROSS, 0, close_win, data);
}

int	escape(int keycode, t_data *data)
{
	(void) data;
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

/*
int	printwin(int keycode, t_data *data)
{
	(void) data;
	printf("keycode %i", keycode);
	return (0);
}

int	key_press(int keycode, void *param)
{
//	t_data	*data;

//	data = (t_data *)param;
	(void)param;
	(void)keycode;
	return (0);
}*/

int	close_win(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
}
