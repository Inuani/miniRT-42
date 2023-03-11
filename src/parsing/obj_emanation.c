#include "../../includes/minirt.h"

int	calc_nb_prop(t_tok *lst)
{
	t_tok	*tmp;
	int		nb;

	nb = 0;
	tmp = lst;
	while(tmp)
	{
		if (tmp->type == 1 || tmp->type == 2)
			nb++;
		tmp = tmp->next;
	}
	return (nb);
}


void	add_ambiant(t_data *d, t_tok *lst)
{
	t_object	*new;
	t_ambiant	inst;
	int			nb;

	nb = calc_nb_prop(lst);
	if (nb != 4)
		exit_error(ERR_PROPERTIES, 1); // make a personalised error for ambiant etc. ?
	lst = lst->next;
	inst.light_ratio = ft_atof(lst->s);
	lst = lst->next;
	inst.colors.x = ft_atof(lst->s);
	lst = lst->next;;
	inst.colors.y = ft_atof(lst->s);
	lst = lst->next;
	inst.colors.z = ft_atof(lst->s);
	new = create_object(AMBIANT, &inst);
	add_object_to_list(&d->chaos, new);
	free_tok(d);
	// free_tok_from_end(lst);
	// d->lst = NULL;
}

void	set_camera_prop(t_tok **lst, t_cam *inst)
{
	*lst = (*lst)->next;
	inst->pos.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->pos.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->pos.z = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.z = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->fov = ft_atof((*lst)->s);
	inst->orient = vec_unit(inst->orient);
	if (!inst->orient.x && !inst->orient.z)
		inst->up = vec_cross(inst->orient, (t_vec) {0, 0, 1});
	else
		inst->up = (t_vec) {0, 1, 0};
	inst->up = vec_unit(inst->up);
	inst->right = vec_cross(inst->orient, inst->up);
	inst->right = vec_unit(inst->right);
}

void	add_camera(t_data *d, t_tok *lst)
{
	t_object	*new;
	t_cam		inst;
	int			nb;

	//TRANSFORMER LE VECTEUR ORIENTATION EN VECTEUR UNITAIRE.
	// OU BIEN (plutot) RETOURNER UNE ERREUR SI CE N EST PAS UN.
	nb = calc_nb_prop(lst);
	if (nb != 7)
		exit_error(ERR_PROPERTIES, 1);
	set_camera_prop(&lst, &inst);
	// lst = lst->next;
	// inst.pos.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.pos.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.pos.z = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.z = ft_atof(lst->s);
	// lst = lst->next;
	// inst.fov = ft_atof(lst->s);
	// inst.orient = vec_unit(inst.orient);
	// if (!inst.orient.x && !inst.orient.z)
	// 	inst.up = vec_cross(inst.orient, (t_vec) {0, 0, 1});
	// else
	// 	inst.up = (t_vec) {0, 1, 0};
	// inst.up = vec_unit(inst.up);
	// inst.right = vec_cross(inst.orient, inst.up);
	// inst.right = vec_unit(inst.right);
	new = create_object(CAMERA, &inst);
	add_object_to_list(&d->chaos, new);
	free_tok(d);
	// free_tok_from_end(lst);
	// d->lst = NULL;
}

void	set_light_prop(t_tok **lst, t_light *inst)
{
	*lst = (*lst)->next;
	inst->pos.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->pos.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->pos.z = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->light_ratio = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.z = ft_atof((*lst)->s);
}

int	add_light(t_data *d, t_tok *lst)
{
	t_object	*new;
	t_light		inst;
	int			nb;

	nb = calc_nb_prop(lst);
	if (nb != 7)
		exit_error(ERR_PROPERTIES, 1);
	set_light_prop(&lst, &inst);
	// lst = lst->next;
	// inst.pos.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.pos.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.pos.z = ft_atof(lst->s);
	// lst = lst->next;
	// inst.light_ratio = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.z = ft_atof(lst->s);
	new = create_object(LIGHT, &inst);
	add_object_to_list(&d->chaos, new);
	free_tok(d);
	// free_tok_from_end(lst);
	// d->lst = NULL;
	return (1);
}

