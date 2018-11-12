/*
 * =====================================================================================
 *
 *       Filename:  data_structures.hpp
 *
 *    Description:  Data structure definitions
 *
 *        Version:  1.0
 *        Created:  10/27/2018 02:57:45 PM
 *       Revision:  none
 *
 *         Author:  Sachin
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef __DATA_STRUCTURES_HPP__
#define __DATA_STRUCTURES_HPP__

class Particle{
public:
    double coord[3];
    Particle();
    Particle(double, double, double);
    ~Particle();
    void setCoord(double, double, double);
};


#endif
