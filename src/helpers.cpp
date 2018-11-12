/*
 * =====================================================================================
 *
 *       Filename:  helpers.cpp
 *
 *    Description:  Helper function implementations
 *
 *        Version:  1.0
 *        Created:  10/27/2018 03:43:36 PM
 *       Revision:  none
 *
 *         Author:  Sachin
 *   Organization:
 *
 * =====================================================================================
 */
#include <fstream>
#include "helpers.hpp"
#include "variables.hpp"

using namespace std;

double udist()
{
    return (static_cast<double>(generator()) / (static_cast<double> (GEN_MAX - GEN_MIN) + 1.0));
}

int collisionCheck(int p)
{
    int i;
    int nsp = hsphere.size();
    for(i = 0;i < nsp;i++)
    {
        if(i != p)
        {
            if(dist(p, i) < 2.0*radius)
               return 1;
        }
    }
    return 0;
}

void wrapPBC(int p)
{
    int i;
    double box_lim = box_size / 2.0;
    for(i = 0;i < 3;i++)
    {
        if(hsphere[p].coord[i] > box_lim )
            hsphere[p].coord[i] -= box_size;
        else if(hsphere[p].coord[i] < -box_lim)
            hsphere[p].coord[i] += box_size;
    }
    return;
}

double dist(int s1, int s2)
{
    int i;
    double r[3];
    double dis;
    double box_lim = box_size / 2.0;
    // We have to take the difference of the coordinates with the minimum image here
    r[0] = hsphere[s1].coord[0] - hsphere[s2].coord[0];
    r[1] = hsphere[s1].coord[1] - hsphere[s2].coord[1];
    r[2] = hsphere[s1].coord[2] - hsphere[s2].coord[2];
    for(i = 0;i < 3;i++)
    {
        if(r[i] > box_lim)
            r[i] -= box_size;
        else if (r[i] < -box_lim)
            r[i] += box_size;
    }

    dis = sqrt(r[0]*r[0] + r[1]*r[1] + r[2]*r[2]);
    return dis;
}

void outputFile(int t)
{
    ofstream fout;
    char filename[256];
    sprintf(filename, "out.%d.vtk", t);
    fout.open(filename, ios::out);
    fout<<"# vtk DataFile Version 2.0"<<endl;
    fout<<"hardSpheres Output"<<endl;
    fout<<"ASCII"<<endl;
    fout<<"DATASET POLYDATA"<<endl;
    fout<<"POINTS "<<hsphere.size()<<" float"<<endl;
    for(unsigned int i = 0;i < hsphere.size();i++)
    {
        fout<<hsphere[i].coord[0]<<" "<<hsphere[i].coord[1]<<" "<<hsphere[i].coord[2]<<endl;
    }
    fout.close();
    return;
}
