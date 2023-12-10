/* Implements gravity acceleration computation using JGM-3 coefficients for
spherical harmonic gravity model. This doesn't consider any other perturbation to
gravity for example due to presence of Sun and Moon and other planets
*/

#ifndef GRAVITYMODELJGM3_H
#define GRAVITYMODELJGM3_H

#include <gravity_model.h>

class GravityModelJgm3:public GravityModel{
public:
	GravityModelJgm3(float mean_planet_radius_m, float mu_m3ps2, float c_2_0_nd);
	~GravityModelJgm3();

	array<float, 3> GetGravityAccel(array<float, 3> const &sat_eci_location_m);

protected:
	// Dimensionless Zonal Coefficients for degree = 2 and order = 0
	float c_2_0_nd_;
};

#endif