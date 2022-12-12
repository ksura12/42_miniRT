#ifndef STRUCTS_H
# define STRUCTS_H

# include "minirt.h"

typedef struct s_coordenate	t_coord;
typedef struct s_elements	t_elements;
typedef struct s_amb_light	t_amb_light;
typedef struct s_light		t_light;
typedef struct s_cam		t_cam;
typedef struct s_obj		t_obj;
typedef struct s_vec		t_vec;
typedef struct s_color		t_color;

typedef struct s_counter
{
	int			ambient_light_count;
	int			light_count;
	int			camera_count;
	int			sphere_count;
	int			cylinder_count;
	int			plane_count;
	int			newline_count;
	int			create_count;
}	t_counter;

typedef struct s_elements
{
	t_amb_light	*amb_light;
	t_light		*light;
	t_cam		*camera;
	t_obj		**objects;
}	t_elements;

/**
 * @brief struct for vectors consisting out of three parameters
 * @param x [double] Value for the X-Component of the vector
 * @param y [double] Value for the Y-Component of the vector
 * @param z [double] Value for the Z-Component of the vector
 * @param f [int] Flag: 1 if vector is valid, 0 if not
*/
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
	int		f;
}	t_vec;

/**
 * @brief struct for a RGB-color consisting out of three parameters
 * @param r [int] Value for the red-content (0-255)
 * @param g [int] Value for the green-content (0-255)
 * @param b [int] Value for the blue-content (0-255)
 */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/**
 * @brief struct for any object
 * @param id [char] Identifier of the Object (c-cylinder, p-plane, s-sphere)
 * @param v_pos [t_vec] Vector for origin of Object
 * @param v_or [t_vec] Orientation Vector for Object
 * @param dia [double] diameter of the Object
 * @param h [double] Height of the Object
 * @param col [t_col] color of the Object
 */
typedef struct s_obj
{
	char	id;
	t_vec	v_pos;
	t_vec	v_orient;
	double	dia;
	double	height;
	t_color	color;
}	t_obj;

/**
 * @brief struct for Ambient Light
 * @param lr [double] lighting ratio  from (0,0 -1,0)
 * @param col [t_col] color of the light
 */
typedef struct s_amb_light
{
	double	lratio;
	t_color	color;
}	t_amb_light;

/**
 * @brief struct for Light
 * @param v_pos [t_vec] Vector for postion of the light
 * @param lr [double] lighting ratio  from (0,0 -1,0)
 * @param col [t_col] color of the light
 */
typedef struct s_light
{
	t_vec	v_pos;
	double	lratio;
	t_color	color;
}	t_light;

/**
 * @brief struct for a camera
 * @param v_pos [t_vec] Vector for postion of the camera
 * @param v_or [t_vec] Vector for the orientation of the camera
 * @param fov [int] Field of view in degrees(0,0 180)
 */
typedef struct s_cam
{
	t_vec	v_pos;
	t_vec	v_orient;
	double	angle_vert;
	double	angle_horz;
	int		fov_w;
	int		fov_h;
}	t_cam;

typedef struct s_ray
{
	t_vec	v_pos;
	t_vec	v_direct;
	double	tmax;
}	t_ray;

typedef struct s_coordenate
{
	double	x;
	double	y;
}	t_coord;

#endif
