#include "main.h"

/*
Checks the current type identifier, and checks if everything is correct,
depending on the type. If the line is empty, it ignores it.
All identifiers will first be checked, and if everything is valid,
the values will be saved.
@param type_id The first field of each element, the type
identifier, like 'A', 'sp', etc.
@param scene->pars.error_code A variable in the parsing struct that stores
an error code. If the error code is not 0, the program will print an error
message and exit.*/
int	check_and_set_single_element(t_scene *scene)
{
	char	*type_id;

	type_id = scene->pars.elem_data[0];
	if (!type_id)
		scene->pars.error_code = 0;
	else if (!ft_strcmp(type_id, "A") || !ft_strcmp(type_id, "A\n"))
		scene->pars.error_code = parse_and_set_ambience(scene);
	else if (!ft_strcmp(type_id, "C") || !ft_strcmp(type_id, "C\n"))
		scene->pars.error_code = parse_and_set_camera(scene);
	else if (!ft_strcmp(type_id, "L") || !ft_strcmp(type_id, "L\n"))
		scene->pars.error_code = parse_and_set_light(scene);
	else if (!ft_strcmp(type_id, "sp") || !ft_strcmp(type_id, "sp\n"))
		scene->pars.error_code = parse_sphere(scene);
	else if (!ft_strcmp(type_id, "pl") || !ft_strcmp(type_id, "pl\n"))
		scene->pars.error_code = parse_plane(scene);
	else if (!ft_strcmp(type_id, "cy") || !ft_strcmp(type_id, "cy\n"))
		scene->pars.error_code = parse_cylinder(scene);
	else if (!ft_strcmp(type_id, "\n") || type_id[0] == '#')
		scene->pars.error_code = 0;
	else
		scene->pars.error_code = ERR_INVALID_IDENTIFIER;
	return (scene->pars.error_code);
}
