/*
 * =====================================================================================
 *
 *       Filename:  data_structures.cpp
 *
 *    Description:  Data structure implementations
 *
 *        Version:  1.0
 *        Created:  10/27/2018 03:49:23 PM
 *       Revision:  none
 *
 *         Author:  Sachin
 *   Organization:
 *
 * =====================================================================================
 */

#include "data_structures.hpp"

Particle::Particle()
{
}

Particle::Particle(double x, double y, double z)
{
    this->setCoord(x, y, z);
    return;
}

Particle::~Particle()
{
}

void Particle::setCoord(double x, double y, double z)
{
    this->coord[0] = x;
    this->coord[1] = y;
    this->coord[2] = z;
    return;
}
