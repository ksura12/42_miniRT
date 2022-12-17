#include	"../header/minirt.h"

/**
 * @brief multiplies vector with 4x4matrix
 * 
 * @param vec vector to convert
 * @param mat (double) double pointer to matrix for convertion of vector
 * @return t_vec converted vector
 */
t_vec	mult_vec_mat(t_vec vec, double **mat)
{
	t_vec	ret;

	ret.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0] + mat[3][0];
	ret.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1] + mat[3][1];
	ret.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2] + mat[3][2];
	ret.f = 1;
	return (ret);
}

/**
 * @brief converts degrees to radian
 * 
 * @param deg 
 * @return double rad
 */
double	degtorad(double deg)
{
	return(deg * M_PI / 180);
}

t_vec	make_opposite_vector(t_vec vec)
{
	t_vec	opp;

	opp.x = -vec.x;
	opp.y = -vec.y;
	opp.z = -vec.z;
	return(opp);
}