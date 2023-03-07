/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lskraber <lskraber@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:22 by egauthey          #+#    #+#             */
/*   Updated: 2023/03/06 17:06:46 by lskraber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"

void	printf_vec(t_vec vec)
{
	printf("x : %f\n", vec.x);
	printf("y : %f\n", vec.y);
	printf("z : %f\n", vec.z);
	printf("\n");
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data	data;

	data.changed = 1;
	data.current = 0;
	mrt_parsing(av, &data);
	initialise_viewport(&data);
	// free (data.objs);
	// free_obj_list(data.chaos);

	int i = 0;
	while(data.objs[i])
	 	print_object(*data.objs[i++]);
	
	// print_new_list(&data);

	// printf("count: %i\n", data.count.sp_count);
	init_window(&data);// --normal
	init_image(&data, WIDTH, HEIGHT, &data.img);

	render(&data);
	// create_thread(&data);
	mlx_hook(data.win, 17, 1L << 2, close_win, &data);
	mlx_key_hook(data.win, event_handler, &data);
	//mlx_key_hook(data.win, print_key, &data);
	mlx_loop(data.mlx);
	return (0);
}

// TO DO implement depth buffer;
