/*
 * =====================================================================================
 *
 *       Filename:  variables.hpp
 *
 *    Description:  Global variable declarations
 *
 *        Version:  1.0
 *        Created:  10/27/2018 03:45:32 PM
 *       Revision:  none
 *
 *         Author:  Sachin
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef __VARIABLES_HPP__
#define __VARIABLES_HPP__

#include "data_structures.hpp"
#include <random>

extern int nspheres;
extern int random_seed;
extern int mc_steps;
extern int out_time;
extern double radius;
extern double packing_fraction;
extern double box_size;
extern std::vector <Particle> hsphere;

extern std::mt19937 generator;
extern unsigned int GEN_MAX;
extern unsigned int GEN_MIN;


#endif
