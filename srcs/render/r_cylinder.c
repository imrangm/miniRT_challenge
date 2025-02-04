#include "../../includes/minirt.h"

int	check_cap(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((pow(x, 2) + pow(z, 2)) <= 1)
		return (1);
	return (0);
}

t_intersect	intersect_caps(t_shape *cy, t_ray ray, t_intersect *i,t_list **intersections_lst)
{
	double			min;
	double			max;

	max = cy->height / 2.0;
	min = -1.0 * max;
	i->t[2] = (min - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, i->t[2]))
	{
		if (i->t[2] > EPSILON)
			create_intersection(intersections_lst,i->t[2], cy);
	}
	else
		i->t[2] = 0;
	i->t[3] = (max - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, i->t[3]))
	{
		if (i->t[2] > EPSILON)
			create_intersection(intersections_lst,i->t[3], cy);
	}
	else
		i->t[3] = 0;
	return (*i);
}

void	init_intersect(t_intersect *inter1)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		(*inter1).t[i] = 0;
		i++;
	}
	(*inter1).count = 0;
}

// int get_list_count(t_list **ls)
// {
// 	int i;
// 	i = 0;	

// 	t_list **st;
// 	st =  ls;

// 	while (*st)
// 	{
// 		*st = (*st)->next;
// 		i++;
// 	}
// 	printf("\n%d\n", i);
// 	return (i);
// }

void create_intersection(t_list **intersections_list,double t, t_shape *shape)
{
	t_intersection *inter;
	inter = malloc (sizeof (t_intersection));
	inter->object = shape;
	inter->t = t;
	inter->count = 1;
	if (*intersections_list == NULL)
	{
		// 
		*intersections_list = ft_lstnew(inter);
	}
	else
	{
		ft_lstadd_back(intersections_list, ft_lstnew(inter));
	}
	// 
}

void	check_intersect(t_intersect *inter1, double min, double max, t_ray ray, t_list **intersections_list,t_shape *s)
{
	double		y0_y1[2];
	double		temp;

	if ((*inter1).t[0] > (*inter1).t[1])
	{
		temp = (*inter1).t[0];
		(*inter1).t[0] = (*inter1).t[1];
		(*inter1).t[1] = temp;
	}
	y0_y1[0] = ray.origin.y + ((*inter1).t[0] * ray.direction.y);
	y0_y1[1] = ray.origin.y + ((*inter1).t[1] * ray.direction.y);
	if (min < y0_y1[0] && y0_y1[0] < max)
	{
		if (inter1->t[0] > EPSILON)
			create_intersection(intersections_list ,inter1->t[0],s);
	}
	else
		(*inter1).t[0] = 0;
	if (min < y0_y1[1] && y0_y1[1] < max)
	{
		if (inter1->t[0] > EPSILON)
			create_intersection(intersections_list ,inter1->t[1],s);
	}
	else
		(*inter1).t[1] = 0;
}

void	set_intersect(t_intersect *inter1, t_ray ray, double min, double max, t_list **intersections_list, t_shape *s)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	b = (2 * ray.origin.x * ray.direction.x)
		+ (2 * ray.origin.z * ray.direction.z);
	c = (pow(ray.origin.x, 2) + pow(ray.origin.z, 2)) - 1.0;
	disc = pow(b, 2) - (4 * a * c);
	(*inter1).t[0] = (((-1 * b) - sqrt(disc)) / (2 * a));
	(*inter1).t[1] = (((-1 * b) + sqrt(disc)) / (2 * a));
	if (disc >= 0 && (double_equal(a, 0) == 0))
		check_intersect(inter1, min, max, ray,intersections_list, s);
	else
	{
		(*inter1).t[0] = 0;
		(*inter1).t[1] = 0;
	}
}