void	set_xpm_path(char **n_img, char **n_path, char **xpm, char **img)
{
	*n_path = ft_strjoin("images/", "n_");
	if (!*n_path)
		exit_error(ERR_MALLOC, 260);
	*n_img = ft_strjoin(*n_path, *img);
	if (!n_img)
		exit_error(ERR_MALLOC, 260);
	*xpm = ft_strjoin("images/", *img);
	if (!xpm)
		exit_error(ERR_MALLOC, 260);
	if (access(*xpm, F_OK) != 0)
		exit_error(ERR_XPM_IMG, 1);
	if (access(*n_img, F_OK) != 0)
		exit_error(ERR_XPM_IMG, 1);
}

void	sp_img_init(t_data *d, t_tok **lst, t_sphere *cur)
{
	char	*n_img;
	char	*n_path;
	char	*xpm;

	n_img = NULL;
	n_path = NULL;
	xpm = NULL;
	*lst = (*lst)->next;
	set_xpm_path(&n_img, &n_path, &xpm, &(*lst)->s);
	// n_path = ft_strjoin("images/", "n_");
	// if (!n_path)
	// 	exit_error(ERR_MALLOC, 260);
	// n_img = ft_strjoin(n_path, (*lst)->s);
	// if (!n_img)
	// 	exit_error(ERR_MALLOC, 260);
	// xpm = ft_strjoin("images/", (*lst)->s);
	// if (!xpm)
	// 	exit_error(ERR_MALLOC, 260);
	// if (access(xpm, F_OK) != 0)
	// 	exit_error(ERR_XPM_IMG, 1);
	// if (access(n_img, F_OK) != 0)
	// 	exit_error(ERR_XPM_IMG, 1);
	cur->xpm.img = mlx_xpm_file_to_image(d->mlx, xpm, &cur->xpm.wdth, &cur->xpm.hgt);
	cur->xpm.addr = mlx_get_data_addr(cur->xpm.img, &cur->xpm.bits_per_pixel, &cur->xpm.line_length, &cur->xpm.endian);
	cur->n_map.img = mlx_xpm_file_to_image(d->mlx, n_img, &cur->n_map.wdth, &cur->n_map.hgt);
	cur->n_map.addr = mlx_get_data_addr(cur->n_map.img, &cur->n_map.bits_per_pixel, &cur->n_map.line_length, &cur->n_map.endian);
	free(n_path);
	free(n_img);
	free(xpm);
}

void	set_sp_prop(t_tok **lst, t_sphere *inst)
{
	*lst = (*lst)->next;
	inst->center.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->center.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->center.z = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->radius = (ft_atof((*lst)->s) / 2.0);
	*lst = (*lst)->next;
	inst->colors.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.z = ft_atof((*lst)->s);
	inst->up = (t_vec) {0, 1, 0};
	inst->right = (t_vec) {1, 0, 0};
}

int	add_sphere(t_data *d, t_tok *lst)
{
	t_object	*new;
	t_sphere	inst;
	int			nb;

	nb = calc_nb_prop(lst);
	if (nb != 7 && nb != 8)
		exit_error(ERR_PROPERTIES, 1);
	inst.flg = 0;
	set_sp_prop(&lst, &inst);
	// lst = lst->next;
	// inst.center.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.center.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.center.z = ft_atof(lst->s);
	// lst = lst->next;
	// inst.radius = (ft_atof(lst->s) / 2.0);
	// lst = lst->next;
	// inst.colors.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.z = ft_atof(lst->s);
	// inst.up = (t_vec) {0, 1, 0};
	// inst.right = (t_vec) {1, 0, 0};
	if (nb == 8)
	{
		if (!ft_strncmp(lst->next->s, "damier", 6))
			inst.flg = 1;
		else
		{
			sp_img_init(d, &lst, &inst);
			inst.flg = 2;
		}
	}
	// printf("flg : %d\n", inst.flg);
	new = create_object(SPHERE, &inst);
	add_object_to_list(&d->chaos, new);
	free_tok(d);
	// free_tok_from_end(lst);
	// d->lst = NULL;
	return (1);
}

