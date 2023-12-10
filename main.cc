#include <gravity_model_jgm3.h>
#include <orbit_modeling.h>

#include <iostream>
#include <fstream>


int main(int argc, char *argv[]){

	// JGM-3 gravity model object
	GravityModelJgm3 test_gravity(6.3781e6, 3.986004415e14, -0.108262668355e-2);

	float sample_time_s = 0.01;
	// Orbit modeling object
	OrbitModeling test_orbit(array<float, 3>{6.778100e6, 0.0, 100e3}, array<float, 3>{0.0, 7.66e3, 0.0}, sample_time_s);

	// Sim duration and sim timer
	float sim_duration_s = 90*60*5.0;
	float sim_time_s = 0;

	array<float, 3> sat_eci_pos;

	// Save sim data to .CSV for post inspection to create plots with python
	std::ofstream orbit_save_file;
    orbit_save_file.open ("orbit_sim_data.csv");
	orbit_save_file <<"Time,X,Y,Z\n";
	while(sim_time_s < sim_duration_s){
		test_orbit.Step(test_gravity);
		sat_eci_pos = test_orbit.GetCurrSatEciPos();
		orbit_save_file <<sim_time_s<<", "<<sat_eci_pos[0]<<", "<<sat_eci_pos[1]<<", "<<sat_eci_pos[2]<<"\n";
		sim_time_s += sample_time_s;
	}

	orbit_save_file.close();
	return 0;
}