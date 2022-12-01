
#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * @brief struct for vectors consisting out of three parameters
 * @param x [double] Value for the X-Component of the vector
 * @param y [double] Value for the Y-Component of the vector
 * @param z [double] Value for the Z-Component of the vector
*/
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

/**
 * @brief struct for a RGB-color consisting out of three parameters
 * @param r [int] Value for the red-content (0-255)
 * @param g [int] Value for the green-content (0-255)
 * @param b [int] Value for the blue-content (0-255)
 */
typedef struct s_col
{
	int	r;
	int	g;
	int	b;
}	t_col;

/**
 * @brief struct for any object
 * @param id [char] Identifier of the Object (c-cylinder, p-plane, s-sphere)
 * @param v_pos [t_vec] Vector for origin of Object
 * @param v_or [t_vec] Orientation Vector for Object
 * @param rad [double] Radius of the Object
 * @param h [double] Height of the Object
 * @param col [t_col] color of the Object
 */
typedef struct s_obj
{
	char	id;
	t_vec	v_pos;
	t_vec	v_or;
	double	rad;
	double	h;
	t_col	col;
}	t_obj;

/**
 * @brief struct for Ambient Light
 * @param lr [double] lighting ratio  from (0,0 -1,0)
 * @param col [t_col] color of the light
 */
typedef struct s_al
{
	double	lr;
	t_col	col;
}	t_al;

/**
 * @brief struct for Light
 * @param v_pos [t_vec] Vector for postion of the light
 * @param lr [double] lighting ratio  from (0,0 -1,0)
 * @param col [t_col] color of the light
 */
typedef struct s_l
{
	t_vec	v_pos;
	double	lr;
	t_col	col;
}	t_l;

/**
 * @brief struct for a camera
 * @param v_pos [t_vec] Vector for postion of the camera
 * @param v_or [t_vec] Vector for the orientation of the camera
 * @param fov [int] Field of view in degrees(0,0 -180)
 */
typedef struct s_cam
{
	t_vec	v_pos;
	t_vec	v_or;
	int		fov;
}	t_cam;


#endif