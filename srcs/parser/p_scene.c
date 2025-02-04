#include "../../includes/minirt.h"

int	set_error_obj(int err_code, char *msg, t_data *scene_data)
{
	scene_data->error.message = msg;
	scene_data->error.error_code = err_code;
	return (0);
}

void	init_scene(t_data *scene_data)
{
	scene_data->num_objs.num_ambiance = 0;
	scene_data->num_objs.num_cam = 0;
	scene_data->num_objs.num_cy = 0;
	scene_data->num_objs.num_light = 0;
	scene_data->num_objs.num_pl = 0;
	scene_data->num_objs.num_sp = 0;
}

int	parse_line(int fd, t_data *scene_data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line && *line != '#' && *line != '\n')
		{
			if (!parse_current_line(line, scene_data))
			{
				free_memmory(&line);
				return (0);
			}
		}
		else if (!line)
		{
			free_memmory(&line);
			break ;
		}
		free_memmory(&line);
	}
	return (1);
}

int	parse_scene(char *file_name, t_data *scene_data)
{
	int		fd;
	t_list	*shapes;
	t_shape	*sp;

	init_scene(scene_data);
	if (check_file_name(file_name))
		return (set_error_obj(1, "FILE EXTENTION IS INCORRECT", scene_data));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (set_error_obj(2, "ERROR OPENING FILE", scene_data));
	if (!parse_line(fd, scene_data))
		return (0);
	shapes = scene_data->wrld.shapes;
	while (shapes)
	{	
		sp = (t_shape *) shapes->content;
		sp->material.ambient = scene_data->amb_ratio;
		shapes = shapes->next;
	}
	close(fd);
	return (1);
}
