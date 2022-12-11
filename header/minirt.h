#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "structs.h"
#	include <fcntl.h> //open

# ifdef __APPLE__ // should work in linux and mac headers
#  include "../mlx/mlx.h"
#  include <OpenGL/gl.h>//OS x libs
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
# else
#  include <GL/glut.h>
#  include <mlx.h>
# endif

# define WIDTH			1400
# define HEIGHT 		1400
# define BUFFERSIZE 	1000
# define INFO_AL		3
# define INFO_C			4
# define INFO_L			4
# define INFO_PL		4
# define INFO_SP		4
# define INFO_CY		6

//events
# define RED_CROSS		17
# define KEY_PRESS		2
# define ESC			65307

typedef struct s_elements	t_elements;
typedef struct s_counter	t_counter;
typedef struct s_elements	t_elements;
typedef struct s_amb_light	t_amb_light;
typedef struct s_light		t_light;
typedef struct s_cam		t_cam;
typedef struct s_obj		t_obj;
typedef struct s_vec		t_vec;
typedef struct s_color		t_color;

typedef	struct s_data 
{
	int			bit_per_pix;
	int			line_len;
	int			endian;
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	t_counter	*counter;
	t_elements	*elements;
} t_data;

//free.c
void	freeing_dpointer(char **paths);

//main.c
int open_file(char **argv);
int	init_A(t_data *data, char **splitted);
int	parse_line(char *line, t_data *data, char **splitted);

//init.c
void	allocating_elements(t_data *data);
int		init_elements(char **argv, t_data *data);
void	init_counter(t_data *data);

int	counting_elements(char **argv, t_data *data);
int	expected_words(int expected, char **words);
int assign_info(char **splitted);

void	controls(t_data *data);

//elements.c
int		init_a(t_data *data, char **splitted);
int		init_camera(t_data *data, char **splitted);
int		init_l(t_data *data, char **splitted);
int		init_s(t_data *data, char **splitted);
int		init_cylinder(t_data *data, char **splitted);
int		init_plane(t_data *data, char **splitted);
int		init_camera_fov(t_cam *cam, char **splitted);
int		check_boundries_vector(t_vec *vector, int min, int max);
t_vec	init_vector(char *xyz);
int		isaldigit(char **value);
int		check_colors(char *rgb, t_color *location);
int		char_to_double(char *value, double *dst);

#endif
