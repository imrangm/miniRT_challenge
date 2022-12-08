#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 500
# define HEIGHT 500

# define KEY_ESC 53
# define ON_DESTROY 17
# define TRUE 1
# define FALSE 0

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libs/mlx/mac/mlx.h"
# include "../libs/libft/libft.h"
# define EPSILON 0.00001
# include "parse.h"
# include "maths.h"
# include "utils.h"
# include "render.h"

int				verify_digits(char **str);
int				comma_count(char *str);
int				set_error_obj(int err_code, char *msg, t_data *scene_data);
double			**normal_rotation_matrix(t_tuple normal);
void			free_matrix(double **arr, int size);
void			print_vector(t_vector vector);
int				double_equal(double a, double b);
void			print_point(t_point point);
void			print_matrix(double **mat, int col);
void			print_error_msg_and_exit(char *error_msg, t_data *scene_data);
void			default_world(t_data *scene_data);
t_color			color(double red, double green, double blue);
t_camera2		camera(double hsize, double vsize, double field_of_view);
double			**view_transform(t_point from, t_point to, t_vector up);
void			render(t_camera2 cam, t_world wrld, t_data *scene_data);

// tuples
t_tuple			tuple(double x, double y, double z, double w);
t_point			point(double x, double y, double z);
t_tuple			point_tp(t_point p);

// utils
t_ray			ray(t_point p, t_vector v);
t_intersection	*hit(t_list *xs);
t_comps			prepare_computations(t_intersection *i, t_ray r);
t_vector		local_normal_at_sphere(t_point obj_point, t_point point);
t_vector		local_normal_at_cylinder(double h, t_point pnt);
t_vector		local_normal_at_plane(void);
t_color			shade_hit(t_world w, t_comps comps);
t_color			color_at(t_world w, t_ray r);
void		local_intersect_plane(t_shape *s, t_list **intersections_lst);
void		local_intersect_sphere(t_shape *s, t_list **intersections_lst);
t_intersect		local_intersect_cylinder(t_shape *s, t_ray r,
					t_list **intersections_list);
t_list			*intersect_world(t_world w, t_ray r);
void			print_parsed_values(t_data *scene_data);
t_ray			transform(t_ray r, double **m);
t_light			point_light(t_point pos, t_color intensity);
t_point			position(t_ray r, float num);
t_vector		normal_at(t_shape *s, t_point p);
t_intersect		intersect_sphere(t_shape *s, t_ray r);
double			determinant(double **mat, int size);
double			**submatrix(double **mat, int size, int row, int col);
double			cofactor(double **mat, int size, int row, int col);
void			create_intersection(t_list **intersections_list, double t,
					t_shape *shape);
#endif