#include <orbit_modeling.h>
#include <iostream>

OrbitModeling::OrbitModeling(array<float, 3> sat_init_eci_pos_m, array<float, 3> sat_init_eci_vel_mps, float sample_time_s):
							sat_curr_eci_pos_m_(sat_init_eci_pos_m),
							sat_curr_eci_vel_mps_(sat_init_eci_vel_mps),
							sample_time_s_(sample_time_s){

							}


/* This functions sets the current ECI position of the satellite, this can be used for example
after a simulation run to reset the satellite position to some other initial ECI position to rerun
the simulation
*/
void OrbitModeling::SetSatEciPos(array<float, 3> const &sat_eci_pos_m){
	sat_curr_eci_pos_m_ = sat_eci_pos_m;
}

/* This functions sets the current ECI velocity of the satellite, this can be used for example
after a simulation run to reset the satellite velocity to some other initial condition to rerun
the simulation
*/
void OrbitModeling::SetSatEciVel(array<float, 3> const &sat_eci_vel_mps){
	sat_curr_eci_vel_mps_ = sat_eci_vel_mps;
}

/* Function to get the current satellite ECI position
*/
array<float, 3> OrbitModeling::GetCurrSatEciPos(){
	return sat_curr_eci_pos_m_;
}

/* Function to get the current satellite ECI velocity
*/
array<float, 3> OrbitModeling::GetCurrSatEciVel(){
	return sat_curr_eci_vel_mps_;
}

/* This function propogates the satellite position using first order Euler 
integration using the acceleration from the gravity model.
*/
void OrbitModeling::Step(GravityModel &gravity_model){
	/* Get the acceleration due to gravity at the current position
	*/
	array<float, 3> grav_accel_eci_mps2 = gravity_model.GetGravityAccel(sat_curr_eci_pos_m_);

	/* Much more complex integration scheme can be used for improved accuracy but for simplicity only
	forward Euler is used
	*/
	for (size_t idx = 0; idx < 3; idx++){
		sat_curr_eci_pos_m_[idx] += sat_curr_eci_vel_mps_[idx]*sample_time_s_ + 0.5*pow(sample_time_s_, 2)*grav_accel_eci_mps2[idx];
		sat_curr_eci_vel_mps_[idx] += sample_time_s_*grav_accel_eci_mps2[idx];
	}

}
