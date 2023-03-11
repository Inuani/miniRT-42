#include "../../includes/minirt.h"

void	get_cylindre(t_data *d)
{
	t_object	*tmp;
	int	i;

	tmp = d->chaos;
	i = 2 + d->count.l_count + d->count.sp_count + d->count.pl_count;
	while(tmp)
	{
		if (tmp->type == CYLINDER)
		{
			d->objs[i] = tmp;
			i++;
		}
		tmp = tmp->next;
	}
}

void	cy_img_init(t_data *d, t_tok **lst, t_cylinder *cur)
{
	char	*n_img;
	char	*n_path;
	char	*xpm;

	n_img = NULL;
	n_path = NULL;
	xpm = NULL;
	*lst = (*lst)->next;
	set_xpm_path(&n_img, &n_path, &xpm, &(*lst)->s);
	cur->xpm.img = mlx_xpm_file_to_image(d->mlx, xpm, &cur->xpm.wdth, &cur->xpm.hgt);
	cur->xpm.addr = mlx_get_data_addr(cur->xpm.img, &cur->xpm.bits_per_pixel, &cur->xpm.line_length, &cur->xpm.endian);
	cur->n_map.img = mlx_xpm_file_to_image(d->mlx, n_img, &cur->n_map.wdth, &cur->n_map.hgt);
	cur->n_map.addr = mlx_get_data_addr(cur->n_map.img, &cur->n_map.bits_per_pixel, &cur->n_map.line_length, &cur->n_map.endian);
	free(n_path);
	free(n_img);
	free(xpm);
}

void	set_cyl_prop(t_tok **lst, t_cylinder *inst)
{
	*lst = (*lst)->next;
	inst->center.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->center.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->center.z = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.z = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->radius = (ft_atof((*lst)->s) / 2.0);
	*lst = (*lst)->next;
	inst->hgt = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.z = ft_atof((*lst)->s);
	inst->orient = vec_unit(inst->orient);
}

int	add_cylinder(t_data *d, t_tok *lst)
{
	t_object	*new;
	t_cylinder	inst;
	int			nb;

	nb = calc_nb_prop(lst);
	if (nb != 11 && nb != 12)
		exit_error(ERR_PROPERTIES, 1);
	inst.flg = 0;
	set_cyl_prop(&lst, &inst);
	if (nb == 12)
	{
		if (!ft_strncmp(lst->next->s, "damier", 6))
			inst.flg = 1;
		else
		{
			cy_img_init(d, &lst, &inst);
			inst.flg = 2;
		}
	}
	new = create_object(CYLINDER, &inst);
	add_object_to_list(&d->chaos, new);
	free_tok(d);
	return (1);
}