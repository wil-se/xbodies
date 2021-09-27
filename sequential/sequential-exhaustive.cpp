#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


#include "sequential-exhaustive.h"
#include "../common/memory.h"

void compute_sequential_exhaustive(){
    for(int body1=0; body1<n; body1++){
        for(int body2=0; body2<n; body2++){
			if(body2 != body1){
				compute_ex_force(body2, body1, new_bodies_position, new_bodies_attrs);	
			}
        }
    }
    double *temp_pos;
	double *temp_attrs;
	
	temp_pos = bodies_position;
    temp_attrs = bodies_attrs;

	bodies_position = new_bodies_position;
    bodies_attrs = new_bodies_attrs;

	new_bodies_position = temp_pos;
	new_bodies_attrs = temp_attrs;
}

void compute_ex_force(int body2, int body1, double* new_position, double* new_attrs){

    double acc[3] = {0, 0, 0};
	double force[3] = {0, 0, 0};
	double distance[3] = {bodies_position[(body2*3)] - bodies_position[(body1*3)], bodies_position[(body2*3)+1] - bodies_position[(body1*3)+1], bodies_position[(body2*3)+2] - bodies_position[(body1*3)+2]};
	double dist = sqrt(pow(bodies_position[(body2*3)] - bodies_position[(body1*3)],2) + pow(bodies_position[(body2*3)+1] - bodies_position[(body1*3)+1],2) + pow(bodies_position[(body2*3)+2] - bodies_position[(body1*3)+2],2));
	double unit_vector[3] = {distance[0]/fabs(distance[0]), distance[1]/fabs(distance[1]), distance[2]/fabs(distance[2])};

    if(distance[0] == 0){
		unit_vector[0] = 0;
	}
	if(distance[1] == 0){
		unit_vector[1] = 0;
	}
	if(distance[2] == 0){
		unit_vector[2] = 0;
	}

    force[0] = -G*((bodies_attrs[(body1*4)]*bodies_attrs[(body2*4)]/pow(dist, 2)))*unit_vector[0];
	force[1] = -G*((bodies_attrs[(body1*4)]*bodies_attrs[(body2*4)]/pow(dist, 2)))*unit_vector[1];
	force[2] = -G*((bodies_attrs[(body1*4)]*bodies_attrs[(body2*4)]/pow(dist, 2)))*unit_vector[2];

    acc[0] = force[0]/bodies_attrs[(body2*4)];
	acc[1] = force[1]/bodies_attrs[(body2*4)];
	acc[2] = force[2]/bodies_attrs[(body2*4)];
	
	new_position[(body2*3)] += new_attrs[(body2*4)+1]*dt + (acc[0])*dt*dt*0.5;
	new_position[(body2*3)+1] += new_attrs[(body2*4)+2]*dt + (acc[1])*dt*dt*0.5;
	new_position[(body2*3)+2] += new_attrs[(body2*4)+3]*dt + (acc[2])*dt*dt*0.5;

    double new_acc[3] = {0, 0, 0};
	double new_force[3] = {0, 0, 0};
	double new_distance[3] = {new_position[(body2*3)] - bodies_position[(body1*3)], new_position[(body2*3)+1] - bodies_position[(body1*3)+1], new_position[(body2*3)+2] - bodies_position[(body1*3)+2]};
	double new_dist = sqrt(pow(new_position[(body2*3)] - bodies_position[(body1*3)],2) + pow(new_position[(body2*3)+1] - bodies_position[(body1*3)+1],2) + pow(new_position[(body2*3)+2] - bodies_position[(body1*3)+2],2));
	double new_unit_vector[3] = {new_distance[0]/fabs(new_distance[0]), new_distance[1]/fabs(new_distance[1]), new_distance[2]/fabs(new_distance[2])};

    if(new_distance[0] == 0){
		new_unit_vector[0] = 0;
	}
	if(new_distance[1] == 0){
		new_unit_vector[1] = 0;
	}
	if(new_distance[2] == 0){
		new_unit_vector[2] = 0;
	}

    new_force[0] = -G*((bodies_attrs[(body1*4)]*bodies_attrs[(body2*4)]/pow(new_dist, 2)))*new_unit_vector[0];
	new_force[1] = -G*((bodies_attrs[(body1*4)]*bodies_attrs[(body2*4)]/pow(new_dist, 2)))*new_unit_vector[1];
	new_force[2] = -G*((bodies_attrs[(body1*4)]*bodies_attrs[(body2*4)]/pow(new_dist, 2)))*new_unit_vector[2];

    new_acc[0] = new_force[0]/bodies_attrs[(body2*4)];
	new_acc[1] = new_force[1]/bodies_attrs[(body2*4)];
	new_acc[2] = new_force[2]/bodies_attrs[(body2*4)];

    new_attrs[(body2*4)+1] += 0.5*(acc[0] + new_acc[0])*dt;
	new_attrs[(body2*4)+2] += 0.5*(acc[1] + new_acc[1])*dt;
	new_attrs[(body2*4)+3] += 0.5*(acc[2] + new_acc[2])*dt;
}


