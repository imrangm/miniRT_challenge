#include "../../includes/minirt.h"

t_vector	vector(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vector	negate_vector(t_vector vec)
{
	t_vector	ret;

	ret = vector(0, 0, 0);
	if (vec.x)
		ret.x = vec.x * -1;
	if (vec.y)
		ret.y = vec.y * -1;
	if (vec.z)
		ret.z = vec.z * -1;
	return (ret);
}
