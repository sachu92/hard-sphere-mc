/*
 * =====================================================================================
 *
 *       Filename:  rdf_pp.hpp
 *
 *    Description:  Post process MC output in VTK format to calculate the radial distribution function
 *
 *        Version:  1.0
 *        Created:  11/12/2018 19:32:32 PM
 *       Revision:  none
 *
 *         Author:  Sachin
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    int i,j,k;
    int num_bins;
    int start_time;
    int stop_time;
    int cu_time;
    int nspheres = 0;
    double mean_density;
    double box_size;
    double box_lim;
    double dr;
    double dis;
    double radius;
    char filename[256];

    if(argc < 6)
    {
        cout<<"Usage: "<<argv[0]<<" <start_time> <stop_time> <box_size> <num_bins> <data_folder>"<<endl;
        return 0;
    }
    start_time = atoi(argv[1]);
    stop_time = atoi(argv[2]);
    box_size = atof(argv[3]);
    num_bins = atoi(argv[4]);

    box_lim = box_size / 2.0;
    dr = box_size / (2.0 * num_bins);

    int ngr = 0;
    string temp;
    string line;
    vector < long long > nr;
    ifstream fin;
    double volbin;
    double nid;
    double r12[3];
    double **r = nullptr;

    for(i = 0;i < num_bins;i++)
        nr.push_back(0);

    for(cu_time = start_time; cu_time <= stop_time;cu_time++)
    {
        sprintf(filename, "%s/out.%d.vtk", argv[5], cu_time);
        fin.open(filename, ios::in);
        getline(fin, line);
        getline(fin, line);
        getline(fin, line);
        getline(fin, line);
        getline(fin, line);
        if(cu_time == start_time)
        {
            stringstream iss(line);
            getline(iss, temp, ' ');
            getline(iss, temp, ' ');
            nspheres = atoi(temp.c_str());
            r = (double **) malloc(sizeof(double *) * nspheres);
            for(i = 0;i < nspheres;i++)
                r[i] = (double *) malloc(sizeof(double) * 3);

        }
        for(i = 0;i < nspheres;i++)
        {
            getline(fin, line);
            stringstream iss(line);
            iss>>r[i][0]>>r[i][1]>>r[i][2];
        }
        fin.close();
        mean_density = nspheres / (box_size * box_size * box_size);
        ngr += 1;
        for(i = 0;i < nspheres - 1;i++)
        {
            for(j = i+1;j < nspheres;j++)
            {
                r12[0] = r[j][0] - r[i][0];
                r12[1] = r[j][1] - r[i][1];
                r12[2] = r[j][2] - r[i][2];
                // minimum image correction
                for(k = 0;k < 3;k++)
                {
                    if(r12[k] > box_lim)
                        r12[k] -= box_size;
                    else if(r12[k] < -box_lim)
                        r12[k] += box_size;
                }
                dis = sqrt(r12[0]*r12[0] + r12[1]*r12[1] + r12[2]*r12[2]);
                if(dis < box_lim)
                    nr[(int)(dis/dr)]+=2;
            }
        }
    }
    for(i = 0;i < nspheres;i++)
    {
        if(r[i] != NULL)
            free(r[i]);
    }
    if(r != NULL)
        free(r);

    ofstream fout;
    fout.open("rdf.dat", ios::out);
    for(i = 0; i < num_bins;i++)
    {
        radius = (i + 0.5) * dr;
        volbin = ((i+1)*(i+1)*(i+1) - i*i*i)*dr*dr*dr;
        nid=(4.18879*volbin*mean_density);
        fout<<radius<<" "<<nr[i] / (ngr * nspheres * nid)<<endl;
    }
    fout.close();

    return 0;
}
