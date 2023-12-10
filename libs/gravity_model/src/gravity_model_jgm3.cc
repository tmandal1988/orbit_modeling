#include <gravity_model_jgm3.h>

GravityModelJgm3::GravityModelJgm3(float mean_planet_radius_m, float mu_m3ps2, float c_2_0_nd):
				  GravityModel(mean_planet_radius_m, mu_m3ps2),
				  c_2_0_nd_(c_2_0_nd){

				  }

GravityModelJgm3::~GravityModelJgm3(){

}

/* Returns an array of length 3 containing X, Y, Z components of
gravity acceleration (m/s^2) in Earth Centered Inertial (ECI) frame. This does
not account for Tesseral and Sectoral terms as they are significantly
smaller than zonal terms and hence not consequential for few meters level accuracy.
Also only 2nd degree Zonal coefficients are used since in JGM3 model 3rd degree and higher 
Zonal coefficients are more than 3 orders of magnitude smaller and also to keep
the computations simple.
ref: 
1. https://spsweb.fltops.jpl.nasa.gov/portaldataops/mpg/MPG_Docs/Source%20Docs/gravity-SphericalHarmonics.pdf
2. https://people.engineering.osu.edu/sites/default/files/2022-10/Kassas_Orbit_modeling_for_simultaneous_tracking_and_navigation_using_LEO_satellite_signals.pdf
3. https://en.wikipedia.org/wiki/Geopotential_model
*/
array<float, 3> GravityModelJgm3::GetGravityAccel(array<float, 3> const &sat_eci_location_m){
	float x_m, y_m, z_m;
	// Extract individual components of satellite ECI location
	x_m = sat_eci_location_m[0];
	y_m = sat_eci_location_m[1];
	z_m = sat_eci_location_m[2];

	// Compute the square of distance of the satellite from the center of ECI
	float sat_r_m2 = pow(x_m, 2) + pow(y_m, 2) + pow(z_m, 2);


	array<float, 3> gravity_accel_mps2;

	// Temp variables so that we don't have to compute same number more than once
	float temp_mu_over_r = this->mu_m3ps2_/sat_r_m2;
	float temp_radius_over_r = pow(this->mean_planet_radius_m_, 2)/sat_r_m2;
	float temp_sat_r_m = sqrt(sat_r_m2);
	float temp_z_over_r = pow(z_m, 2)/sat_r_m2;

	// Compute ECI X, Y Z acceleration due to gravity
	gravity_accel_mps2[0] = -temp_mu_over_r*x_m/temp_sat_r_m - temp_mu_over_r*temp_radius_over_r*c_2_0_nd_*( 7.5*temp_z_over_r - 1.5)*x_m/temp_sat_r_m;
	gravity_accel_mps2[1] = -temp_mu_over_r*y_m/temp_sat_r_m - temp_mu_over_r*temp_radius_over_r*c_2_0_nd_*( 7.5*temp_z_over_r - 1.5)*y_m/temp_sat_r_m;
	gravity_accel_mps2[2] = -temp_mu_over_r*z_m/temp_sat_r_m - temp_mu_over_r*temp_radius_over_r*c_2_0_nd_*( 7.5*temp_z_over_r - 4.5)*z_m/temp_sat_r_m;

	return gravity_accel_mps2;

}