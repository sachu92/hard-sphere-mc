/*
 * =====================================================================================
 *
 *       Filename:  main.hpp
 *
 *    Description:  Monte carlo code for hard sphere fluids
 *
 *        Version:  1.0
 *        Created:  10/27/2018 03:45:32 PM
 *       Revision:  none
 *       Compiler:  g++
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
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <random>
#include "data_structures.hpp"
#include "variables.hpp"
#include "helpers.hpp"
#include "mc_moves.hpp"
using namespace std;

int nspheres;
int random_seed;
int mc_steps;
int out_time;
double radius;
double packing_fraction;
double box_size;
vector <Particle> hsphere;

mt19937 generator;
unsigned int GEN_MAX;
unsigned int GEN_MIN;

int main(int argc, char *argv[])
{
    int i;
    int j;
    if(argc < 2)
    {
        cout<<"Please provide input file."<<endl;
        return 0;
    }

    int rand_sphere;
    int moveSuccess;
    long long nmoves = 0;
    long long namoves = 0;

    // Read input file
    ifstream infile;
    string line;
    char temp[512];

    infile.open(argv[1], ios::in);
    while(!infile.eof())
    {
        infile>>line;
        strcpy(temp, line.c_str());
        if(temp[0] == '#')
        {
            continue;
        }
        else if(strcmp(temp, "packing-fraction:")==0)
        {
            infile>>packing_fraction;
        }
        else if(strcmp(temp, "sphere-radius:")==0)
        {
            infile>>radius;
        }
        else if(strcmp(temp, "box-size:")==0)
        {
            infile>>box_size;
        }
        else if(strcmp(temp, "seed:")==0)
        {
            infile>>random_seed;
        }
        else if(strcmp(temp, "mc-steps:")==0)
        {
            infile>>mc_steps;
        }
        else if(strcmp(temp, "out-time:")==0)
        {
            infile>>out_time;
        }
    }
    // Initialize data containers
    generator.seed(random_seed);
    GEN_MAX = generator.max();
    GEN_MIN = generator.min();

    double lbyr = box_size/radius;
    nspheres = (int) (0.2387324 * packing_fraction * lbyr * lbyr * lbyr); // N = 3 * phi * L^3 / r^3
    cout<<"Box dimension = "<<box_size<<endl;
    cout<<"Number of spheres = "<<nspheres<<endl;
    // Set initial positions
    for(i = 0;i < nspheres;i++)
    {
        double px, py, pz;
        px = (udist() * box_size) - box_size / 2.0;
        py = (udist() * box_size) - box_size / 2.0;
        pz = (udist() * box_size) - box_size / 2.0;
        Particle p;
        p.setCoord(px, py, pz);
        hsphere.push_back(p);
        if(collisionCheck(i))
        {
            hsphere.pop_back();
            i--;
        }
        cout<<"\r "<<(i+1)<<" / "<<nspheres;
        fflush(stdout);
    }
    cout<<"\nParticles created."<<endl;
    outputFile(0);
    // Main MC loop
    for(i = 1; i <= mc_steps;i++)
    {
        for(j = 0;j < nspheres;j++)
        {
            rand_sphere = (int) (udist() * nspheres);
            moveSuccess = moveSphere(rand_sphere);
            namoves += moveSuccess;
            nmoves++;
        }
        if(i % out_time == 0)
        {
            cout<<"\rStep "<<i<<" / "<<mc_steps;
            fflush(stdout);
            outputFile(i/out_time);
        }
    }
    // Clean and Exit
    cout<<"\nAcceptance ratio : "<<((double) namoves)/((double) nmoves)<<endl;
    hsphere.clear();
    return 0;
}
