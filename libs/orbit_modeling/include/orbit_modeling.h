/*Implements a very simple orbit simulation by integrating acceleration over time. Tested fo
LEO from altitude of 500km to 2000km above mean Earth radius
*/

#ifndef ORBITMODELING_H
#define ORBITMODELING_H

#include <gravity_model.h>


class OrbitModeling{
public:
	/* Use a default sample time of 0.01s
	for orbit simulation
	*/
	OrbitModeling(array<float, 3> sat_init_eci_pos_m, array<float, 3> sat_init_eci_vel_mps, float sample_time_s = 0.01);
	~OrbitModeling(){};
	/* This propogates the satelite position
	*/
	void Step(GravityModel &gravity_model);

	/* Setter and Getter functions
	*/
	void SetSatEciPos(array<float, 3> const &sat_eci_pos_m);
	void SetSatEciVel(array<float, 3> const &sat_eci_vel_m);
	array<float, 3> GetCurrSatEciPos();
	array<float, 3> GetCurrSatEciVel();


protected:
	// Variable to store current satellite position and velocity in ECI frame
	array<float, 3> sat_curr_eci_pos_m_;
	array<float, 3> sat_curr_eci_vel_mps_;

	float sample_time_s_;

};

#endif