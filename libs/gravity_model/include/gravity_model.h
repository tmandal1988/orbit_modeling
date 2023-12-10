/*Creates a base grvaity class which then can be inherited by various gravity classes
for example JGM-3 gravity model
*/

#ifndef GRAVITYMODEL_H
#define GRAVITYMODEL_H

#include <array>

using namespace std;

/* Using float data type but this class can be easily templatized, for better readablity
append units at the end of variables if it makes sense
*/

class GravityModel{
public:
	GravityModel(float mean_planet_radius_m, float mu_m3ps2):
	mean_planet_radius_m_(mean_planet_radius_m),
	mu_m3ps2_(mu_m3ps2){};

	~GravityModel(){};

	// Function to compute Gravity Acceleration components in ECI frame
	virtual array<float, 3> GetGravityAccel(array<float, 3> const &sat_eci_location_m) = 0;

protected:
	float mean_planet_radius_m_;

	// mu = G*M for the planet
	float mu_m3ps2_;
};

#endif