#include <stdio.h>
#include <stdlib.h>
#include "memory.h"


int n;
double *bodies_position;
double *bodies_attrs;


void print_body(int i) {
    printf("%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", i, bodies_position[i*3], bodies_position[(i*3)+1], bodies_position[(i*3)+2], bodies_attrs[(i*4)], bodies_attrs[(i*4)+1], bodies_attrs[(i*4)+2], bodies_attrs[(i*4)+3]);
}

void print_bodies(){
    for(int i=0; i<n; i++){
        print_body(i);
    }
}

void initialize(){
    scanf("%d", &n);
    bodies_position = (double*)malloc(sizeof(double)*n*3);
    bodies_attrs = (double*)malloc(sizeof(double)*n*4);
    
    for(int i=0; i<n; i++){
        //     x   y   z   m   sx  sy  sz
        scanf("%lf %lf %lf %lf %lf %lf %lf", &bodies_position[i*3], &bodies_position[(i*3)+1], &bodies_position[(i*3)+2], &bodies_attrs[(i*4)], &bodies_attrs[(i*4)+1], &bodies_attrs[(i*4)+2], &bodies_attrs[(i*4)+3]);
	}
}

void terminate(){
    free(bodies_position);
    free(bodies_attrs);
}