void	set_plane_prop(t_tok **lst, t_plane *inst)
{
	*lst = (*lst)->next;
	inst->point.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->point.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->point.z = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.z = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.z = ft_atof((*lst)->s);
	inst->orient = vec_unit(inst->orient);
}

int	add_plane(t_data *d, t_tok *lst)
{
	t_object	*new;
	t_plane		inst;
	int			nb;

	nb = calc_nb_prop(lst);
	if (nb != 9)
		exit_error(ERR_PROPERTIES, 1);
	set_plane_prop(&lst, &inst);
	// lst = lst->next;
	// inst.point.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.point.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.point.z = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.z = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.z = ft_atof(lst->s);
	// inst.orient = vec_unit(inst.orient);
	new = create_object(PLANE, &inst);
	add_object_to_list(&d->chaos, new);
	free_tok(d);
	// free_tok_from_end(lst);
	// d->lst = NULL;
	return (1);
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
	set_cyl_prop(&lst, &inst);
	// lst = lst->next;
	// inst.center.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.center.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.center.z = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.z = ft_atof(lst->s);
	// lst = lst->next;
	// inst.radius = (ft_atof(lst->s) / 2.0);
	// lst = lst->next;
	// inst.hgt = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.z = ft_atof(lst->s);
	// inst.orient = vec_unit(inst.orient);
	
	if (nb == 12)
	{
		cy_img_init(d, &lst, &inst);
	}
	new = create_object(CYLINDER, &inst);
	add_object_to_list(&d->chaos, new);
	free_tok(d);
	// free_tok_from_end(lst);
	// d->lst = NULL;
	return (1);
}

void	set_hp_prop(t_tok **lst, t_hyperboloid *inst)
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

int	add_hyperboloid(t_data *d, t_tok *lst)
{
	t_object		*new;
	t_hyperboloid	inst;
	int				nb;

	nb = calc_nb_prop(lst);
	if (nb != 11)
		exit_error(ERR_PROPERTIES, 1);
	// print_token(&lst);
	set_hp_prop(&lst, &inst);
	// lst = lst->next;
	// inst.center.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.center.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.center.z = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.orient.z = ft_atof(lst->s);
	// lst = lst->next;
	// inst.radius = (ft_atof(lst->s) / 2.0);
	// lst = lst->next;
	// inst.hgt = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.x = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.y = ft_atof(lst->s);
	// lst = lst->next;
	// inst.colors.z = ft_atof(lst->s);
	// inst.orient = vec_unit(inst.orient);
	new = create_object(HYPERBOLOID, &inst);
	add_object_to_list(&d->chaos, new);
	free_tok(d);
	// free_tok_from_end(lst);
	// d->lst = NULL;
	return (1);
}

void	what_obj(t_data *d, char *obj)
{
	if (!ft_strncmp(obj, "A", 1) && obj[1] == 0)
		add_ambiant(d, d->lst);
	else if (!ft_strncmp(obj, "C", 1) && obj[1] == 0)
		add_camera(d, d->lst);
	else if (!ft_strncmp(obj, "L", 1) && obj[1] == 0)
		d->count.l_count += add_light(d, d->lst);
	else if (!ft_strncmp(obj, "sp", 2) && obj[2] == 0)
		d->count.sp_count += add_sphere(d, d->lst);
	else if (!ft_strncmp(obj, "pl", 2) && obj[2] == 0)
		d->count.pl_count += add_plane(d, d->lst);
	else if (!ft_strncmp(obj, "cy", 2) && obj[2] == 0)
	{
		
		d->count.cy_count += add_cylinder(d, d->lst);
	}
	else if (!ft_strncmp(obj, "hy", 2) && obj[2] == 0)
		d->count.hy_count += add_hyperboloid(d, d->lst);
	else
		exit_error(ERR_OBJ, 1);
}

void	obj_eman(t_data *d)
{
	t_tok	*tmp;

	tmp = d->lst;
	while(tmp)
	{
		if (tmp->type == 0)
		{
			what_obj(d, tmp->s);
			break ;
		}
		tmp = tmp->next;
	}
}
